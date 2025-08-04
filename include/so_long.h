/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:14:00 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/05 00:48:06 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_map
{
	int		collectibles_counts;
	int		player_counts;
	int		exit_counts;
	int		height;
	int		width;
	char	**grid;
}	t_map;

void	ft_error(const char *message);
void	parse_map(t_map *map, const char *filename);
void	s_init(t_map *map);
char	**create_array(t_list *list);
void	update_create(t_map *map, int line_count, t_list *lines);
void	count_elements(t_map *map, char *line);
void	rectangular_map_parse(t_map *map, char *line);

#endif