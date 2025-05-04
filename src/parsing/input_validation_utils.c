/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhu <czhu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:39:32 by auzou             #+#    #+#             */
/*   Updated: 2025/05/04 13:50:29 by czhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

char	*ft_strstr(const char *big, char *small)
{
	int	i;
	int	j;

	i = 0;
	if (!small)
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (big[i + j] && small[j]
			&& big[i + j] == small[j])
			j++;
		if (!small[j])
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	is_valid_rgb(char *line)
{
	int	i;
	int	count;
	int	value;

	i = 0;
	count = 0;
	while (line[i] && (line[i] == 'F' || line[i] == 'C' || is_space(line[i])))
		i++;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (0);
		if (ft_isdigit(line[i]))
		{
			value = ft_atoi(&line[i]);
			if (value < 0 || value > 255)
				return (0);
			count++;
			while (line[i] && ft_isdigit(line[i]))
				i++;
		}
		else
			i++;
	}
	return (count == 3);
}

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
