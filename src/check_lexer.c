/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:34:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/04 14:09:50 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int	check_lexer(t_data *data, t_lex *lexer)
{
	if (lexer->type == PIPE)
		return (error_type(data, BEGIN_PIPE));
	else if (lexlast(lexer)->type == PIPE)
		return (error_type(data, END_PIPE));
	else if (lexlast(lexer)->prev && lexlast(lexer)->prev->type == REDIR
		&& lexlast(lexer)->type == REDIR)
		return (error_type(data, END_MULTITOKEN));
	else if (lexlast(lexer)->type == REDIR)
		return (error_type(data, END_TOKEN));
	return (1);
}

int	error_type(t_data *data, t_errors n)
{
	if (n == BEGIN_PIPE)
		print_error(data, "minishell: syntax error near unexpected token `|'\n", 2);
	else if (n == END_PIPE)
		print_error(data, "minishell: syntax error: unexpected end of file\n", 2);
	else if (n == END_TOKEN)
		print_error(data, "minishell: syntax error near unexpected token `newline'\n", 2);
	else if (n == END_MULTITOKEN && lexlast(data->lexer)->redir == INFILE)
		print_error(data, "minishell: syntax error near unexpected token '<'\n", 2);
	else if (n == END_MULTITOKEN && lexlast(data->lexer)->redir == HEREDOC)
		print_error(data, "minishell: syntax error near unexpected token '<<'\n", 2);
	else if (n == END_MULTITOKEN && lexlast(data->lexer)->redir == OUTFILE)
		print_error(data, "minishell: syntax error near unexpected token '>'\n", 2);
	else if (n == END_MULTITOKEN && lexlast(data->lexer)->redir == APPEND)
		print_error(data, "minishell: syntax error near unexpected token '>>'\n", 2);
	else if (n == IS_A_DIR)
		print_error(data, ft_strjoin_free(ft_strjoin("minishell: ", data->lexer->data->str),
			": Is a directory\n", 1), 126);
	return (0);
}
