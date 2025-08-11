/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:37:02 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/11 20:42:15 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

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
	free_grid(game->map.grid);
	free(game);
	return (0);
}
