/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:26:41 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/21 16:53:47 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	token_type(t_lex *lexer, char *prompt)
{
	lexer->type = REDIR;
	if (!ft_strncmp(prompt, ">>", 2))
		lexer->redir = APPEND;
	else if (!ft_strncmp(prompt, ">", 1))
		lexer->redir = OUTFILE;
	else if (!ft_strncmp(prompt, "<<", 2))
		lexer->redir = HEREDOC;
	else if (!ft_strncmp(prompt, "<", 1))
		lexer->redir = INFILE;
	else if (!ft_strncmp(prompt, "|", 1))
		lexer->type = PIPE;
	if (!ft_strncmp(prompt, "<<", 2) || !ft_strncmp(prompt, ">>", 2))
		return (2);
	return (1);
}

int	string_type(t_data *data, t_lex *lexer, bool space)
{
	int	i;

	i = 0;
	lexer->type = STRING;
	while (data->prompt[i] && !ft_strchr("><| \t\r\v\f", data->prompt[i]))
	{
		if (data->prompt[i] == '\'' || data->prompt[i] == '"')
		{
			while (count_quotes(data->prompt))
				data->prompt = add_final_quote(data->prompt);	
			if (data->prompt[i] == '\'')
				i += data_quote(lexer, data->prompt + i, "'", space);
			else if (data->prompt[i] == '"')
				i += data_quote(lexer, data->prompt + i, "\"", space);
		}
		else
			i += data_noquote(lexer, data->prompt + i, "\"'><| \t\r\v\f", space);
	}
	return (i);
}
