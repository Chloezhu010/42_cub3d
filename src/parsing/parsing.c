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
    // skip identifier
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



/* parse a single line for color or texture info */


/* fill the map structure */


/* extract the player direction */


/* init the player based on the input */


/* main parsing function */


/* cleanup */


// testing extract_texture_path
int main()
{
    char *line1 = "NO textures/test/north.xpm";
    char *line2 = "   EA      textures/test/east.xpm   ";

    printf("line1: %s\n", extract_texture_path(line1));
    printf("line2: %s\n", extract_texture_path(line2));
}