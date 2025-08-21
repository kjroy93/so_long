/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:09:45 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/21 11:58:10 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	count_elements(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'P')
			map->player_counts++;
		else if (line[i] == 'E')
			map->exit_counts++;
		else if (line[i] == 'C')
			map->collectibles_counts++;
		else if (line[i] != '0' && line[i] != '1')
		{
			ft_printf("Error: the map content is not valid\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	create_lst(t_list **nodes, char *line, int *count)
{
	char	*content;
	t_list	*node;

	content = ft_strdup(line);
	if (!content)
		return (false);
	node = ft_lstnew(content);
	if (!node)
	{
		free(content);
		ft_lstclear(nodes, free);
		return (false);
	}
	ft_lstadd_back(nodes, node);
	(*count)++;
	return (true);
}

char	**create_array(t_list *list)
{
	char	**array;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(list);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	while (list)
	{
		array[i++] = ft_strdup((char *)list->content);
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

void	validate_map_size(t_game *game)
{
	int	screen_w;
	int	screen_h;

	screen_w = game->map.width * TILE;
	screen_h = game->map.height * TILE;
	if (game->screen_w == 0 && game->screen_h == 0)
	{
		game->screen_w = 1920;
		game->screen_h = 1080;
	}
	if (screen_w > game->screen_w || screen_h > game->screen_h)
	{
		ft_printf("Error: The map is too big.\n");
		clean_exit(game, 1);
	}
}

bool	create_map(t_map *map, t_list *lines)
{
	if (map->player_counts != 1 || map->exit_counts < 1
		|| map->collectibles_counts < 1)
	{
		ft_printf("Error: missing element.\n");
		return (false);
	}
	map->map_grid = create_array(lines);
	if (!map->map_grid)
		return (false);
	return (true);
}
