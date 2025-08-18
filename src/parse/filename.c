/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:30:24 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/18 19:36:45 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*check_file(char **argv)
{
	char	*filepath;
	char	*file;
	size_t	len;

	file = argv[1];
	if (!file)
		ft_error("Error: no file provided.\n");
	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".ber", 4) != 0)
		ft_error("Error: map name is not valid.\n");
	filepath = malloc((ft_strlen("src/maps/")) + ft_strlen(file) + 1);
	if (!filepath)
		ft_error("Error: allocation failed in filepath.\n");
	ft_strlcpy(filepath, "src/maps/", ft_strlen("src/maps/") + 1);
	ft_strlcat(filepath, file, ft_strlen("src/maps/") + ft_strlen(file) + 1);
	return (filepath);
}
