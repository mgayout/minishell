/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:39:13 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/24 14:04:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	data_noquote(t_lex *lexer, char *prompt, bool space)
{
	t_lstr	*data;
	char	*tmp;
	int		i;

	i = 0;
	while (prompt[i] && !ft_strchr("\"'><| \t\r\v\f", prompt[i]))
		i++;
	data = new_lstr();
	if (!data)
		return (0);
	tmp = ft_substr(prompt, 0, i);
	if (!tmp)
		data->str = NULL;
	else
		data->str = ft_strdup(tmp);
	data->space = space;
	data->quote = NO_QUOTE;
	data->final_quote = NOTHING;
	lstradd_back(&lexer->data, data);
	free(tmp);
	return (i);
}

int	data_squote(t_lex *lexer, char *prompt, bool space, t_errors final_quote)
{
	t_lstr	*data;
	char	*tmp;
	int		i;

	i = 1;
	while (prompt[i] && !ft_strchr("'", prompt[i]))
		i++;
	data = new_lstr();
	if (!data)
		return (0);
	tmp = ft_substr(prompt, 1, i - 1);
	if (!tmp)
		data->str = NULL;
	else
		data->str = ft_strdup(tmp);
	data->space = space;
	data->quote = SQUOTE;
	data->final_quote = final_quote;
	lstradd_back(&lexer->data, data);
	free(tmp);
	if (i == (int)ft_strlen(prompt))
		return (i);
	return (i + 1);
}

int	data_dquote(t_lex *lexer, char *prompt, bool space, t_errors final_quote)
{
	t_lstr	*data;
	char	*tmp;
	int		i;

	i = 1;
	while (prompt[i] && !ft_strchr("\"", prompt[i]))
		i++;
	data = new_lstr();
	if (!data)
		return (0);
	tmp = ft_substr(prompt, 1, i - 1);
	if (!tmp)
		data->str = NULL;
	else
		data->str = ft_strdup(tmp);
	data->space = space;
	data->quote = DQUOTE;
	data->final_quote = final_quote;
	lstradd_back(&lexer->data, data);
	free(tmp);
	if (i == (int)ft_strlen(prompt))
		return (i);
	return (i + 1);
}
