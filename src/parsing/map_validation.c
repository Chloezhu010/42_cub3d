#include "../incl/cub3D.h"

/* map check general logic
    - trin the line with space and find may edges
    - check top & bottom boundary: only 1 or space allowed
    - check left boundary: all trimmed rows start with 1
    - check right boundary: all trimmed rows finished with 1
    - player validation
        - locate player
        - check player pos
    - walkable area check
*/

/* find edges of the map */
void    find_edges(t_map *map, int *first_col, int *last_col)
{
    int row;
    int current_col;
    int end_col;
    
    row = 0;
    *first_col = INT_MAX;
    *last_col = 0;
    while (row < map->height)
    {
        if (!is_empty_line(map->grid[row]))
        {
            current_col = 0;
            /* find the first non-space char */
            while (is_space(map->grid[row][current_col]))
                current_col++;
            if (current_col < *first_col)
                *first_col = current_col;
            /* find the last non-space char */
            end_col = ft_strlen(map->grid[row]) - 1;
            while (end_col > 0 && is_space(map->grid[row][end_col]))
                end_col--;
            if (end_col > *last_col)
                *last_col = end_col;
        }
        printf("DEBUG row %d: current col: %d, end col: %d\n", row, current_col, end_col);
        printf("DEBUG row %d: first col: %d, last col: %d\n", row, *first_col, *last_col);
        row++;
    }
}

// testing
int main()
{
    t_map map;
    int first_col;
    int last_col;
    char *grid[] = {
        "    111", // Row 0 - spaces at start
        "    101", // Row 1
        "1101101", // Row 2 - different length
        "101 101", // Row 3 - spaces in middle
        "  1111 ", // Row 4
        NULL  
    };
    map.grid = grid;
    map.height = 5;
    find_edges(&map, &first_col, &last_col);
}