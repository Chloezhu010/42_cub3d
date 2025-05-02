#include "../incl/cub3D.h"

/* extract texture path for NSWE */
char *extract_texture_path(char *line)
{
    char *path;
    int i;
    int start;

    i = 0;
    // skip space
    while (is_space(line[i]))
        i++;
    // skip identifier NO, SO, WE, EA
    while (line[i] && !is_space(line[i]))
        i++;
    // skip space
    while (is_space(line[i]))
        i++;
    // mark the start of the path
    start = i;
    // find the end of the path, trim the trailing space
    while (line[i] && line[i] != '\n')
        i++;
    i--;
    while (i > start && is_space(line[i]))
        i--;
    // extract and duplicate the str
    path = ft_substr(line, start, i - start + 1);
    return (path);
}

/* parse RBG for floor & ceiling */
int parse_rgb(char *line)
{
    int i;
    int r;
    int g;
    int b;
    int comma;

    i = 0;
    comma = 0;
    // skip space
    while (is_space(line[i]))
        i++;
    // skip identifier F, C
    while (line[i] && (line[i] == 'F' 
        || line[i] == 'C' || is_space(line[i])))
        i++;
    // skip space
    while (is_space(line[i]))
        i++;
    // parse R values
    r = ft_atoi(&line[i]);
    // skip to next comma
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
    // parse G value
    g = ft_atoi(&line[i]);
    // skip to next comma
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
    // parse B value
    b = ft_atoi(&line[i]);
    // convert RGB to int value
    return ((r << 16) | (g << 8) | b);
}

/* parse a single line for color or texture info */
int parse_element_line(char *line, t_texture *texture)
{
    // check for direction identifier
    if (ft_strstr(line, "NO"))
    {
        texture->north = extract_texture_path(line);
        return (1);
    }
    else if (ft_strstr(line, "SO"))
    {
        texture->south = extract_texture_path(line);
        return (1);
    }
    else if (ft_strstr(line, "WE"))
    {
        texture->west = extract_texture_path(line);
        return (1);
    }
    else if (ft_strstr(line, "EA"))
    {
        texture->east = extract_texture_path(line);
        return (1);
    }
    // check for color identifier
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


/* extract the player direction */


/* init the player based on the input */


/* main parsing function */
int parse_input(char *file_path, t_texture *texture)
{
    int fd;
    char *line;

    /* validate the input format */
    if (!check_input(file_path))
        return (0);
    /* open file to parse */
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (0);
    /* start parse input */
    line = get_next_line(fd);
    while (line)
    {
        parse_element_line(line, texture);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    /* build the map */

    /* init player */

    return (1);
}

/* cleanup */




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

// test parse_element_line
int main(int ac, char **av)
{
    t_texture *texture;
    
    if (ac != 2)
    {
        printf("Error\nUsage ./cub3D <map .cub>\n");
        return (1);
    }
    texture = malloc(sizeof(t_texture));
    if (!texture)
        return (0);
    ft_memset(texture, 0, sizeof(t_texture));
    
    if (!parse_input(av[1], texture))
        return (0);
    print_texture(texture); //DEBUG
}