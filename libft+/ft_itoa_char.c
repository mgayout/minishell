/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:04:01 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/03 16:16:02 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_countint(int n);

int	ft_itoa_char(char *copy, int n)
{
	long	nb;
	int		sign;
	int		size;

	nb = n;
	sign = 0;
	if (n < 0)
	{
		nb *= -1;
		sign = 1;
	}
	size = ft_countint(n) + sign;
	copy = malloc((size + 1) * sizeof(char));
	if (!copy)
		return (1);
	copy[size] = '\0';
	while (size > 0)
	{
		copy[--size] = (nb % 10) + '0';
		nb /= 10;
	}
	if (sign == 1)
		copy[size] = '-';
	return (0);
}

int	ft_countint(int n)
{
	int	a;

	a = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		a++;
	}
	return (a);
}
