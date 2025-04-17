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


/* check map is valid */