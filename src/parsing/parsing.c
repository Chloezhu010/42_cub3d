/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:11 by czhu              #+#    #+#             */
/*   Updated: 2025/04/15 19:57:57 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* check if the file is in .cub 
    - return 1 if in .cub
    - return 0 if not
*/
int check_file_extension(char *filename)
{
    char    *dot;

    dot = ft_strchr(filename, '.');
    if (!dot || ft_strncmp(dot, ".cub", 4) != 0)
        return (0);
    return (1);
}

/* check if a line is part of the map grid
    - return 0 if empty line or invalid
    - return 1 if it's part of the map line
*/
int is_map_line(char *line)
{
    int i;

    i = 0;
    /* skip the space */
    while (line[i] && line[i] == ' ')
        i++;
    /* if empty line */
    if (!line[i])
        return (0);
    /* if the line contains invalid char */
    while (line[i])
    {
        if (!ft_strchr("01NSEW", line[i]))
            return (0);
        i++;
    }
    return (1);
}

/* check map if it
    - can open properly
    - has all the components: NSWE, FC, map
*/
int check_map_component(char *file_path)
{
    int fd;
    char    *line;
    int has_north;
    int has_south;
    int has_west;
    int has_east;
    int has_floor;
    int has_celling;
    int has_map;

    has_north = 0;
    has_south = 0;
    has_west = 0;
    has_east = 0;
    has_floor = 0;
    has_celling = 0;
    has_map = 0;
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (0);
    /* read line by line and check for componenets */
    line = get_next_line(fd);
    while (line)
    {
        /* chekc NSWE FC */
        if (ft_strnstr(line, "NO ", 3))
            has_north = 1;
        else if (ft_strnstr(line, "SO ", 3))
            has_south = 1;
        else if (ft_strnstr(line, "WE ", 3))
            has_west = 1;
        else if (ft_strnstr(line, "EA ", 3))
            has_east = 1;
        else if (ft_strnstr(line, "F ", 2))
            has_floor = 1;
        else if (ft_strnstr(line, "C ", 2))
            has_celling = 1;
        /* check map */
        else if (is_map_line(line))
            has_map = 1;
        free(line);
        line = get_next_line(fd);
    }
    /* check if all components are incl */
    return (has_north && has_south && has_west && has_east
        && has_floor && has_celling && has_map);
}

/* check if F/C's color is right */

/* check map is valid */

/* check NSWE has the right texture */

/* testing */
// // testing check_file_extension
// int main()
// {
//     char *s1 = "test.cub";
//     char *s2 = "test";

//     printf("%d\n", check_file_extension(s1));
//     printf("%d\n", check_file_extension(s2));
// }

// test check_map_component
int main(int ac, char **av)
{
    (void)ac;

    printf("%d\n", check_map_component(av[1]));
}