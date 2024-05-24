/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:19:20 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/24 15:30:51 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exp(t_exp **expander)
{
	t_exp	*tmp;

	while (*expander != NULL)
	{
		tmp = *expander;
		*expander = (*expander)->next;
		free(tmp->cmd);
		free(tmp->arg);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		free(tmp);
	}
}

void	free_exe(t_exe **exec)
{
	t_exe	*tmp;

	tmp = *exec;
	//if (tmp->heredoc)
		//unlink(".temp");
	free(tmp->child);
	free(tmp->pid);
	free(tmp->pipefd);
}

void	free_tab(char **tabs)
{
	int	i;

	i = 0;
	while (tabs[i] != NULL)
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
}
