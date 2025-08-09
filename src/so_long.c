/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:37:02 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/09 22:24:41 by kmarrero         ###   ########.fr       */
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
	char	filepath[512];
	char	*file;
	t_map	*map;
	t_list	*lst;

	map = malloc(sizeof(t_map));
	lst = NULL;
	if (argc < 2)
		return (write(1, "\n", 1), 1);
	map_init(map);
	file = argv[1];
	ft_strlcpy(filepath, "src/maps/", sizeof(filepath));
	ft_strlcat(filepath, file, sizeof(filepath));
	bool answer = parse_map(filepath, map, &lst);
	if (!answer)
	{
		free(map);
		return (1);
	}
	free_grid(map->grid);
	free(map);
	return (0);
}
