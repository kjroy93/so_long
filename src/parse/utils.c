/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:48:18 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/05 00:47:06 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

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

void	update_create(t_map *map, int line_count, t_list *lines)
{
	map->height = line_count;
	map->grid = create_array(lines);
	if (!map->grid)
		ft_error("Error: Memory allocation falied for map grid");
	ft_lstclear(&lines, free);
	if (map->player_counts != 1 || map->exit_counts < 1 ||
			map->collectibles_counts < 1)
			ft_error("Error: The map is invalid");
}

void	count_elements(t_map *map, char *line)
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
			ft_error("Error: non valid character");
		i++;
	}
}

void	rectangular_map_parse(t_map *map, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	len = ft_strlen(line);
	if (map->width == 0)
		map->width = len;
	else if(len != map->width)
		ft_error("Error: The map is not a square");
}
