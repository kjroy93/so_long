/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarrero <kmarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:25:07 by kmarrero          #+#    #+#             */
/*   Updated: 2025/08/05 19:26:39 by kmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *message)
{
	write(2, "Error\n", 6);
	write(1, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
