/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:18:18 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 17:46:55 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

static int	init_mlx_components(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("mlx_init failed\n");
		return (0);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
	{
		ft_printf("mlx_new_window failed\n");
		return (0);
	}
	return (1);
}

static int	init_image_components(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		ft_printf("mlx_new_image failed\n");
		return (0);
	}
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
	{
		ft_printf("mlx_get_data_addr failed\n");
		return (0);
	}
	return (1);
}

void	init_game(t_game *game)
{
	if (!init_mlx_components(game))
	{
		cleanup(game);
		exit(1);
	}
	if (!init_image_components(game))
	{
		cleanup(game);
		exit(1);
	}
	if (!load_all_textures(game))
	{
		ft_printf("Failed to load textures\n");
		cleanup(game);
		exit(1);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
