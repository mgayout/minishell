/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:39:13 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/03 13:04:00 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	data_noquote(t_lex *lexer, char *prompt, bool space)
{
	t_lstr	*data;
	int		i;

	data = new_lstr();
	if (!data)
		return (0);
	i = 0;
	while (prompt[i] && !ft_strchr("\"'><| \t\r\v\f", prompt[i]))
		i++;
	data->str = ft_substr(prompt, 0, i);
	if (!data->str)
	{
		free(data);
		return (0);
	}
	data->space = space;
	data->quote = NO_QUOTE;
	lstradd_back(&lexer->data, data);
	return (i);
}

int	data_squote(t_lex *lexer, char *prompt, bool space)
{
	t_lstr	*data;
	int		i;

	data = new_lstr();
	if (!data)
		return (0);
	i = 1;
	while (prompt[i] && !ft_strchr("'", prompt[i]))
		i++;
	data->str = ft_substr(prompt, 1, i - 1);
	if (!data->str)
	{
		free(data);
		return (0);
	}
	data->space = space;
	data->quote = SQUOTE;
	lstradd_back(&lexer->data, data);
	if (i == (int)ft_strlen(prompt))
		return (i);
	return (i + 1);
}

int	data_dquote(t_lex *lexer, char *prompt, bool space)
{
	t_lstr	*data;
	int		i;

	data = new_lstr();
	if (!data)
		return (0);
	i = 1;
	while (prompt[i] && !ft_strchr("\"", prompt[i]))
		i++;
	data->str = ft_substr(prompt, 1, i - 1);
	if (!data->str)
	{
		free(data);
		return (0);
	}
	data->space = space;
	data->quote = DQUOTE;
	lstradd_back(&lexer->data, data);
	if (i == (int)ft_strlen(prompt))
		return (i);
	return (i + 1);
}
