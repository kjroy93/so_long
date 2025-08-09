/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:26:55 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/09 22:15:16 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

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
	free(line);
	close(fd);
	get_next_line(-1);
	ft_printf(message);
}

void	ft_error(char *message)
{
	write(2, "Error\n", 6);
	write(1, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
