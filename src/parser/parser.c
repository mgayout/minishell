/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:09 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 21:38:14 by mgayout          ###   ########.fr       */
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
		tmp = parser->infile_lst;
		while (tmp)
		{
			printf("infile id = %d\n", tmp->id);
			printf("infile = %s\n", tmp->str);
			if (tmp->quote == SQUOTE)
				printf("SQUOTE\n");
			else if (tmp->quote == DQUOTE)
				printf("DQUOTE\n");
			tmp = tmp->next;
		}
		tmp = parser->heredoc_lst;
		while (tmp)
		{
			printf("heredoc id = %d\n", tmp->id);
			printf("mdp = %s\n", tmp->str);
			if (tmp->quote == SQUOTE)
				printf("SQUOTE\n");
			else if (tmp->quote == DQUOTE)
				printf("DQUOTE\n");
			tmp = tmp->next;
		}
		tmp = parser->last_infile;
		while (tmp)
		{
			if (parser->heredoc == false)
			{
				printf("real infile :\n");
				printf("infile id = %d\n", tmp->id);
				printf("infile = %s\n", tmp->str);
				if (tmp->quote == SQUOTE)
					printf("SQUOTE\n");
				else if (tmp->quote == DQUOTE)
					printf("DQUOTE\n");
			}
			else
			{
				printf("real heredoc :\n");
				printf("heredoc id = %d\n", tmp->id);
				printf("mdp = %s\n", tmp->str);
				if (tmp->quote == SQUOTE)
					printf("SQUOTE\n");
				else if (tmp->quote == DQUOTE)
					printf("DQUOTE\n");
			}
			tmp = tmp->next;
		}
		printf("outfile count = %d\n", parser->outfile_count);
		tmp = parser->outfile_lst;
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
		tmp = parser->append_lst;
		while (tmp)
		{
			printf("outfile append id = %d\n", tmp->id);
			printf("outfile append = %s\n", tmp->str);
			if (tmp->quote == SQUOTE)
				printf("SQUOTE\n");
			else if (tmp->quote == DQUOTE)
				printf("DQUOTE\n");
			tmp = tmp->next;
		}
		tmp = parser->last_outfile;
		while (tmp)
		{
			printf("real outfile :\n");
			printf("outfile id = %d\n", tmp->id);
			printf("outfile = %s\n", tmp->str);
			if (tmp->quote == SQUOTE)
				printf("SQUOTE\n");
			else if (tmp->quote == DQUOTE)
				printf("DQUOTE\n");
			if (parser->append == true)
				printf("append true\n");
			else
				printf("append false\n");
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
