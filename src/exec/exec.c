/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:25 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/24 13:37:10 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(t_data *data)
{
	data->exec = init_exe(data->expander);
	if (data->exec->nb_cmd == 1)
		exec_cmd_file(data);
	else
		exec_pipeline(data);
	dup2(data->exec->std_in, STDIN_FILENO);
	dup2(data->exec->std_out, STDOUT_FILENO);
	if (data->exec->temp)
		unlink(".temp");
}

void	exec_cmd_file(t_data *data)
{
	t_pid	child;

	data->exec->child[data->exec->status] = init_child(data);
	child = data->exec->child[data->exec->status];
	data->exec->pid = malloc(sizeof(int));
	if (!child.lst->builtin)
		data->exec->pid[0] = fork();
	if (child.lst->builtin || !data->exec->pid[0])
	{
		open_file_cmd(data, child);
		children(data, child);
	}
	if (!child.lst->builtin)
		waitpid(data->exec->pid[0], NULL, 0);
}

void	exec_pipeline(t_data *data)
{
	t_pid	child;
	int		i;

	data->exec->pid = malloc(sizeof(int) * data->exec->nb_cmd);
	while (data->exec->status < data->exec->nb_cmd)
	{
		i = data->exec->status;
		data->exec->child[i] = init_child(data);
		child = data->exec->child[i];
		if (child.lst->pipeout)
			pipe(data->exec->pipefd);
		if (!child.lst->builtin)
			data->exec->pid[i] = fork();
		open_file_pipeline(data, child);
		if (child.lst->builtin || !data->exec->pid[i])
			children(data, child);
		waitpid(data->exec->pid[i], NULL, 0);
		data->exec->status += 1;
	}
}
