/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:11 by czhu              #+#    #+#             */
/*   Updated: 2025/04/17 18:09:39 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* check if a char is a space
    - return 1 if it's a space
    - return 0 if not
*/
int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\v')
        return (1);
    return (0);
}

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

/* check if the RGB color of floor/ceiling is right
    - return 1 if valid
    - return 0 if not
*/
int is_valid_rgb(char *line)
{
    int i;
    int count;
    int value;

    i = 0;
    count = 0;
    /* skip F or C or space */
    while (line[i] && (line[i] == 'F' || line[i] == 'C' || is_space(line[i])))
        i++;
    while (line[i])
    {
        while (is_space(line[i]))
            i++;
        /* check if it's a digit */
        if (!ft_isdigit(line[i]) && line[i] != ',')
            return (0);
        /* parse the rgb value */
        if (ft_isdigit(line[i]))
        {
            value = ft_atoi(&line[i]);
            /* check if the value is in the range 0-255 */
            if (value < 0 || value > 255)
                return (0);
            count++;
            while (line[i] && ft_isdigit(line[i]))
                i++;
        }
        else
            i++;
    }
    /* check if have 3 valid values for RGB */
    return (count == 3);
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

/* check map if it
    - can open properly
    - has all the components: NSWE, FC, map
    - return 1 if valid, return 0 if not
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
    int map_started;
    int emtpy_after_map;
    int invalid_after_map;

    has_north = 0;
    has_south = 0;
    has_west = 0;
    has_east = 0;
    has_floor = 0;
    has_celling = 0;
    has_map = 0;
    map_started = 0;
    emtpy_after_map = 0;
    invalid_after_map = 0;
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (0);
    /* read line by line and check for componenets */
    line = get_next_line(fd);
    while (line)
    {
        /* skip empty line */
        if (is_empty_line(line))
        {
            /* if map already started and see the empty line, flag it */
            if (map_started)
                emtpy_after_map = 1;
            free(line);
            line = get_next_line(fd);
            continue ;
        }
        /* check map */
        else if (is_map_line(line))
        {
            has_map = 1;
            /* if see map content, then empty line, then map content, invalid */
            if (map_started && emtpy_after_map)
                invalid_after_map = 1;
            map_started = 1;
        }
        /* if map has started, and it's non-map non-empty line, then invalid */
        else if (map_started)
            invalid_after_map = 1;
        else
        {
            /* chekc has NSWE */
            if (ft_strnstr(line, "NO ", 3))
            has_north = 1;
            else if (ft_strnstr(line, "SO ", 3))
                has_south = 1;
            else if (ft_strnstr(line, "WE ", 3))
                has_west = 1;
            else if (ft_strnstr(line, "EA ", 3))
                has_east = 1;
            /* check has FC, validate its RGB color */
            else if (ft_strnstr(line, "F ", 2))
                has_floor = is_valid_rgb(line);
            else if (ft_strnstr(line, "C ", 2))
                has_celling = is_valid_rgb(line);
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    /* check if all components are incl */
    return (has_north && has_south && has_west && has_east
        && has_floor && has_celling && has_map && !invalid_after_map);
}

/* check map is valid */

/* check NSWE has the right texture */

/* check the order
    - map need to be the last item
    - no other char after the map
*/

/* testing */
// // testing check_file_extension
// int main()
// {
//     char *s1 = "test.cub";
//     char *s2 = "test";

//     printf("%d\n", check_file_extension(s1));
//     printf("%d\n", check_file_extension(s2));
// }

// // test is_valid_rgb
// int main()
// {
//     char *line1 = "F 20,20,-20";
//     char *line2 = "C 200,200,200";
//     char *line3 = "G 200,200,200";
//     char *line4 = "C 200,200,";
//     char *line5 = "C ,,,";
//     char *line6 = "      F      17,    38,     64";
//     char *line7 = "C 200,          200,200";
    
//     printf("%d\n", is_valid_rgb(line1));
//     printf("%d\n", is_valid_rgb(line2));
//     printf("%d\n", is_valid_rgb(line3));
//     printf("%d\n", is_valid_rgb(line4));
//     printf("%d\n", is_valid_rgb(line5));
//     printf("%d\n", is_valid_rgb(line6));
//     printf("%d\n", is_valid_rgb(line7));
// }

// test check_map_component
int main(int ac, char **av)
{
    (void)ac;

    printf("%d\n", check_map_component(av[1]));
}