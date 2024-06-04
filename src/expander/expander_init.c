/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:57:52 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/04 14:34:45 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "../lexer/lexer.h"

char	*dollar_exp(t_data *data, t_lstr *lst)
{
	char	*new;
	t_lstr	*tmp;

	new = NULL;
	tmp = lst;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '$') && tmp->quote != SQUOTE)
		{
			new = modify_lstr(data, tmp->str);
			free(tmp->str);
			tmp->str = ft_strdup(new);
		}
		tmp = tmp->next;
	}
	if (new)
		free(new);
	new = lstrjoin(lst);
	return (new);
}