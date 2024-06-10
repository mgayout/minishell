/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 14:13:51 by mgayout          ###   ########.fr       */
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
