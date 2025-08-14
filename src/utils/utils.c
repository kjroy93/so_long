/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:26:55 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/14 17:27:23 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_grid(char **grid)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

bool	cleanup_and_return(t_list **lst, t_map *map, bool status)
{
	if (lst && *lst)
		ft_lstclear(lst, free);
	if (map && map->grid)
		free_grid(map->grid);
	return (status);
}

void	error_free(char *line, int fd, char *message)
{
	close(fd);
	free(line);
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
	if (game->map.grid)
		free_grid(game->map.grid);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	exit(code);
}
