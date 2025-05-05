/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:34:56 by your_username    #+#    #+#             */
/*   Updated: 2025/05/02 12:34:56 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* 加载XPM文件到图像结构 */
int	load_texture(t_game *game, t_img *img, char *path)
{
	if (!path)
		return (0);
	img->img = (mlx_xpm_file_to_image(game->mlx, path,
				&img->width, &img->height));
	if (!img->img)
	{
		printf("Error loading texture: %s\n", path);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(game->mlx, img->img);
		img->img = NULL;
		return (0);
	}
	return (1);
}

/* 加载所有纹理 */
int	load_all_textures(t_game *game)
{
	init_img(&game->textures.north_img);
	init_img(&game->textures.south_img);
	init_img(&game->textures.west_img);
	init_img(&game->textures.east_img);
	if (!load_texture(game, &game->textures.north_img
			, game->textures.north_path))
		return (0);
	if (!load_texture(game, &game->textures.south_img
			, game->textures.south_path))
		return (0);
	if (!load_texture(game, &game->textures.west_img, game->textures.west_path))
		return (0);
	if (!load_texture(game, &game->textures.east_img, game->textures.east_path))
		return (0);
	return (1);
}

/* 清理纹理资源 */
void	cleanup_texture(t_game *game)
{
	if (game->textures.north_img.img)
		mlx_destroy_image(game->mlx, game->textures.north_img.img);
	if (game->textures.south_img.img)
		mlx_destroy_image(game->mlx, game->textures.south_img.img);
	if (game->textures.west_img.img)
		mlx_destroy_image(game->mlx, game->textures.west_img.img);
	if (game->textures.east_img.img)
		mlx_destroy_image(game->mlx, game->textures.east_img.img);
}

/* 从纹理获取像素颜色 */
int	get_texture_pixel(t_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= img->width)
		x = img->width - 1;
	if (y >= img->height)
		y = img->height - 1;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(int *)pixel;
	return (color);
}

/* 根据墙面类型获取对应纹理 */
t_img	*get_wall_texture(t_game *game, t_wall_side side)
{
	if (side == WALL_NORTH)
		return (&game->textures.north_img);
	else if (side == WALL_SOUTH)
		return (&game->textures.south_img);
	else if (side == WALL_EAST)
		return (&game->textures.east_img);
	else if (side == WALL_WEST)
		return (&game->textures.west_img);
	else
		return (&game->textures.north_img);
}
