/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:53:10 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/21 00:17:04 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_map(t_game *game, t_textures *tx)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.map_grid[y])
	{
		x = 0;
		while (game->map.map_grid[y][x])
		{
			mlx_image_to_window(game->mlx, tx->grass,
				(x * TILE), (y * TILE));
			if (game->map.map_grid[y][x] == '1')
				mlx_image_to_window(game->mlx, tx->wall,
					(x * TILE), (y * TILE));
			else if (game->map.map_grid[y][x] == 'E')
				mlx_image_to_window(game->mlx, tx->exit,
					(x * TILE), (y * TILE));
			else if (game->map.map_grid[y][x] == 'C')
				mlx_image_to_window(game->mlx, tx->collect,
					(x * TILE), (y * TILE));
			x++;
		}
		y++;
	}
}

static void	draw_player(t_game *game, t_textures *tx)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.map_grid[y])
	{
		x = 0;
		while (game->map.map_grid[y][x])
		{
			if (game->map.map_grid[y][x] == 'P')
			{
				mlx_image_to_window(game->mlx, tx->player,
					(x * TILE), (y * TILE));
				game->player_x = x;
				game->player_y = y;
				game->player_img = tx->player;
				break ;
			}
			x++;
		}
		y++;
	}
}

static mlx_image_t	*load_png(t_game *game, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_printf("Error; texture load failed: %s.\n", path);
		clean_exit(game, 0);
	}
	image = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
	{
		ft_printf("Error: image load failed: %s.\n", path);
		clean_exit(game, 0);
	}
	return (image);
}

void	disable_collectible(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < (game->map.collectibles_counts))
	{
		if (((game->tx.collect->instances[i].x) == (x * TILE))
			&& ((game->tx.collect->instances[i].y) == (y * TILE)))
		{
			game->tx.collect->instances[i].enabled = false;
			return ;
		}
		i++;
	}
}

void	draw_all_textures(t_game *game, t_textures *tx)
{
	tx->grass = load_png(game, "textures/tileset.png");
	tx->wall = load_png(game, "textures/wall.png");
	tx->exit = load_png(game, "textures/exit.png");
	tx->collect = load_png(game, "textures/collectible.png");
	tx->player = load_png(game, "textures/player.png");
	draw_map(game, tx);
	draw_player(game, tx);
}
