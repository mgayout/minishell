/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:26:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/04 13:55:38 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_par	*new_par(void)
{
	t_par	*new;

	new = ft_calloc(1, sizeof(t_par));
	if (!new)
		return (NULL);
	new->id = 0;
	new->status = 0;
	new->cmd = NULL;
	new->arg = NULL;
	new->infile_lst = NULL;
	new->heredoc_lst = NULL;
	new->infile_count = 0;
	new->last_infile = NULL;
	new->outfile_lst = NULL;
	new->append_lst = NULL;
	new->outfile_count = 0;
	new->last_outfile = NULL;
	new->heredoc = false;
	new->append = false;
	new->pipein = false;
	new->pipeout = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	parsize(t_par *parser)
{
	int	size;

	size = 0;
	while (parser != NULL)
	{
		++size;
		parser = parser->next;
	}
	return (size);
}

t_par	*parlast(t_par *lst)
{
	t_par	*last;
	int		i;
	int		j;

	last = lst;
	if (!last)
		return (NULL);
	i = 1;
	j = parsize(last);
	while (i != j)
	{
		last = last->next;
		i++;
	}
	return (last);
}

void	paradd_back(t_par **lst, t_par *new)
{
	t_par	*last;

	if (*lst != NULL)
	{
		last = *lst;
		last = parlast(*lst);
		new->prev = last;
		last->next = new;
		return ;
	}
	*lst = new;
}
