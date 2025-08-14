/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:14:10 by kjroy93           #+#    #+#             */
/*   Updated: 2025/08/14 17:46:00 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	game->player_x = x;
	game->player_y = y;
	game->moves++;
	ft_printf("Moves: %i\n", game->moves);
	if ((game->map.grid[y][x] == 'E'
		&& game->points == game->map.collectibles_counts))
	{
		ft_printf("WINNER\n");
		clean_exit(game, 0);
	}
}

void	ft_close_window(void *param)
{
	t_game *game;

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
	else if (keydata.key == MLX_KEY_W)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keydata.key == MLX_KEY_S)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keydata.key == MLX_KEY_A)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keydata.key == MLX_KEY_D)
		move_player(game, game->player_x + 1, game->player_y);
}
