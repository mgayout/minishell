/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:17 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/11 11:21:15 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_builtin(t_data *data, t_pid child)
{
	t_env	*tmp;

	if (child.lst->arg && (child.lst->arg[0] == '-' && &child.lst->arg[1]))
		print_error(ft_strjoin_free(ft_strjoin("minishell: env: ",
					child.lst->arg), ": invalid option\n", 1), 1);
	else if (child.lst->arg)
		print_error(ft_strjoin_free(ft_strjoin("minishell: env: '",
					child.lst->arg), "': No such file or directory\n", 1), 1);
	else
	{
		tmp = data->env;
		while (tmp && (tmp->name && tmp->value))
		{
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
			tmp = tmp->next;
		}
	}
	free_all(data, 1);
	exit(g_global.error);
}
