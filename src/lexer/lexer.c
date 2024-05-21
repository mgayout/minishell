/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:10:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/21 16:53:03 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer(t_data *data)
{
	int		i;
	bool	space;

	i = 0;
	data->lexer = NULL;
	space = false;
	while (data->prompt[i])
	{
		while ((data->prompt[i] >= 9 && data->prompt[i] <= 13) || data->prompt[i] == ' ')
		{
			space = true;
			i++;
		}
		i = add_new_t_lex(data, &data->lexer, &data->prompt[i], space);
	}
}

int	add_new_t_lex(t_data *data, t_lex **lexer, char *prompt, bool space)
{
	t_lex	*new;
	int		i;

	i = 0;
	new = new_lex();
	data->prompt = ft_strdup(prompt);
	if (prompt[0] == '>' || prompt[0] == '<' || prompt[0] == '|')
		i = token_type(new, prompt);
	else
		i = string_type(data, new, space);
	lexadd_back(lexer, new);
	return (i);
}
