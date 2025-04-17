/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:11 by czhu              #+#    #+#             */
/*   Updated: 2025/04/17 20:06:54 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* helper function: check texture & handle duplication */
void    check_NSWE_texture(char *line, t_component *ctx)
{
    if (ft_strnstr(line, "NO ", 3) && check_texture_extension(line))
    {
        if (ctx->has_north)
            ctx->invalid = 1;
        ctx->has_north = 1;
    }
    else if (ft_strnstr(line, "SO ", 3) && check_texture_extension(line))
    {
        if (ctx->has_south)
            ctx->invalid = 1;
        ctx->has_south = 1;
    }
    else if (ft_strnstr(line, "WE ", 3) && check_texture_extension(line))
    {
        if (ctx->has_west)
            ctx->invalid = 1;
        ctx->has_west = 1;
    }
    else if (ft_strnstr(line, "EA ", 3) && check_texture_extension(line))
    {
        if (ctx->has_east)
            ctx->invalid = 1;
        ctx->has_east = 1;
    }
}

/* helper function: check FC texture & handle duplication */
void    check_FC_texture(char *line, t_component *ctx)
{
    if (ft_strnstr(line, "F ", 2))
    {
        if (ctx->has_floor)
            ctx->invalid = 1;
        ctx->has_floor = is_valid_rgb(line);
    }
    else if (ft_strnstr(line, "C ", 2))
    {
        if (ctx->has_ceiling)
            ctx->invalid = 1;
        ctx->has_ceiling = is_valid_rgb(line);
    }
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

/* check map if it
    - can open properly
    - has all the components: NSWE, FC, map
    - return 1 if valid, return 0 if not
*/
int check_map_component(char *file_path)
{
    int fd;
    char    *line;
    t_component ctx;
    
    /* init ctx */
    ft_memset(&ctx, 0, sizeof(t_component));
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
    /* check if all components are incl */
    return (ctx.has_north && ctx.has_south && ctx.has_west && ctx.has_east
        && ctx.has_ceiling && ctx.has_floor && ctx.has_map && !ctx.invalid);
}

// test check_map_component
int main(int ac, char **av)
{
    (void)ac;

    printf("%d\n", check_map_component(av[1]));
}
// TODO: good/square_map.cub