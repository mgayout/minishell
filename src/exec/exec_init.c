/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:49:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/21 12:44:06 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../expander/expander.h"

t_exe	*init_exe(t_exp *expander)
{
	t_exe	*exec;

	exec = (t_exe *)ft_calloc(1, sizeof(t_exe));
	if (!exec)
		return (NULL);
	exec->status = 0;
	exec->nb_cmd = expsize(expander);
	exec->std_in = dup(0);
	exec->std_out = dup(1);
	exec->temp = false;
	exec->child = malloc(sizeof(t_pid) * exec->nb_cmd);
	return (exec);
}

t_pid	init_child(t_data *data)
{
	t_pid	child;
	t_exp	*tmp;
	int		i;

	child.infile = 0;
	child.outfile = 0;
	i = data->exec->status;
	tmp = data->expander;
	while (tmp != NULL)
	{
		if (i == (tmp->id - 1))
		{
			child.lst = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	return (child);
}
