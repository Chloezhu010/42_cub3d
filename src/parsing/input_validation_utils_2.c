/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:54:20 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 17:02:27 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	dot = ft_strchr(filename, '.');
	if (!dot || ft_strncmp(dot, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	check_texture_extension(char *texture)
{
	char	*dot;

	dot = ft_strchr(texture, '.');
	if (!dot || ft_strncmp(dot, ".xpm", 4) != 0)
		return (0);
	return (1);
}

/* helper function: check texture & handle duplication */
void	check_nswe_texture(char *line, t_component *ctx)
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
