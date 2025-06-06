/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:53:14 by czhu              #+#    #+#             */
/*   Updated: 2025/05/05 17:35:55 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

void	print_ascii(void)
{
	ft_printf("\n");
	ft_printf("\tW: Forward\t");
	ft_printf("\tS: Backward\n");
	ft_printf("\tA: Left\t\t");
	ft_printf("\tD: Right\n");
	ft_printf("\t<-: Turn left\t");
	ft_printf("\t->: Turn right\n");
	ft_printf("\n");
}

/* click cross to close the win */
int	cross_close(t_game *game)
{
	(void)game;
	cleanup(game);
	exit(0);
}
