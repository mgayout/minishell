/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:59 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/05 16:07:43 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd_builtin(t_data *data, t_pid child)
{
	t_env	*tmp;

	if (child.lst->arg)
		if (pwd_error(data, child.lst->arg))
			return;
	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", ft_strlen("PWD")))
		{
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

int	pwd_error(t_data *data, char *arg)
{
	if (arg[0] == '-' && &arg[1])
	{
		print_error(data, ft_strjoin_free(ft_strjoin("minishell: pwd: ", arg), ": invalid option\n", 1), 2);
		return (1);
	}
	return (0);
}