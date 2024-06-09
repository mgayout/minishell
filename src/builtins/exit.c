/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:41 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 21:02:55 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_builtin(t_data *data, t_pid child)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (child.lst->arg && child.lst->arg[i])
	{
		if (child.lst->arg[i] == ' ')
			status = 1;
		else if (child.lst->arg[i] == '-')
			status = 2;
		else if ((child.lst->arg[i] < '0' || child.lst->arg[i] > '9')
			&& child.lst->arg[i] != '+')
			status = 3;
		if (status != 0)
			break ;
		i++;
	}
	print_exit(data, child.lst->arg, status);
}

void	print_exit(t_data *data, char *arg, int status)
{
	if (!arg)
		print_error(ft_strdup("exit\n"), g_global.error);
	else if (status == 0)
		print_error(ft_strdup("exit\n"), ft_atoi(arg));
	else if (status == 1)
	{
		print_error(ft_strdup("exit\nminishell: exit: too many arguments\n"),
			1);
		return ;
	}
	else if (status == 2)
		print_error(ft_strdup("exit\n"), 156);
	else if (status == 3)
		print_error(ft_strjoin_free(ft_strjoin("exit\nminishell: exit: ", arg),
				": numeric argument required\n", 1), 2);
	free_all(data, 1);
	exit(g_global.error);
}
