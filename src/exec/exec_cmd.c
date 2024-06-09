/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:55:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 21:31:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	children(t_data *data, t_pid child)
{
	if (child.lst->builtin > 0)
		exec_builtins(data, child);
	else
	{
		child.arg1 = create_arg1(data, child.lst->cmd);
		if (child.arg1)
			child.arg2 = create_arg2(child);
		if (child.arg1 && child.arg2)
		{
			if (execve(child.arg1, child.arg2, data->envp) == -1)
			{
				exit(2);
			}
			exit(1);
		}
		else
			print_error(ft_strjoin(child.lst->cmd,
					": command not found\n"), 127);
		exit(127);
	}
}

char	*create_arg1(t_data *data, char *str)
{
	t_env	*path;
	char	**path_arg;
	char	*path_cmd;
	int		i;

	path = search_path(data);
	if (!path)
		return (NULL);
	path_arg = ft_split(path->value, ':');
	i = 0;
	while (path_arg[i] != NULL)
	{
		path_cmd = ft_strjoin_free(ft_strjoin(path_arg[i], "/"), str, 1);
		if (access(path_cmd, 0) == 0)
		{
			free_tab(path_arg);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	free_tab(path_arg);
	if (access(str, 0) == 0)
		return (str);
	return (NULL);
}

t_env	*search_path(t_data *data)
{
	t_env	*path;

	path = data->env;
	while (path)
	{
		if (!ft_strncmp(path->name, "PATH", 5))
			break ;
		path = path->next;
	}
	return (path);
}

char	**create_arg2(t_pid child)
{
	char	**arg2;
	char	*tmp;

	tmp = child.lst->cmd;
	if (child.lst->arg)
	{
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, child.lst->arg);
	}
	arg2 = ft_split(tmp, ' ');
	return (arg2);
}
