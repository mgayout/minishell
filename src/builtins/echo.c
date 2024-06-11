/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:45:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/11 11:20:52 by mgayout          ###   ########.fr       */
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

	begin = 0;
	status = 0;
	while (begin == 0 && lst->arg)
	{
		if (is_an_option(lst->arg))
		{
			status = 1;
			lst->arg = echo_new_arg(lst->arg);
		}
		else
			break ;
	}
	return (status);
}

int	is_an_option(char *arg)
{
	int	i;

	i = 0;
	while (1)
	{
		if (arg[i] != '-')
			return (0);
		else
			i++;
		while (arg[i] == 'n')
			i++;
		if ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ' || arg[i] == '\0')
			break ;
		else
			return (0);
	}
	return (1);
}

char	*echo_new_arg(char	*old_arg)
{
	char	*new;
	int		i;

	i = 1;
	while (old_arg && old_arg[i] == 'n')
		i++;
	while (old_arg && ((old_arg[i] >= 9 && old_arg[i] <= 13)
			|| old_arg[i] == ' '))
		i++;
	new = ft_substr(old_arg, i, ft_strlen(old_arg) - (i - 1));
	free (old_arg);
	return (new);
}
