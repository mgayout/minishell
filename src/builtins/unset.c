/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:47:55 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/31 12:55:33 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	unset_builtin(t_data *data, t_pid child)
{
	t_env	*tmp_env;
	t_env	*tmp_exp;

	if (!child.lst->arg)
		return;
	tmp_env = data->env;
	tmp_exp = data->export;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->name, child.lst->arg, ft_strlen(tmp_env->name)))
		{
			remove_var(tmp_env);
			break;
		}
		tmp_env = tmp_env->next;
	}
	while (tmp_exp)
	{
		if (!ft_strncmp(tmp_exp->name, child.lst->arg, ft_strlen(tmp_exp->name)))
		{
			remove_var(tmp_exp);
			break;
		}
		tmp_exp = tmp_exp->next;
	}
}

void	remove_var(t_env *tmp)
{
	t_env	*next;
	t_env	*prev;

	next = NULL;
	prev = NULL;
	if (tmp->next)
		next = tmp->next;
	if (tmp->prev)
		prev = tmp->prev;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	if (next && !prev)
		next->prev = NULL;
	else if (!next && prev)
		prev->next = NULL;
	else if (next && prev)
	{
		prev->next = next;
		next->prev = prev;
	}
}
