/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:26:30 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/05 14:21:25 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../lexer/lexer.h"
#include "../expander/expander.h"

void	first_elem(t_data *data, t_par *new, t_lex *lexer)
{
	if (!data->parser)
		new->id = 1;
	else
	{
		new->id = parlast(data->parser)->id + 1;
		new->pipein = true;	
	}
	if (lexer->type == STRING)
	{
		new->cmd = lexer->data;
		new->status = 1;
	}
	else if (lexer->type == REDIR)
		new->status = 2;
}

void	infile_parser(t_par *parser, t_lex *lexer)
{
	if (parser->heredoc)
		lstradd_back(&parser->heredoc_lst, parser->last_infile);
	else if (parser->infile_count >= 1)
		lstradd_back(&parser->infile_lst, parser->last_infile);
	if (lexer->prev->redir == INFILE)
	{
		parser->infile_count += 1;
		lexer->data->id = parser->infile_count;
		parser->last_infile = lexer->data;
		parser->heredoc = false;
	}
	else if (lexer->prev->redir == HEREDOC)
	{
		parser->infile_count += 1;
		lexer->data->id = parser->infile_count;
		parser->last_infile = lexer->data;
		parser->heredoc = true;
	}
}

void	outfile_parser(t_par *parser, t_lex *lexer)
{
	if (parser->append)
		lstradd_back(&parser->append_lst, parser->last_outfile);
	else if (parser->outfile_count >= 1)
		lstradd_back(&parser->outfile_lst, parser->last_outfile);
	if (lexer->prev->redir == OUTFILE)
	{
		parser->outfile_count += 1;
		lexer->data->id = parser->outfile_count;
		parser->last_outfile = lexer->data;
		parser->append = false;
	}
	else if (lexer->prev->redir == APPEND)
	{
		parser->outfile_count += 1;
		lexer->data->id = parser->outfile_count;
		parser->last_outfile = lexer->data;
		parser->append = true;
	}
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
