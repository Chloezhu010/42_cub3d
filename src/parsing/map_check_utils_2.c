/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:01:17 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 17:02:10 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

int	validate_map(t_map *map)
{
	if (!process_player(map))
		return (0);
	if (!is_map_closed(map))
		return (0);
	return (1);
}
