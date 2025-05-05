/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:28:37 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 17:44:13 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* parse RBG for floor & ceiling */
static void	skip_identifiers(char *line, int *i)
{
	while (is_space(line[*i]))
		(*i)++;
	while (line[*i] && (line[*i] == 'F'
			|| line[*i] == 'C' || is_space(line[*i])))
		(*i)++;
	while (is_space(line[*i]))
		(*i)++;
}

static int	get_color_value(char *line, int *i, int *comma)
{
	int	value;

	value = ft_atoi(&line[*i]);
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	if (line[*i] == ',')
	{
		(*i)++;
		(*comma)++;
	}
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	return (value);
}

int	parse_rgb(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;
	int	comma;

	i = 0;
	comma = 0;
	skip_identifiers(line, &i);
	r = get_color_value(line, &i, &comma);
	g = get_color_value(line, &i, &comma);
	b = ft_atoi(&line[i]);
	return ((r << 16) | (g << 8) | b);
}
