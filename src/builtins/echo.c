/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:45:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/28 13:35:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo_builtin(t_pid child)
{
	if (!child.lst->arg)
		printf("\n");
	else if (!echo_arg(child.lst))
		printf("%s\n", child.lst->arg);
	else
		printf("%s", child.lst->arg);
}

int	echo_arg(t_exp *lst)
{
	int begin;
	int	status;
	int	i;

	begin = 0;
	status = 0;
	i = 0;
	while (begin == 0 && lst->arg[i])
	{
		if (lst->arg[i] == ' ' || lst->arg[i] == '-')
		{
			if (!ft_strncmp(&lst->arg[i], "-n ", 3))
			{
				status = 1;
				lst->arg = ft_substr(lst->arg, i + 3, ft_strlen(lst->arg) - 2);
				i = 0;
			}
			else
				i++;
		}
		else
			begin = 1;
	}
	return (status);
}
