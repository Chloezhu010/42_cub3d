/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:30:39 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 17:31:04 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* parse a single line for color or texture info */
static int	handle_texture(char *line, char **path, char *id)
{
	if (ft_strstr(line, id))
	{
		*path = extract_texture_path(line);
		return (1);
	}
	return (0);
}

static int	handle_color(char *line, int *color, char *id)
{
	if (ft_strstr(line, id))
	{
		*color = parse_rgb(line);
		return (1);
	}
	return (0);
}

int	parse_element_line(char *line, t_texture *texture)
{
	if (handle_texture(line, &texture->north_path, "NO"))
		return (1);
	else if (handle_texture(line, &texture->south_path, "SO"))
		return (1);
	else if (handle_texture(line, &texture->west_path, "WE"))
		return (1);
	else if (handle_texture(line, &texture->east_path, "EA"))
		return (1);
	else if (handle_color(line, &texture->floor_color, "F"))
		return (1);
	else if (handle_color(line, &texture->ceiling_color, "C"))
		return (1);
	return (0);
}
