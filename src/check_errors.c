/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:34:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/23 17:16:12 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int	check_lexer(t_data *data, t_lex *lexer)
{
	if (lexer->type == PIPE)
		return (print_errors(data, BEGIN_PIPE));
	else if (lexlast(lexer)->type == PIPE)
		return (print_errors(data, END_PIPE));
	else if (lexlast(lexer)->prev && lexlast(lexer)->prev->type == REDIR
		&& lexlast(lexer)->type == REDIR)
		return(print_errors(data, END_MULTITOKEN));
	else if (lexlast(lexer)->type == REDIR)
		return (print_errors(data, END_TOKEN));
	else if (is_a_directory(lexer))
		return(print_errors(data, IS_A_DIR));
	else if (no_final_quote(lexer, NO_EOF_SQ))
		return (print_errors(data, NO_EOF_SQ));
	else if (no_final_quote(lexer, NO_EOF_DQ))
		return (print_errors(data, NO_EOF_DQ));
	return (1);
}

int	print_errors(t_data *data, t_errors n)
{
	if (n == BEGIN_PIPE)
	{
		data->error = 2;
		printf("bash: syntax error near unexpected token `|'\n");	
	}
	else if (n == END_PIPE)
	{
		printf("bash: syntax error: unexpected end of file\n");	
	}
	else if (n == END_TOKEN || n == END_MULTITOKEN)
	{
		data->error = 2;
		if (n == END_TOKEN)
			printf("bash: syntax error near unexpected token `newline'\n");
		else
		{
			if (lexlast(data->lexer)->redir == INFILE
				|| lexlast(data->lexer)->redir == HEREDOC)
				printf("bash: syntax error near unexpected token '<<'\n");
			else
				printf("bash: syntax error near unexpected token '>>'\n");
		}
	}
	else if (n == IS_A_DIR)
	{
		data->error = 126;
		printf("bash: %s: Is a directory\n", data->lexer->data->str);
	}
	else if (n == NO_EOF_SQ)
	{
		data->error = 2;
		printf("bash: unexpected EOF while looking for matching `\''\nbash: syntax error: unexpected end of file\n");	
	}
	else if (n == NO_EOF_DQ)
	{
		data->error = 2;
		printf("bash: unexpected EOF while looking for matching `\"'\nbash: syntax error: unexpected end of file\n");
	}
	return (0);
}

int	is_a_directory(t_lex *lexer)
{
	int	count;
	int	i;
	
	count = 0;
	i = 0;
	if (lexer->type != STRING)
		return (0);
	while (lexer->data->str[i])
	{
		if (lexer->data->str[i] != '.' && lexer->data->str[i] != '/')
			return (0);
		if (lexer->data->str[i] == '.')
			count++;
		else if (lexer->data->str[i] == '/')
			count = 0;
		if (count >= 3)
			return (0);
		i++;
	}
	return (1);
}

int	no_final_quote(t_lex *lexer, t_errors n)
{
	t_lex	*tmp;
	t_lstr	*tmp2;

	tmp = lexer;
	while (tmp)
	{
		tmp2 = tmp->data;
		if (tmp->type == STRING)
			while(tmp2)
			{
				if (tmp2->final_quote == n)
					return (1);
				tmp2 = tmp2->next;
			}
		tmp = tmp->next;
	}
	return (0);
}
