/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:53:27 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 17:23:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_file_cmd(t_data *data, t_pid child)
{
	child.infile = infile_cmd(data, child);
	child.outfile = outfile_cmd(data, child);
	dup2(child.infile, STDIN_FILENO);
	dup2(child.outfile, STDOUT_FILENO);
}

int	infile_cmd(t_data *data, t_pid child)
{
	int	infile;

	if (child.lst->infile && !child.lst->heredoc)
		infile = open(child.lst->infile, O_RDONLY);
	else if (child.lst->infile && child.lst->heredoc)
	{
		infile = init_heredoc(data, child.lst->infile);
		data->exec->temp = true;
	}
	else
		infile = data->exec->std_in;
	return (infile);
}

int	outfile_cmd(t_data *data, t_pid child)
{
	if (child.lst->outfile && !child.lst->append)
		child.outfile = open(child.lst->outfile,
				O_RDWR | O_TRUNC | O_CREAT, 0640);
	else if (child.lst->outfile && child.lst->append)
		child.outfile = open(child.lst->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0640);
	else
		child.outfile = data->exec->std_out;
	return (child.outfile);
}
