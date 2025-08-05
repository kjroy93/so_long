/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:09:45 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/05 20:51:11 by kmarrero         ###   ########.fr       */
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

void	validate_walls(t_list *lines, t_map *map, int map_len)
{
	t_list	*tmp;
	char	*line;

	tmp = lines;
	line = (char *)tmp->content;
	while (*line)
	{
		if (*line++ != '1')
			ft_error("Error: The map is open from the upside");
	}
	while (tmp->next && tmp->next->next)
	{
		line = (char *)tmp->next->content;
		if (line[0] != '1' || line[map_len - 1] != '1')
			ft_error("Error: The map is open on the sides");
		tmp = tmp->next;
	}
	line = (char *)tmp->next->content;
	while (*line)
	{
		if (*line != '1')
			ft_error("Error: The map is open from the bottom");
		line++;
	}
}

void	update_create(t_map *map, int line_count, t_list *lines)
{
	if (map->player_counts != 1 || map->exit_counts < 1
		|| map->collectibles_counts < 1)
		ft_error("Error: The map is invalid");
	map->height = line_count;
	map->grid = create_array(lines);
	if (!map->grid)
		ft_error("Error: Memory allocation failed for map grid");
	ft_lstclear(&lines, free);
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
	else if (len != map->width)
		ft_error("Error: the map is not a square");
}
