/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstr_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:56:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/21 18:07:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lstr	*new_lstr(void)
{
	t_lstr	*new;

	new = (t_lstr *)ft_calloc(1, sizeof(t_lstr));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->id = 0;
	new->heredoc = false;
	new->space = false;
	new->next = NULL;
	return (new);
}

t_lstr	*lstrlast(t_lstr *lst)
{
	t_lstr	*last;
	int		i;
	int		j;

	last = lst;
	if (!last)
		return (NULL);
	i = 1;
	j = lstrsize(last);
	while (i != j)
	{
		last = last->next;
		i++;
	}
	return (last);
}

int	lstrsize(t_lstr *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}

void	lstradd_back(t_lstr **lst, t_lstr *new)
{
	t_lstr	*last;

	if (*lst != NULL)
	{
		last = *lst;
		last = lstrlast(*lst);
		last->next = new;
		return ;
	}
	*lst = new;
}

char	*lstrjoin(t_lstr *lst)
{
	char	*str;
	
	str = NULL;
	while (lst)
	{
		if (lst->str)
		{
			if (!str)
				str = ft_strdup(lst->str);
			else
			{
				if (lst->space)
					str = ft_strjoin(ft_strjoin(str, " "), lst->str);
				else
					str = ft_strjoin(str, lst->str);
			}	
		}
		lst = lst->next;
	}
	return (str);
}
