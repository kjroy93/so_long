/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:57:26 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/11 18:49:09 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static void	remove_newline(char *line)
{
	size_t	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static bool	validate_line_not_empty(char *line)
{
	if (!line || line[0] == '\0')
		return (false);
	return (true);
}

static bool	read_map_lines(int fd, t_map *map, t_list **lines)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		remove_newline(line);
		if (!validate_line_not_empty(line))
			return (error_free(line, fd, "Error: No line\n"), false);
		if (map->width == 0)
			map->width = (int)ft_strlen(line);
		else if (((int)ft_strlen(line)) != map->width)
			return (error_free(line, fd, "Error: no parallelogram.\n"), false);
		if (!count_elements(map, line))
			return (error_free(line, fd, "Error: wrong element\n"), false);
		if (!create_lst(lines, line, &map->height))
			return (error_free(line, fd, "Error: array line NULL\n"), false);
		free(line);
		line = get_next_line(fd);
	}
	return (*lines != NULL);
}

static bool	validate_walls(t_list **lines, t_map *map)
{
	t_list	*tmp;
	char	*line;

	tmp = *lines;
	line = (char *)tmp->content;
	while (*line)
	{
		if (*line++ != '1')
			return (ft_printf("Error: Map is open from the top\n"), false);
	}
	while (tmp->next && tmp->next->next)
	{
		line = (char *)tmp->next->content;
		if (line[0] != '1' || line[map->width - 1] != '1')
			return (ft_printf("Error: Map is open on the sides\n"), false);
		tmp = tmp->next;
	}
	line = (char *)tmp->next->content;
	while (*line)
	{
		if (*line++ != '1')
			return (ft_printf("Error: Map is open from the bottom\n"), false);
	}
	return (true);
}

bool	parse_map(char *file, t_map *map, t_list **lst)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error: file could not be opened"), false);
	if (!read_map_lines(fd, map, lst))
	{
		close(fd);
		return (cleanup_and_return(lst, map, false));
	}
	if (!validate_walls(lst, map))
	{
		close(fd);
		return (cleanup_and_return(lst, map, false));
	}
	if (!content_create(map, *lst))
	{
		close(fd);
		return (cleanup_and_return(lst, map, false));
	}
	ft_lstclear(lst, free);
	return (true);
}
