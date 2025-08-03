/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:47:10 by kjroy93           #+#    #+#             */
/*   Updated: 2025/08/03 14:49:59 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*update_line(char *chunk)
{
	char	*result;
	size_t	len;
	size_t	i;

	if (!chunk)
		return (NULL);
	i = 0;
	len = ft_strlen(chunk);
	while (chunk[i] && chunk[i] != '\n')
		i++;
	if (chunk[i] == '\n')
	{
		result = ft_substr(chunk, i + 1, len - (i + 1));
		return (result);
	}
	else
		return (NULL);
}

static char	*extract_line(char *chunk)
{
	char	*result;
	size_t	i;

	i = 0;
	while (chunk[i] && chunk[i] != '\n')
		i++;
	if (chunk[i] == '\n')
	{
		result = ft_substr(chunk, 0, i + 1);
		return (result);
	}
	else
	{
		result = ft_strdup(chunk);
		return (result);
	}
}

static char	*read_and_accumulate(int fd, char *chunk, char *buffer)
{
	ssize_t	bytes;
	char	*tmp;

	bytes = 0;
	while (!ft_strchr(chunk, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		if (!chunk)
			chunk = ft_strdup("");
		tmp = ft_strjoin(chunk, buffer);
		free(chunk);
		chunk = tmp;
	}
	free(buffer);
	if (bytes < 0)
	{
		free(chunk);
		return (NULL);
	}
	return (chunk);
}

char	*get_next_line(int fd)
{
	static char	*chunk;
	char		*line;
	char		*tmp;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	chunk = read_and_accumulate(fd, buffer, chunk);
	if (!chunk)
		return (NULL);
	if (chunk[0] == '\0')
	{
		free(chunk);
		chunk = NULL;
		return (NULL);
	}
	line = extract_line(chunk);
	tmp = update_line(chunk);
	chunk = tmp;
	return (line);
}
