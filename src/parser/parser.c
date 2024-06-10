/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:09 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 14:14:13 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_data *data)
{
	t_lex	*lexer;

	lexer = data->lexer;
	while (lexer != NULL)
	{
		lexer = init_parser(data, lexer);
		if (lexer)
			lexer = lexer->next;
	}
	if (!data->parser)
		return (0);
	return (1);
}

t_lex	*init_parser(t_data *data, t_lex *lexer)
{
	t_par	*new;

	new = new_par();
	if (!new)
		return (NULL);
	while (lexer)
	{
		if (parser_type(data, new, lexer))
			break ;
		lexer = lexer->next;
	}
	paradd_back(&data->parser, new);
	return (lexer);
}

int	parser_type(t_data *data, t_par *new, t_lex *lexer)
{
	if (new->id == 0)
		first_elem(data, new, lexer);
	else if (lexer->type != PIPE)
	{
		if (lexer->prev && (lexer->prev->redir == INFILE
				|| lexer->prev->redir == HEREDOC))
			infile_parser(new, lexer);
		else if (lexer->prev && (lexer->prev->redir == OUTFILE
				|| lexer->prev->redir == APPEND))
			outfile_parser(new, lexer);
		else if (lexer->type == STRING)
			cmd_arg_parser(new, lexer);
	}
	else
	{
		new->pipeout = true;
		return (1);
	}
	return (0);
}
