/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:29:31 by kjroy93           #+#    #+#             */
/*   Updated: 2025/08/05 00:31:38 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

void	s_init(t_map *map)
{
	map->collectibles_counts = 0;
	map->player_counts = 0;
	map->exit_counts = 0;
	map->width = 0;
}
