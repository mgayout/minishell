/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 17:32:49 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expander(t_data *data)
{
	t_par	*parser;

	parser = data->parser;
	while (parser != NULL)
	{
		init_expander(data, &data->expander, parser);
		parser = parser->next;
	}
}

void	init_expander(t_data *data, t_exp **expander, t_par *parser)
{
	t_exp	*new;

	new = new_exp();
	if (!new)
		return ;
	new->id = parser->id;
	new->cmd = dollar_exp(data, parser->cmd);
	if (!new->cmd)
	{
		free(new);
		return ;
	}
	new->builtin = is_a_builtin(new->cmd);
	new->arg = dollar_exp(data, parser->arg);
	new->infile = dollar_exp(data, parser->last_infile);
	new->outfile = dollar_exp(data, parser->last_outfile);
	new->pipein = parser->pipein;
	new->pipeout = parser->pipeout;
	new->heredoc = parser->heredoc;
	new->append = parser->append;
	expadd_back(expander, new);
}
