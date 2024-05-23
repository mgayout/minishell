/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/23 17:42:09 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_errors	count_quotes(char *prompt)
{
	int	i;
	t_errors status;

	i = 0;
	status = NOTHING;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && status != NO_EOF_DQ)
		{
			if (status == NOTHING)
				status = NO_EOF_SQ;
			else
				status = NOTHING;
		}
		else if (prompt[i] == '\"' && status != NO_EOF_SQ)
		{
			if (status == NOTHING)
				status = NO_EOF_DQ;
			else
				status = NOTHING;
		}
		i++;
	}
	return (status);
}

void	print_lex(t_data *data)
{
	t_lex	*tmp;
	t_lstr	*tmp2;
	int		i;

	tmp = data->lexer;
	i = 1;
	printf("\nLEXER\n\n");
	while (tmp != NULL)
	{
		tmp2 = tmp->data;
		printf("lst n* %d\n", i);
		printf("type = %d\n", tmp->type);
		if (tmp->type == 1)
			printf("redir = %d\n", tmp->redir);
		else if (tmp->type == 2)
			while (tmp2)
			{
				printf("data = %s\n", tmp2->str);
				tmp2 = tmp2->next;	
			}
		tmp = tmp->next;
		i++;
	}
}
