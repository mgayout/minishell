/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:26:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/24 15:37:25 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_par	*new_par(void)
{
	t_par	*new;

	new = (t_par *)ft_calloc(1, sizeof(t_par));
	if (!new)
		return (NULL);
	new->id = 0;
	new->status = 0;
	new->cmd = NULL;
	new->arg = NULL;
	new->infile = NULL;
	new->infile_count = 0;
	new->outfile = NULL;
	new->outfile_count = 0;
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
