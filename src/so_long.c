/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:37:02 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/14 18:27:31 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_init(t_map *map)
{
	map->collectibles_counts = 0;
	map->player_counts = 0;
	map->exit_counts = 0;
	map->height = 0;
	map->width = 0;
	map->grid = NULL;
}

int	main(int argc, char **argv)
{
	char	*filepath;
	bool	answer;
	t_game	*game;
	t_list	*lst;

	if (argc < 2)
		return (write(2, "\n", 1), 1);
	filepath = check_file(argv);
	game = malloc(sizeof(t_game));
	if (!game)
		ft_error("Error: allocation failed for game.\n");
	lst = NULL;
	map_init(&game->map);
	answer = parse_map(filepath, &game->map, &lst);
	free(filepath);
	if (!answer)
	{
		free(game);
		return (1);
	}
	answer = validate_path(game);
	if (!answer)
	{
		free_grid(game->map.grid);
		game->map.grid = NULL;
		free(game);
		return (1);
	}
	game->points = 0;
	game->moves = 0;
	game->mlx = mlx_init(game->map.width * TILE, game->map.height * TILE, "so_long", true);
	mlx_get_monitor_size(0, &game->screen_w, &game->screen_h);
	mlx_key_hook(game->mlx, ft_key_hook, game);
	mlx_close_hook(game->mlx, ft_close_window, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	clean_exit(game, 0);
	free(game);
	return (0);
}
