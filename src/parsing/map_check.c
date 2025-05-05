/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:46:37 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 17:01:12 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* check if a line is part of the map grid
    - return 0 if empty line or invalid
    - return 1 if it's part of the map line
*/
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return (0);
	while (line[i])
	{
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

/* helper function to check if a line is empty
    - return 1 if it's empty line
    - return 0 if not
*/
int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/* check if it's a player char */
int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W'
		|| c == 'E');
}

/* count player nbr and store player's pos
    - return 1 if there is only 1 player,
        and store player's x,y pos in map
    - return 0 if invalid
*/
static void	update_player_position(t_map *map, int row
		, int col, int *player_count)
{
	if (is_player(map->grid[row][col]))
	{
		(*player_count)++;
		if (*player_count == 1)
		{
			map->player_x = col;
			map->player_y = row;
		}
		else
		{
			map->player_x = -1;
			map->player_y = -1;
		}
	}
}

int	process_player(t_map *map)
{
	int	row;
	int	col;
	int	player_count;

	player_count = 0;
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < (int)ft_strlen(map->grid[row]))
		{
			update_player_position(map, row, col, &player_count);
			col++;
		}
		row++;
	}
	return (player_count == 1);
}

// // test boundary check
// int main()
// {
//     char *grid[] = {
//         "    111", // Row 0 - spaces at start
//         "    1S1", // Row 1
//         "11111 1", // Row 2 - different length
//         "1 1 101", // Row 3 - spaces in middle
//         "111 111", // Row 4
//         NULL  
//     };
//     printf("expected 0: %d\n", is_within_bounds(grid, 0, 0, 5)); 
//     printf("expected 0: %d\n", is_within_bounds(grid, 1, 1, 5)); 
//     printf("expected 0: %d\n", is_within_bounds(grid, 0, 15, 5));
//     printf("expected 0/1: %d\n", is_within_bounds(grid, 3, 3, 5));
//     printf("expected 1: %d\n", is_within_bounds(grid, 0, 6, 5));
//     printf("expected 1: %d\n", is_within_bounds(grid, 2, 5, 5));
//     printf("expected 1: %d\n", is_within_bounds(grid, 4, 6, 5));
// }

// // test 
// int main()
// {
//     t_map map;
//     // char *grid[] = {
//     //     "    111", // Row 0 - spaces at start
//     //     "    101", // Row 1
//     //     "11011S1", // Row 2 - different length
//     //     "101 101", // Row 3 - spaces in middle
//     //     "111 111", // Row 4
//     //     NULL  
//     // };
//     char *grid[] = {
//         "111",
//         "111",
//         "1S1",
//         "101",
//         "101",
//         "101",
//         "101",
//         NULL
//     };
//     map.grid = grid;
//     map.height = 5;
//     map.width = 3;
//     // map.player_x = 1;
//     // map.player_y = 2;
//     // printf("%d\n", process_player(&map));
//     // printf("col: %d, row: %d\n", map.player_x, map.player_y);
//     // printf("%d\n", is_map_closed(&map));
//     printf("%d\n", validate_map(&map));
// }
