/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:26:55 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/21 14:51:58 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

bool	cleanup_and_return(t_list **lst, t_map *map, bool status)
{
	if (lst && *lst)
		ft_lstclear(lst, free);
	if (map && map->map_grid)
		free_map(map->map_grid);
	return (status);
}

void	error_free(char *line, int fd, char *message)
{
	free(line);
	close(fd);
	get_next_line(-1);
	ft_printf(message);
}

void	ft_error(char *message)
{
	write(2, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

void	clean_exit(t_game *game, int code)
{
	if (game->map.map_grid)
		free_map(game->map.map_grid);
	if (game->tx.collect)
		mlx_delete_image(game->mlx, game->tx.collect);
	if (game->tx.player)
		mlx_delete_image(game->mlx, game->tx.player);
	if (game->tx.exit)
		mlx_delete_image(game->mlx, game->tx.exit);
	if (game->tx.grass)
		mlx_delete_image(game->mlx, game->tx.grass);
	if (game->tx.wall)
		mlx_delete_image(game->mlx, game->tx.wall);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	free(game);
	exit(code);
}
