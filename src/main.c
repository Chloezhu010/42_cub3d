/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:40:37 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 17:47:17 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

static int	check_arguments(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nUsage ./cub3D <map .cub>\n");
		return (0);
	}
	if (!check_file_extension(av[1]))
	{
		printf("Error\nFile must be .cub file\n");
		return (0);
	}
	if (!check_input(av[1]))
	{
		printf("Error\nInvalid input\n");
		return (0);
	}
	return (1);
}

static t_game	*initialize_game_data(char *map_path)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		printf("Error: Malloc failed\n");
		return (NULL);
	}
	ft_memset(game, 0, sizeof(t_game));
	if (!parse_input(map_path, &game->map, &game->textures, &game->player))
	{
		free(game);
		return (NULL);
	}
	return (game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (!check_arguments(ac, av))
		return (1);
	game = initialize_game_data(av[1]);
	if (!game)
		return (1);
	init_game(game);
	print_ascii();
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, cross_close, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
