/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:46:24 by kjroy93           #+#    #+#             */
/*   Updated: 2025/08/05 01:25:29 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static void	read_maps(int fd, t_map *map, t_list **lines)
{
	int		line_count;
	char	*line;
	char	*dup;

	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		rectangular_map_parse(map, line);
		count_elements(map, line);
		dup = ft_strdup(line);
		if (!dup)
			ft_error("Error: The line was not duplicated in read_maps");
		ft_lstadd_back(lines, ft_lstnew(dup));
		free(line);
		free(dup);
		line_count++;
		line = get_next_line(fd);
	}
	close(fd);
	if (line_count == 0)
		ft_error("Error: the map file was empty");
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
