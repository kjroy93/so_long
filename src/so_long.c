/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:37:02 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/21 10:36:18 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_init(t_game *game)
{
	game->map.collectibles_counts = 0;
	game->map.exit_counts = 0;
	game->map.height = 0;
	game->map.map_grid = NULL;
	game->map.player_counts = 0;
	game->map.width = 0;
	game->mlx = NULL;
	game->moves = 0;
	game->player_img = NULL;
	game->player_x = 0;
	game->player_y = 0;
	game->points = 0;
	game->screen_h = 0;
	game->screen_w = 0;
}

static void	validate_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		ft_error("Error: no filename added.\n");
	len = ft_strlen(filename);
	if (len < 5)
		ft_error("Error: the filename can not be just .typefile.\n");
	if (ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		ft_error("Error: the name of the file is not valid.\n");
	if (filename[len - 5] == '/')
		ft_error("Error: the file must have a name before .ber.\n");
}

static void	validate_map(t_game **game, t_list **lst, char *file)
{
	bool	answer;

	answer = parse_map(file, &(*game)->map, lst);
	if (!answer)
	{
		if ((*game)->map.map_grid)
			free_map((*game)->map.map_grid);
		free(*game);
		*game = NULL;
		ft_lstclear(lst, free);
		ft_error("Error: the map could not be parsed.\n");
	}
	answer = validate_path(*game);
	if (!answer)
	{
		if ((*game)->map.map_grid)
			free_map((*game)->map.map_grid);
		(*game)->map.map_grid = NULL;
		free(*game);
		*game = NULL;
		ft_lstclear(lst, free);
		ft_error("Error: the map does not have a valid path.\n");
	}
	validate_map_size(*game);
}

int	main(int argc, char **argv)
{
	char	*file;
	t_game	*game;
	t_list	*lst;

	if (argc != 2)
		return (write(2, "Error: not valid amount of arguments.\n", 39), 1);
	file = argv[1];
	validate_extension(file);
	game = malloc(sizeof(t_game));
	if (!game)
		ft_error("Error: allocation failed for game.\n");
	map_init(game);
	lst = NULL;
	mlx_get_monitor_size(0, &game->screen_w, &game->screen_h);
	validate_map(&game, &lst, file);
	game->mlx = mlx_init(game->map.width * TILE,
			game->map.height * TILE, "so_long", true);
	draw_all_textures(game, &game->tx);
	mlx_key_hook(game->mlx, ft_key_hook, game);
	mlx_close_hook(game->mlx, ft_close_window, game);
	mlx_loop(game->mlx);
	clean_exit(game, 0);
	return (0);
}
