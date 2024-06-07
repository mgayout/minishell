/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:47:55 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 16:53:21 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_builtin(t_data *data, t_pid child)
{
	char	**split_arg;
	int		i;

	if (!child.lst->arg)
		return;
	split_arg = ft_split(child.lst->arg, ' ');
	i = 0;
	while (split_arg[i])
	{
		search_pos(data, split_arg[i]);
		i++;
	}
	free_tab(split_arg);
}

void	search_pos(t_data *data, char *arg)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, arg, ft_strlen(tmp->name)))
		{
			remove_var(data, tmp, 1);
			break;
		}
		tmp = tmp->next;
	}
	tmp = data->export;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, arg, ft_strlen(tmp->name)))
		{
			remove_var(data, tmp, 0);
			break;
		}
		tmp = tmp->next;
	}
}

void	remove_var(t_data *data, t_env *tmp, int n)
{
	t_env	*next;
	t_env	*prev;

	if (!tmp->prev && !tmp->next)
		remove_all(data, tmp, n);
	else if (!tmp->prev)
		remove_first(data, tmp, n);
	else if (!tmp->next)
		remove_last(tmp);
	else
	{
		next = NULL;
		prev = NULL;
		next = tmp->next;
		prev = tmp->prev;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		prev->next = next;
		next->prev = prev;
	}
}

void	remove_all(t_data *data, t_env *tmp, int n)
{
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	if (n == 0)
		data->export = NULL;
	else
		data->env = NULL;
}

void	remove_first(t_data *data, t_env *tmp, int n)
{
	if (n == 0)
		data->export = data->export->next;
	else
		data->env = data->env->next;
	data->env->prev = NULL;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}

void	remove_last(t_env *tmp)
{
	t_env	*prev;

	prev = tmp->prev;
	prev->next = NULL;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}
