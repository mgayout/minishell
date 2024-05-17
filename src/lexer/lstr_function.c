/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstr_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:56:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/17 18:14:42 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lstr	*new_lstr(char *str, t_lex_quote n)
{
	t_lstr	*new;

	new = (t_lstr *)ft_calloc(1, sizeof(t_lstr));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->quote = n;
	new->id = 0;
	new->heredoc = false;
	new->next = NULL;
	new->prev = NULL;
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
		new->prev = last;
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
		if (!str)
			str = ft_strdup(lst->str);
		else
			str = ft_strjoin(str, lst->str);
		lst = lst->next;
	}
	return (str);
}
