/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:10:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/31 18:05:43 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lexer(t_data *data)
{
	int		i;

	i = 0;
	while (data->prompt[i])
	{
		while ((data->prompt[i] >= 9 && data->prompt[i] <= 13)
			|| data->prompt[i] == ' ')
			i++;
		if (i >= 1 && data->prompt[i - 1] == ' ')
			i = add_new_t_lex(data, &data->lexer, &data->prompt[i], true);
		else
			i = add_new_t_lex(data, &data->lexer, &data->prompt[i], false);
		if (i < 0)
			return (0);
	}
	return (1);
}

int	add_new_t_lex(t_data *data, t_lex **lexer, char *prompt, bool space)
{
	t_lex	*new;
	int		i;

	i = 0;
	new = new_lex();
	if (!new)
		return (-1);
	data->prompt = ft_strdup(prompt);
	if (!data->prompt)
		return (-1);
	if (prompt[0] == '>' || prompt[0] == '<' || prompt[0] == '|')
		i = token_type(new, prompt);
	else
		i = string_type(data, new, space);
	lexadd_back(lexer, new);
	return (i);
}
