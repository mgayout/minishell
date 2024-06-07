/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:47:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 16:53:16 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_builtin(t_data *data, t_pid child)
{
	char	**args;
	int		i;

	if (!child.lst->arg)
		print_export(data);
	else
	{
		i = 0;
		args = ft_split(child.lst->arg, ' ');
		if (!check_export_arg(args))
		{
			while (args[i])
			{
				init_new_export(data, args[i]);
				if (ft_strchr(args[i], '='))
					init_new_env(data, args[i]);
				i++;
			}
		}
		free_tab(args);
	}
}

void	init_new_export(t_data *data, char *arg)
{
	char	**split_arg;
	t_env	*new;
	int		i;

	split_arg = ft_split(arg, '=');
	new = malloc(sizeof(t_env));
	new->name = ft_strdup(split_arg[0]);
	new->value = NULL;
	new->prev = NULL;
	new->next = NULL;
	i = 1;
	while (split_arg[i])
	{
		if (!new->value)
			new->value = ft_strdup(split_arg[i]);
		else
			new->value = ft_strjoin(new->value, ft_strjoin("=", split_arg[i]));
		i++;
	}
	find_pos_export(data, new);
	free_tab(split_arg);
}

void	init_new_env(t_data *data, char *arg)
{
	char	**split_arg;
	t_env	*new;
	int		i;

	split_arg = ft_split(arg, '=');
	new = malloc(sizeof(t_env));
	new->name = ft_strdup(split_arg[0]);
	new->value = NULL;
	new->prev = NULL;
	new->next = NULL;
	i = 1;
	while (split_arg[i])
	{
		if (!new->value)
			new->value = ft_strdup(split_arg[i]);
		else
			new->value = ft_strjoin(new->value, ft_strjoin("=", split_arg[i]));
		i++;
	}
	envadd_back(&data->env, new);
	free_tab(split_arg);
}

void	find_pos_export(t_data *data, t_env *new)
{
	t_env	*pos;
	
	pos = data->export;
	while (pos)
	{
		if (ft_strncmp(pos->name, new->name, ft_strlen(pos->name)) >= 0)
		{
			if (!pos->prev)
			{
				data->export->prev = new;
				new->next = data->export;
				data->export = new;
			}
			else
				add_new_export(pos, new);
			break;
		}
		pos = pos->next;
	}
	if (!pos)
		envadd_back(&data->export, new);
}

void	add_new_export(t_env *pos, t_env *new)
{
	t_env	*prev;

	if (ft_strncmp(pos->name, new->name, ft_strlen(pos->name)) > 0)
	{
		prev = pos->prev;
		prev->next = new;
		new->prev = prev;
		new->next = pos;
		pos->prev = new;
	}
	else if (!ft_strncmp(pos->name, new->name, ft_strlen(pos->name)) && new->value)
		pos->value = ft_strdup(new->value);
}
