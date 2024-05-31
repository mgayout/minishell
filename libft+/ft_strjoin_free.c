/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:17:38 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/31 17:20:44 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_free(char *s1, char *s2, int n)
{
	char	*copy;
	size_t	i;

	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!s1 || !s2)
		return (NULL);
	copy = malloc(i * sizeof(char));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s1, i);
	ft_strlcat(copy, s2, i);
	if (n == 1)
		free(s1);
	else if (n == 2)
		free(s2);
	else if (n == 3)
	{
		free(s1);
		free(s2);
	}
	return (copy);
}
