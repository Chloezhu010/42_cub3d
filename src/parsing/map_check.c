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

/* flood fill to check if surrounded by wall */
int flood_fill(t_map *map, bool **visited, int x, int y)
{
    // check if the player is within bound
    if (!is_within_bounds(map->grid, y, x, map->height))
        return (0);
    // skip if already visited or wall
    if (visited[y][x] || map->grid[y][x] == '1')
        return (1);
    // check for invalid char
    if (!ft_strchr("0NSEW ", map->grid[y][x]))
        return (0);
    // mark as visited
    visited[y][x] = true;
    // recursively check adjacent cells
    return (flood_fill(map, visited, x + 1, y)
            && flood_fill(map, visited, x - 1, y)
            && flood_fill(map, visited, x, y + 1)
            && flood_fill(map, visited, x, y - 1));
}

/* free the visited grid */
void    free_visited_grid(bool **visited, int height)
{
    int i;

    if (!visited)
        return ;
    i = 0;
    while (i < height)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
}

/* init visited grid for flood fill */
bool    **create_visited_grid(int width, int height)
{
    bool **visited;
    int i;

    visited = (bool **)ft_calloc(height, sizeof(bool *));
    if (!visited)
        return (NULL);
    i = 0;
    while (i < height)
    {
        visited[i] = (bool *)ft_calloc(width, sizeof(bool));
        if (!visited[i])
        {
            free_visited_grid(visited, i);
            return (NULL);
        }
        i++;
    }
    return (visited);
}

/* check if map is closed */
int is_map_closed(t_map *map)
{
    bool    **visited;
    int     result;

    // create visited grid
    visited = create_visited_grid(map->width, map->height);
    if (!visited)
        return (0);
    // flood fill from the player pos
    result = flood_fill(map, visited, map->player_x, map->player_y);
    // cleanup and return
    free_visited_grid(visited, map->height);
    return (result);
}

int validate_map(t_map *map)
{
    // check player count & pos
    if (!process_player(map))
        return (0);
    // check map enclosure
    if (!is_map_closed(map))
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
