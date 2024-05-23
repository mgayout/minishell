/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:09 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/23 12:25:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser(t_data *data)
{
	t_par	*par_tmp;
	t_lex	*lex_tmp;
	
	data->parser = new_par();
	par_tmp = data->parser;
	lex_tmp = data->lexer;
	while (lex_tmp != NULL)
	{
		if (init_parser(par_tmp, lex_tmp))
			par_tmp = par_tmp->next;
		lex_tmp = lex_tmp->next;
	}
}

int	init_parser(t_par *parser, t_lex *lexer)
{
	if (parser->id == 0)
	{
		if (parser->prev == NULL)
			parser->id = 1;
		else
			parser->id = parser->prev->id + 1;
		if (lexer->type == STRING)
			first_string(parser, lexer);
		else if (lexer->type == REDIR)
			parser->status = 2;
	}
	else if (lexer->type != PIPE)
	{
		if (lexer->type == STRING
		&& (lexer->prev->redir == INFILE || lexer->prev->redir == HEREDOC))
			infile_parser(parser, lexer);
		else if (lexer->type == STRING
		&& (lexer->prev->redir == OUTFILE || lexer->prev->redir == APPEND))
			outfile_parser(parser, lexer);
		else if (lexer->type == STRING)
			cmd_arg_parser(parser, lexer);
	}
	else
		return (last_parser(parser));
	return (0);
}

int	last_parser(t_par *parser)
{
	t_par	*new;

	new = new_par();
	parser->pipeout = true;
	new->pipein = true;
	new->prev = parser;
	parser->next = new;
	return (1);
}

void	print_par(t_data *data)
{
	t_par	*parser;
	t_lstr	*tmp;

	parser = data->parser;
	printf("\nPARSER\n\n");
	while (parser)
	{
		printf("id = %d\n", parser->id);
		tmp = parser->cmd;
		while (tmp)
		{
			if (tmp->id != 0)
				printf("cmd id = %d\n", tmp->id);
			printf("cmd = %s\n", tmp->str);
			if (tmp->quote == SQUOTE)
				printf("SQUOTE\n");
			else if (tmp->quote == DQUOTE)
				printf("DQUOTE\n");
			tmp = tmp->next;
		}
		tmp = parser->arg;
		while (tmp)
		{
			printf("arg = %s\n", tmp->str);
			if (tmp->quote == SQUOTE)
				printf("SQUOTE\n");
			else if (tmp->quote == DQUOTE)
				printf("DQUOTE\n");
			tmp = tmp->next;
		}
		printf("infile count = %d\n", parser->infile_count);
		tmp = parser->infile;
		while (tmp)
		{
			printf("infile id = %d\n", tmp->id);
			if (tmp->heredoc == true)
			{
				printf("limiter = %s\n", tmp->str);
			}
			else
				printf("infile = %s\n", tmp->str);
			if (tmp->quote == SQUOTE)
				printf("SQUOTE\n");
			else if (tmp->quote == DQUOTE)
				printf("DQUOTE\n");
			tmp = tmp->next;
		}
		printf("outfile count = %d\n", parser->outfile_count);
		tmp = parser->outfile;
		while (tmp)
		{
			printf("outfile id = %d\n", tmp->id);
			printf("outfile = %s\n", tmp->str);
			if (tmp->quote == SQUOTE)
				printf("SQUOTE\n");
			else if (tmp->quote == DQUOTE)
				printf("DQUOTE\n");
			tmp = tmp->next;
		}
		if (parser->pipein == true)
			printf("pipein true\n");
		if (parser->pipeout == true)
			printf("pipeout true\n");
		printf("\n");
		parser = parser->next;
	}
}
