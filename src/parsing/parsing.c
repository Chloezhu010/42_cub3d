/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:51:41 by auzou             #+#    #+#             */
/*   Updated: 2025/05/03 18:37:38 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* extract texture path for NSWE */
char	*extract_texture_path(char *line)
{
	char	*path;
	int		i;
	int		start;

	i = 0;
	while (is_space(line[i]))
		i++;
	while (line[i] && !is_space(line[i]))
		i++;
	while (is_space(line[i]))
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	i--;
	while (i > start && is_space(line[i]))
		i--;
	path = ft_substr(line, start, i - start + 1);
	return (path);
}

/* parse RBG for floor & ceiling */
int	parse_rgb(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;
	int	comma;

	i = 0;
	comma = 0;
	while (is_space(line[i]))
		i++;
	while (line[i] && (line[i] == 'F'
			|| line[i] == 'C' || is_space(line[i])))
		i++;
	while (is_space(line[i]))
		i++;
	r = ft_atoi(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == ',')
	{
		i++;
		comma++;
	}
	while (line[i] && is_space(line[i]))
		i++;
	g = ft_atoi(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == ',')
	{
		i++;
		comma++;
	}
	while (line[i] && is_space(line[i]))
		i++;
	b = ft_atoi(&line[i]);
	return ((r << 16) | (g << 8) | b);
}

/* parse a single line for color or texture info */
int	parse_element_line(char *line, t_texture *texture)
{
	if (ft_strstr(line, "NO"))
	{
		texture->north_path = extract_texture_path(line);
		return (1);
	}
	else if (ft_strstr(line, "SO"))
	{
		texture->south_path = extract_texture_path(line);
		return (1);
	}
	else if (ft_strstr(line, "WE"))
	{
		texture->west_path = extract_texture_path(line);
		return (1);
	}
	else if (ft_strstr(line, "EA"))
	{
		texture->east_path = extract_texture_path(line);
		return (1);
	}
	else if (ft_strstr(line, "F"))
	{
		texture->floor_color = parse_rgb(line);
		return (1);
	}
	else if (ft_strstr(line, "C"))
	{
		texture->ceiling_color = parse_rgb(line);
		return (1);
	}
	return (0);
}

/* fill the map structure */
void	build_map(char *file_path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
			add_line_to_map(map, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	process_player(map);
}

/* extract the player direction
    - return N/ S /W /E */
char	get_player_direction(t_map *map)
{
	if (map->player_x >= 0 && map->player_y >= 0
		&& map->player_y < map->height
		&& map->player_x < (int)ft_strlen(map->grid[map->player_y]))
		return (map->grid[map->player_y][map->player_x]);
	return (0);
}

/* init the player based on the input */
void	init_player_from_map(t_player *player, t_map *map)
{
	char	direction;

	player->pos_x = map->player_x * BLOCK + BLOCK / 2;
	player->pos_y = map->player_y * BLOCK + BLOCK / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	direction = get_player_direction(map);
	if (direction == 'S')
		player->angle = PI / 2;
	else if (direction == 'N')
		player->angle = PI * 3 / 2;
	else if (direction == 'W')
		player->angle = PI;
	else if (direction == 'E')
		player->angle = 0;
}

/* main parsing function */
int	parse_input(char *file_path, t_map *map
		, t_texture *texture, t_player *player)
{
	int		fd;
	char	*line;

	if (!check_input(file_path))
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		parse_element_line(line, texture);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	build_map(file_path, map);
	init_player_from_map(player, map);

	return (1);
}

// // testing extract_texture_path
// int main()
// {
//     char *line1 = "NO textures/test/north.xpm";
//     char *line2 = "   EA      textures/test/east.xpm   ";
//     printf("line1: %s\n", extract_texture_path(line1));
//     printf("line2: %s\n", extract_texture_path(line2));
// }

// // test parse_rgb
// int main()
// {
//     char *line1 = "     F 20,           20,             20";
//     char *line2 = "C 255,    0, 0";
//     printf("line1: %X\n", parse_rgb(line1));
//     printf("line2: %X\n", parse_rgb(line2));
// }

// // test parse_element_line
// int main(int ac, char **av)
// {
//     t_texture *texture;
//     if (ac != 2)
//     {
//         printf("Error\nUsage ./cub3D <map .cub>\n");
//         return (1);
//     }
//     texture = malloc(sizeof(t_texture));
//     if (!texture)
//         return (0);
//     ft_memset(texture, 0, sizeof(t_texture));
//     if (!parse_input(av[1], texture))
//         return (0);
//     print_texture(texture); //DEBUG
// }

// // test build_map, init_player_from_map
// int main(int ac, char **av)
// {
//     t_texture *texture;
//     t_map *map; 
//     t_player *player;
//     if (ac != 2)
//     {
//         printf("Error\nUsage ./cub3D <map .cub>\n");
//         return (1);
//     }
//     // init the struct
//     texture = malloc(sizeof(t_texture));
//     map = malloc(sizeof(t_map));
//     player = malloc(sizeof(t_player));
//     if (!texture || !map || !player)
//         return (0);
//     ft_memset(texture, 0, sizeof(t_texture));
//     ft_memset(map, 0, sizeof(t_map));
//     ft_memset(player, 0, sizeof(t_player));
//     // parse input
//     if (!parse_input(av[1], map, texture, player))
//         return (0);
//     // debug print
//     print_map(map);
//     print_player(player);
// }