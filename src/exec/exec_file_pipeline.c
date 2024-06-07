/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:13:00 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 18:11:28 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_file_pipeline(t_data *data, t_pid child)
{
	if (child.lst->builtin < 3 || !data->exec->pid[data->exec->status])
	{
		infile_pipeline(data, child);
		outfile_pipeline(data, child);
	}
	else if (child.lst->pipeout)
	{
		dup2(data->exec->pipefd[0], STDIN_FILENO);
		close(data->exec->pipefd[1]);
	}
}

void	infile_pipeline(t_data *data, t_pid child)
{
	if (child.lst->infile && !child.lst->heredoc)
	{
		child.infile = open(child.lst->infile, O_RDONLY);
		dup2(child.infile, STDIN_FILENO);
		close(data->exec->pipefd[0]);
	}
	else if (child.lst->infile && child.lst->heredoc)
	{
		child.infile = init_heredoc(data, child.lst->infile);
		data->exec->temp = true;
		dup2(child.infile, STDIN_FILENO);
		close(data->exec->pipefd[0]);
	}
	else
		close(data->exec->pipefd[0]);
}

void	outfile_pipeline(t_data *data, t_pid child)
{
	if (child.lst->outfile && !child.lst->append)
		child.outfile = open(child.lst->outfile,
				O_RDWR | O_TRUNC | O_CREAT, 0640);
	else if (child.lst->outfile && child.lst->append)
		child.outfile = open(child.lst->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0640);
	else if (child.lst->pipeout)
		child.outfile = dup(data->exec->pipefd[1]);
	else
	{
		close(data->exec->pipefd[1]);
		child.outfile = data->exec->std_out;
	}
	dup2(child.outfile, STDOUT_FILENO);
}
