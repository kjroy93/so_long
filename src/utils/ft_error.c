/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroy93 <kjroy93@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:57:20 by kjroy93           #+#    #+#             */
/*   Updated: 2025/08/04 23:58:55 by kjroy93          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(const char *message)
{
	write(2, "Error\n", 6);
	write(1, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);	
}
