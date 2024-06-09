/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:34:56 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 17:23:32 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

/*Write a string.*/
void	ft_putstr_fd_free(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	free(s);
}
