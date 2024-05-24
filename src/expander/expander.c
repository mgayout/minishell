/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/24 16:00:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expander(t_data *data)
{
	t_exp	*tmp;
	t_par	*parser;

	parser = data->parser;
	while (parser != NULL)
	{
		tmp = init_expander(data, parser);
		expadd_back(&data->expander, tmp);
		parser = parser->next;
	}
}

t_exp	*init_expander(t_data *data, t_par *parser)
{
	t_exp	*expander;

	expander = malloc(sizeof(t_exp));
	expander->id = parser->id;
	expander->cmd = dollar_exp(data, parser->cmd);
	expander->builtin = is_a_builtin(expander->cmd);
	expander->arg = dollar_exp(data, parser->arg);
	expander->infile = check_infiles(data, parser->infile,
			parser->infile_count);
	expander->outfile = check_outfiles(data, parser->outfile,
			parser->outfile_count);
	expander->pipein = parser->pipein;
	expander->pipeout = parser->pipeout;
	expander->append = parser->append;
	expander->heredoc = false;
	expander->prev = NULL;
	expander->next = NULL;
	return (expander);
}
