/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:34:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 16:58:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_lexer(t_data *data, t_lex *lexer)
{
	if (lexer->type == PIPE)
		return (error_type(data, 0));
	else if (lexlast(lexer)->type == PIPE)
		return (error_type(data, 1));
	else if (lexlast(lexer)->prev && lexlast(lexer)->prev->type == REDIR
		&& lexlast(lexer)->type == REDIR)
		return (error_type(data, 3));
	else if (lexlast(lexer)->type == REDIR)
		return (error_type(data, 2));
	return (1);
}

int	error_type(t_data *data, int n)
{
	if (n == 0)
		print_error(ft_strdup("minishell: syntax error near unexpected token `|'\n"), 2);
	else if (n == 1)
		print_error(ft_strdup("minishell: syntax error: unexpected end of file\n"), 2);
	else if (n == 2)
		print_error(ft_strdup("minishell: syntax error near unexpected token `newline'\n"), 2);
	else if (n == 3 && lexlast(data->lexer)->redir == INFILE)
		print_error(ft_strdup("minishell: syntax error near unexpected token '<'\n"), 2);
	else if (n == 3 && lexlast(data->lexer)->redir == HEREDOC)
		print_error(ft_strdup("minishell: syntax error near unexpected token '<<'\n"), 2);
	else if (n == 3 && lexlast(data->lexer)->redir == OUTFILE)
		print_error(ft_strdup("minishell: syntax error near unexpected token '>'\n"), 2);
	else if (n == 3 && lexlast(data->lexer)->redir == APPEND)
		print_error(ft_strdup("minishell: syntax error near unexpected token '>>'\n"), 2);
	return (0);
}
