/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:11 by czhu              #+#    #+#             */
/*   Updated: 2025/04/23 18:38:41 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* helper function: check texture & handle duplication */
void    check_NSWE_texture(char *line, t_component *ctx)
{
    if (ft_strstr(line, "NO") && check_texture_extension(line))
    {
        if (ctx->has_north)
            ctx->invalid = 1;
        ctx->has_north = 1;
    }
    else if (ft_strstr(line, "SO") && check_texture_extension(line))
    {
        if (ctx->has_south)
            ctx->invalid = 1;
        ctx->has_south = 1;
    }
    else if (ft_strstr(line, "WE") && check_texture_extension(line))
    {
        if (ctx->has_west)
            ctx->invalid = 1;
        ctx->has_west = 1;
    }
    else if (ft_strstr(line, "EA") && check_texture_extension(line))
    {
        if (ctx->has_east)
            ctx->invalid = 1;
        ctx->has_east = 1;
    }
}

/* helper function: check FC texture & handle duplication */
void    check_FC_texture(char *line, t_component *ctx)
{
    if (ft_strstr(line, "F"))
    {
        if (ctx->has_floor)
            ctx->invalid = 1;
        ctx->has_floor = is_valid_rgb(line);
    }
    else if (ft_strstr(line, "C"))
    {
        if (ctx->has_ceiling)
            ctx->invalid = 1;
        ctx->has_ceiling = is_valid_rgb(line);
    }
}

/* add a line to the map grid and update width, height */
int add_line_to_map(t_map *map, char *line)
{
    char    **new_grid;
    int i;

    /* allocate new grid with + 1 slot */
    new_grid = (char **)ft_calloc(map->height + 2, sizeof(char *));
    if (!new_grid)
        return (0);
    /* copy existing grid */
    i = 0;
    while (i < map->height)
    {
        new_grid[i] = map->grid[i];
        i++;
    }
    /* add new line */
    new_grid[i] = ft_strdup(line);
    if (!new_grid[i])
    {
        free(new_grid);
        return (0);
    }
    /* update dimention */
    map->height++;
    if ((int)ft_strlen(line) > map->width)
        map->width = (int)ft_strlen(line);
    /* replace old grid */
    if (map->grid)
        free(map->grid);
    map->grid = new_grid;
    return (1);
}

/* helper function: process a line of the input */
void    process_line(char *line, t_component *ctx)
{
    if (is_empty_line(line))
    {
        /* if map already started and see the empty line, flag it */
        if (ctx->map_started)
            ctx->empty_after_map = 1;
    }
    /* check map */
    else if (is_map_line(line))
    {
        ctx->has_map = 1;
        /* if see map content, then empty line, then map content, invalid */
        if (ctx->map_started && ctx->empty_after_map)
            ctx->invalid = 1;
        ctx->map_started = 1;
        /* add the line to the current map grid */
        if (!ctx->invalid && !add_line_to_map(&ctx->map, line))
            ctx->invalid = 1;
    }
    /* if map has started, and it's non-map non-empty line, then invalid */
    else if (ctx->map_started)
        ctx->invalid = 1;
    else
    {
        check_NSWE_texture(line, ctx);
        check_FC_texture(line, ctx);
    }
}

/* for DEBUG */
void    print_map(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->height)
    {
        j = 0;
        while (j < map->width)
        {
            printf("%c", map->grid[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

/* check map if it
    - can open properly
    - has all the components: NSWE, FC, map
    - return 1 if valid, return 0 if not
*/
int check_input_component(char *file_path)
{
    int fd;
    char    *line;
    t_component ctx;
    
    /* init ctx */
    ft_memset(&ctx, 0, sizeof(t_component));
    ctx.map.grid = NULL;
    ctx.map.width = 0;
    ctx.map.height = 0;
    /* check file extension */
    if (!check_file_extension(file_path))
        return (0);
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (0);
    /* read line by line and check for componenets */
    line = get_next_line(fd);
    while (line)
    {
        process_line(line, &ctx);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    // print_map(&ctx.map); //DEBUG
    if (!validate_map(&ctx.map))
        return (0);
    /* check if all components are incl */
    return (ctx.has_north && ctx.has_south && ctx.has_west && ctx.has_east
        && ctx.has_ceiling && ctx.has_floor && ctx.has_map && !ctx.invalid);
}


// // test check_NSWE_texture
// int main(int ac, char **av)
// {
//     t_component ctx;
//     (void)ac;
//     ft_memset(&ctx, 0, sizeof(t_component));
//     check_NSWE_texture(av[1], &ctx);
//     printf("%d\n", ctx.has_west);
//     printf("%d\n", ctx.has_east);
//     printf("%d\n", ctx.has_north);
//     printf("%d\n", ctx.has_south);
// }


// test check_input_component
int main(int ac, char **av)
{
    (void)ac;
    printf("%d\n", check_input_component(av[1]));
}
