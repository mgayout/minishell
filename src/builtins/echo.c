/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:45:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 17:07:18 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_builtin(t_data *data, t_pid child)
{
	if (!child.lst->arg)
		ft_putstr_fd("\n", 1);
	else if (!echo_arg(child.lst))
	{
		ft_putstr_fd(child.lst->arg, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd(child.lst->arg, 1);
	free_all(data, 1);
	exit(0);
}

int	echo_arg(t_exp *lst)
{
	int	begin;
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
				lst->arg = echo_new_arg(lst->arg, i);
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

char	*echo_new_arg(char	*old_arg, int i)
{
	char	*new;
	
	new = ft_substr(old_arg, i + 3, ft_strlen(old_arg) - 2);
	free (old_arg);
	return (new);
}
