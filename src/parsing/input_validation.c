/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhu <czhu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:11 by czhu              #+#    #+#             */
/*   Updated: 2025/05/04 12:46:27 by czhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* helper function: check texture & handle duplication */
void	check_nswe_texture(char *line, t_component *ctx)
{
	if (ft_strstr(line, "NO") && check_texture_extension(line))
	{
		if (ctx->has_north)
			ctx->invalid = 1;
		ctx->has_north = 1;
	}
	else if (ft_strstr(line, "SO") && check_texture_extension(line))
	{
		if (ctx->has_south)
			ctx->invalid = 1;
		ctx->has_south = 1;
	}
	else if (ft_strstr(line, "WE") && check_texture_extension(line))
	{
		if (ctx->has_west)
			ctx->invalid = 1;
		ctx->has_west = 1;
	}
	else if (ft_strstr(line, "EA") && check_texture_extension(line))
	{
		if (ctx->has_east)
			ctx->invalid = 1;
		ctx->has_east = 1;
	}
}

/* helper function: check FC texture & handle duplication */
void	check_fc_texture(char *line, t_component *ctx)
{
	if (ft_strstr(line, "F"))
	{
		if (ctx->has_floor)
			ctx->invalid = 1;
		ctx->has_floor = is_valid_rgb(line);
	}
	else if (ft_strstr(line, "C"))
	{
		if (ctx->has_ceiling)
			ctx->invalid = 1;
		ctx->has_ceiling = is_valid_rgb(line);
	}
}

/* add a line to the map grid and update width, height */
int	add_line_to_map(t_map *map, char *line)
{
	char	**new_grid;
	int		i;

	new_grid = (char **)ft_calloc(map->height + 2, sizeof(char *));
	if (!new_grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = map->grid[i];
		i++;
	}
	new_grid[i] = ft_strdup(line);
	if (!new_grid[i])
	{
		free(new_grid);
		return (0);
	}
	map->height++;
	if ((int)ft_strlen(line) > map->width)
		map->width = (int)ft_strlen(line);
	if (map->grid)
		free(map->grid);
	map->grid = new_grid;
	return (1);
}

/* helper function: process a line of the input */
void	process_line(char *line, t_component *ctx)
{
	if (is_empty_line(line))
	{
		if (ctx->map_started)
			ctx->empty_after_map = 1;
	}
	else if (is_map_line(line))
	{
		ctx->has_map = 1;
		if (ctx->map_started && ctx->empty_after_map)
			ctx->invalid = 1;
		ctx->map_started = 1;
		if (!ctx->invalid && !add_line_to_map(&ctx->map, line))
			ctx->invalid = 1;
	}
	else if (ctx->map_started)
		ctx->invalid = 1;
	else
	{
		check_nswe_texture(line, ctx);
		check_fc_texture(line, ctx);
	}
}

/* check map if it
    - can open properly
    - has all the components & texture
        - NSWE, FC, map
    - map is the last one
    - has valid map
        - only 1 player
        - surrounded by wall
    - return 1 if valid, return 0 if not
*/
int	check_input(char *file_path)
{
	int			fd;
	char		*line;
	t_component	ctx;
	int	result;

	ft_memset(&ctx, 0, sizeof(t_component));
	ctx.map.grid = NULL;
	ctx.map.width = 0;
	ctx.map.height = 0;
	if (!check_file_extension(file_path))
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, &ctx);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	result = validate_map(&ctx.map) && ctx.has_north
		&& ctx.has_south && ctx.has_west && ctx.has_east
		&& ctx.has_ceiling && ctx.has_floor
		&& ctx.has_map && !ctx.invalid;
	free_map(&ctx.map);
	return (result);
}


// // test check_NSWE_texture
// int main(int ac, char **av)
// {
//     t_component ctx;
//     (void)ac;
//     ft_memset(&ctx, 0, sizeof(t_component));
//     check_NSWE_texture(av[1], &ctx);
//     printf("%d\n", ctx.has_west);
//     printf("%d\n", ctx.has_east);
//     printf("%d\n", ctx.has_north);
//     printf("%d\n", ctx.has_south);
// }

// // test check_input
// int main(int ac, char **av)
// {
//     (void)ac;
//     printf("%d\n", check_input(av[1]));
// }
