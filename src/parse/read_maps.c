/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:46:24 by kjroy93           #+#    #+#             */
/*   Updated: 2025/08/05 12:48:31 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static void	s_init(t_map *map)
{
	map->collectibles_counts = 0;
	map->player_counts = 0;
	map->exit_counts = 0;
	map->height = 0;
	map->width = 0;
	map->grid = NULL;
}

static void	read_maps(int fd, t_map *map, t_list **lines)
{
	int		line_count;
	char	*line;
	char	*dup;

	line_count = 0;
	line = get_next_line(fd);
	if (!line)
		return ;
	while (line != NULL)
	{
		rectangular_map_parse(map, line);
		count_elements(map, line);
		dup = ft_strdup(line);
		if (!dup)
			ft_error("Error: The line was not duplicated in read_maps");
		ft_lstadd_back(lines, ft_lstnew(dup));
		line_count++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	parse_map(t_map *map, const char *filename)
{
	t_list	*lines;
	int		fd;

	s_init(map);
	lines = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Error: File could not be opened");
	read_maps(fd, map, &lines);
	update_create(map, ft_lstsize(lines), lines);
}
