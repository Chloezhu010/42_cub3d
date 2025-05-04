/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhu <czhu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:18:18 by auzou             #+#    #+#             */
/*   Updated: 2025/05/04 15:05:04 by czhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("mlx_init failed\n");
		cleanup(game);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
	{
		ft_printf("mlx_new_window failed\n");
		cleanup(game);
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		ft_printf("mlx_new_image failed\n");
		cleanup(game);
		exit(1);
	}
	game->data = mlx_get_data_addr(game->img, &game->bpp
			, &game->size_line, &game->endian);
	if (!game->data)
	{
		ft_printf("mlx_get_data_addr failed\n");
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

/* updated main */
int	main(int ac, char **av)
{
	t_game  *game;

	if (ac != 2)
	{
		printf("Error\nUsage ./cub3D <map .cub>\n");
		return (1);
	}
	if (!check_file_extension(av[1]))
	{
		printf("Error\nFile must be .cub file\n");
		return (1);
	}
	if (!check_input(av[1]))
	{
		printf("Error\nInvalid input\n");
		return (1);
	}
	game = malloc(sizeof(t_game));
	if (!game)
	{
		printf("Error: Malloc failed\n");
		return (1);
	}
	ft_memset(game, 0, sizeof(t_game));
	if (!parse_input(av[1], &game->map, &game->textures, &game->player))
		return (0);
	// print_texture(&game->textures);//DEBUG
	// print_map(&game->map);//DEBUG
	// print_player(&game->player);//DEBUG
	init_game(game);
	print_ascii();
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
	mlx_hook(game->win, 3, 1L<<1, key_release, game);
	mlx_hook(game->win, 17, 0, cross_close, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
	return (0);
}