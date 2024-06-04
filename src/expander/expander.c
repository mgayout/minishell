/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/04 16:34:35 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	expander(t_data *data)
{
	t_par	*parser;

	parser = data->parser;
	while (parser != NULL)
	{
		if (init_expander(data, &data->expander, parser))
			return (0);
		parser = parser->next;
	}
	return (1);
}

int	init_expander(t_data *data, t_exp **expander, t_par *parser)
{
	t_exp	*new;

	new = new_exp();
	if (!new)
		return (1);
	new->id = parser->id;
	new->cmd = dollar_exp(data, parser->cmd);
	if (!new->cmd)
		return (1);
	new->builtin = is_a_builtin(new->cmd);
	new->arg = dollar_exp(data, parser->arg);
	new->infile = dollar_exp(data, parser->last_infile);
	new->outfile = dollar_exp(data, parser->last_outfile);
	new->pipein = parser->pipein;
	new->pipeout = parser->pipeout;
	new->heredoc = parser->heredoc;
	new->append = parser->append;
	expadd_back(expander, new);
	return (0);
}
