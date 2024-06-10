/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:57:52 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 17:32:05 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*dollar_exp(t_data *data, t_lstr *lst)
{
	char	*new;
	t_lstr	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '$') && tmp->quote != SQUOTE)
		{
			new = modify_lstr(data, tmp->str);
			free(tmp->str);
			if (new)
			{
				tmp->str = ft_strdup(new);
				free(new);	
			}
			else
				tmp->str = NULL;
		}
		tmp = tmp->next;
	}
	new = lstrjoin(lst);
	return (new);
}
