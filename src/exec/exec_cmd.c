/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:55:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/31 14:52:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	children(t_data *data, t_pid child)
{
	t_env	*path;

	if (child.lst->builtin > 0)
		exec_builtins(data, child);
	else
	{
		path = data->env;
		while (path)
		{
			if (!ft_strncmp(path->name, "PATH", 5))
				break;
			path = path->next;
		}
		child.arg1 = create_arg1(path, child.lst->cmd);
		child.arg2 = create_arg2(child);
		if (child.arg1 && child.arg2)
			execve(child.arg1, child.arg2, data->envp);
		else
			print_error(data, ft_strjoin(child.lst->cmd, ": command not found\n"), 127);
	}
}

char	*create_arg1(t_env *path, char *str)
{
	char	**path_arg;
	char	*tmp;
	char	*path_cmd;
	int		i;

	if (!path)
		return (NULL);
	path_arg = ft_split(path->value, ':');
	i = 0;
	while (path_arg[i] != NULL)
	{
		tmp = ft_strjoin(path_arg[i], "/");
		path_cmd = ft_strjoin(tmp, str);
		free(tmp);
		if (access(path_cmd, 0) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	if (access(str, 0) == 0)
		return (str);
	return (NULL);
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
