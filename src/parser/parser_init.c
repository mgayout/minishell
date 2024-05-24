/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:26:30 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/24 15:55:17 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../lexer/lexer.h"

void	first_string(t_par *parser, t_lex *lexer)
{
	parser->cmd = lexer->data;
	parser->status = 1;
}

void	infile_parser(t_par *parser, t_lex *lexer)
{
	if (lexer->prev->redir == INFILE)
	{
		parser->infile_count += 1;
		lexer->data->id = parser->infile_count;
		lexer->data->heredoc = false;
		lstradd_back(&parser->infile, lexer->data);
	}
	else if (lexer->prev->redir == HEREDOC)
	{
		parser->infile_count += 1;
		lexer->data->id = parser->infile_count;
		lexer->data->heredoc = true;
		lstradd_back(&parser->infile, lexer->data);
	}
}

void	outfile_parser(t_par *parser, t_lex *lexer)
{
	if (lexer->prev->redir == OUTFILE)
		parser->append = false;
	else if (lexer->prev->redir == APPEND)
		parser->append = true;
	parser->outfile_count += 1;
	lexer->data->id = parser->outfile_count;
	lstradd_back(&parser->outfile, lexer->data);
}

void	cmd_arg_parser(t_par *parser, t_lex *lexer)
{
	if (parser->status == 1)
	{
		if (!parser->arg)
			parser->arg = lexer->data;
		else
			lstrlast(parser->arg)->next = lexer->data;
	}
	else if (parser->status == 2 && lexer->prev->prev->type == REDIR)
	{
		parser->cmd = lexer->data;
		parser->status = 1;
	}
}
