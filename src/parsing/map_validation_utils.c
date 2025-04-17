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

/* check NSWE has the right .xpm extension */
/* TODO: manage textures_forbidden.cub case */
int check_texture_extension(char *texture)
{
    char    *dot;

    dot = ft_strchr(texture, '.');
    if (!dot || ft_strncmp(dot, ".xpm", 4) != 0)
        return (0);
    return (1);
}

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

// // testing check_file_extension
// int main()
// {
//     char *s1 = "test.cub";
//     char *s2 = "test";

//     printf("%d\n", check_file_extension(s1));
//     printf("%d\n", check_file_extension(s2));
// }