/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:10:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 21:35:42 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer(t_data *data)
{
	int	i;

	i = 0;
	if (check_quote(data))
		return (0);
	while (data->prompt[i])
	{
		while ((data->prompt[i] >= 9 && data->prompt[i] <= 13)
			|| data->prompt[i] == ' ')
			i++;
		if (i >= 1 && data->prompt[i - 1] == ' ')
			i = add_new_t_lex(data, &data->lexer, i, true);
		else
			i = add_new_t_lex(data, &data->lexer, i, false);
		if (i < 0)
			return (0);
	}
	free(data->prompt);
	return (1);
}

int	add_new_t_lex(t_data *data, t_lex **lexer, int i, bool space)
{
	t_lex	*new;

	new = new_lex();
	if (!new)
		return (-1);
	if (data->prompt[i] == '>' || data->prompt[i] == '<'
		|| data->prompt[i] == '|')
		i += token_type(new, &data->prompt[i]);
	else
		i = string_type(data, i, new, space);
	lexadd_back(lexer, new);
	return (i);
}

int	check_quote(t_data *data)
{
	int	err;

	err = count_quotes(data->prompt);
	if (err == 2)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking \
for matching '''\n", 2);
		print_error(ft_strdup("minishell: syntax error: \
unexpected end of file\n"), 2);
		return (1);
	}
	else if (err == 1)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking \
for matching '\"'\n", 2);
		print_error(ft_strdup("minishell: syntax error: \
unexpected end of file\n"), 2);
		return (1);
	}
	return (0);
}
