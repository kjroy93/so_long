/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:37:02 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/11 15:40:35 by kjroy93          ###   ########.fr       */
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
	t_map	*map;
	t_list	*lst;

	if (argc < 2)
		return (write(1, "\n", 1), 1);
	filepath = check_file(argv);
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error("Error: allocation failed for map.\n");
	lst = NULL;
	map_init(map);
	answer = parse_map(filepath, map, &lst);
	free(filepath);
	if (!answer)
	{
		free(map);
		return (1);
	}
	free_grid(map->grid);
	free(map);
	return (0);
}
