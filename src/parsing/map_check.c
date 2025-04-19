#include "../incl/cub3D.h"

/* check if a line is part of the map grid
    - return 0 if empty line or invalid
    - return 1 if it's part of the map line
*/
int is_map_line(char *line)
{
    int i;

    i = 0;
    /* skip the space */
    while (line[i] && is_space(line[i]))
        i++;
    /* if empty line */
    if (!line[i])
        return (0);
    /* if the line contains invalid char */
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
int is_empty_line(char *line)
{
    int i;

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
int is_player(char c)
{
    return (c == 'N' || c == 'S' || c == 'W'
        || c == 'E');
}

/* count player nbr and store player's pos
    - return 1 if there is only 1 player,
        and store player's x,y pos in map
    - return 0 if invalid
*/
int process_player(t_map *map)
{
    int row;
    int col;
    int player_count;

    player_count = 0;
    row = 0;
    while (row < map->height)
    {
        col = 0;
        while (col < (int)ft_strlen(map->grid[row]))
        {
            if (is_player(map->grid[row][col]))
            {
                player_count++;
                /* only store the player's pos if there is only 1 player */
                if (player_count == 1)
                {
                    map->player_x = col;
                    map->player_y = row;
                }
                /* else reset to -1 */
                else
                {
                    map->player_x = -1;
                    map->player_y = -1;
                }
            }
            col++;
        }
        row++;
    }
    return (player_count == 1);
}

/* check if the player pos is within bounds */
int is_within_bounds(char **grid, int row, int col, int height)
{
    int first_non_space;
    int row_len;

    /* check grid */
    if (!grid)
        return (0);
    /* check row bound */
    if (row < 0 || row >= height || !grid[row])
        return (0);
    /* skip space and check col */
    first_non_space = 0;
    row_len = ft_strlen(grid[row]);
    while (first_non_space < row_len && is_space(grid[row][first_non_space]))
        first_non_space++;
    /* check col bound */
    if (col < first_non_space || col < 0 || col >= row_len)
        return (0);
    return (1);
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

// // test process_player, is_wall_surround
// int main()
// {
//     t_map map;
//     char *grid[] = {
//         "    111", // Row 0 - spaces at start
//         "    101", // Row 1
//         "1101101", // Row 2 - different length
//         "101 101", // Row 3 - spaces in middle
//         "111 111", // Row 4
//         NULL  
//     };
//     map.grid = grid;
//     map.height = 5;
//     // printf("%d\n", process_player(&map));
//     // printf("col: %d, row: %d\n", map.player_x, map.player_y);
//     printf("expected 1: %d\n", is_wall_surround(&map));
// }
