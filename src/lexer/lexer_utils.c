/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 16:57:16 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_quotes(char *prompt)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && status != 1)
		{
			if (status == 0)
				status = 2;
			else
				status = 0;
		}
		else if (prompt[i] == '\"' && status != 2)
		{
			if (status == 0)
				status = 1;
			else
				status = 0;
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
