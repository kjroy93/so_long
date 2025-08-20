/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:40:02 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/19 20:22:29 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_move(t_game *game, int x, int y)
{
	game->player_x = x;
	game->player_y = y;
	game->tx.player->instances[0].x = x * TILE;
	game->tx.player->instances[0].y = y * TILE;
	game->moves++;
}

static void	move_player(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == '1')
		return ;
	if (game->map.grid[y][x] == 'C')
	{
		game->map.grid[y][x] = '0';
		disable_collectible(game, x, y);
		game->points++;
	}
	render_move(game, x, y);
	ft_printf("Moves: %i\n", game->moves);
	if (game->map.grid[y][x] == 'E'
		&& game->points == game->map.collectibles_counts)
	{
		ft_printf("WINNER!\n");
		clean_exit(game, 0);
	}
}

void	ft_close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clean_exit(game, 0);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		clean_exit(game, 0);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		move_player(game, game->player_x + 1, game->player_y);
}
