/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playable_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:14:59 by kjroy93           #+#    #+#             */
/*   Updated: 2025/08/11 19:53:04 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (game->map.grid[i])
	{
		copy[i] = ft_strdup(game->map.grid[i]);
		if (!copy)
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

static void	find_player(char **copy, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (copy[y])
	{
		x = 0;
		while (copy[x])
		{
			if (copy[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	flood_fill(char **copy, int x, int y, t_game *game)
{
	if ((x < 0 || y < 0 ) || (x >= game->map.width || y >= game->map.height))
		return ;
	if (copy[y][x] == '1' || copy[y][x] == 'V')
		return ;
	copy[y][x] = 'V';
	flood_fill(copy, x + 1, y, game);
	flood_fill(copy, x - 1, y, game);
	flood_fill(copy, x, y + 1, game);
	flood_fill(copy, x, y - 1, game);
}

static bool	map_playable(char **copy)
{
	int	x;
	int	y;

	y = 0;
	while (copy[y])
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'C' || copy[y][x] == 'E')
			{
				ft_printf("Error: some objects are unreachable.\n");
				return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_path(t_game *game)
{
	char	**copy;

	copy = copy_map(game);
	if (!copy)
		return (false);
	find_player(copy, game);
	flood_fill(copy, game->player_x, game->player_y, game);
	if (!map_playable(copy))
	{
		ft_printf("Error: The map is not playable.\n");
		free_grid(copy);
		return (false);
	}
	free_grid(copy);
	return (true);
}
