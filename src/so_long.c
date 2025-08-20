/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:37:02 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/20 22:49:49 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_init(t_game *game)
{
	game->map.collectibles_counts = 0;
	game->map.player_counts = 0;
	game->map.exit_counts = 0;
	game->map.height = 0;
	game->map.width = 0;
	game->map.grid = NULL;
	game->points = 0;
	game->moves = 0;
}

static void	validate_map(t_game **game, t_list **lst, char *file)
{
	bool	answer;

	answer = parse_map(file, &(*game)->map, lst);
	if (!answer)
	{
		if ((*game)->map.grid)
			free_grid((*game)->map.grid);
		free(*game);
		*game = NULL;
		ft_lstclear(lst, free);
		ft_error("Error: the map could not be parsed.\n");
	}
	answer = validate_path(*game);
	if (!answer)
	{
		if ((*game)->map.grid)
			free_grid((*game)->map.grid);
		(*game)->map.grid = NULL;
		free(*game);
		*game = NULL;
		ft_lstclear(lst, free);
		ft_error("Error: the map does not have a valid path.\n");
	}
}

int	main(int argc, char **argv)
{
	char	*file;
	t_game	*game;
	t_list	*lst;

	if (argc != 2)
		return (write(2, "Error: not valid amount of arguments.\n", 39), 1);
	game = malloc(sizeof(t_game));
	if (!game)
		ft_error("Error: allocation failed for game.\n");
	lst = NULL;
	map_init(game);
	file = argv[1];
	validate_map(&game, &lst, file);
	game->mlx = mlx_init(game->map.width * TILE,
			game->map.height * TILE, "so_long", true);
	mlx_get_monitor_size(0, &game->screen_w, &game->screen_h);
	draw_all_textures(game, &game->tx);
	mlx_key_hook(game->mlx, ft_key_hook, game);
	mlx_close_hook(game->mlx, ft_close_window, game);
	mlx_loop(game->mlx);
	return (0);
}
