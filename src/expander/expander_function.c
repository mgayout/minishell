/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:10:25 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/04 11:18:29 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_exp	*new_exp(void)
{
	t_exp	*new;

	new = ft_calloc(1, sizeof(t_exp));
	if (!new)
		return (NULL);
	new->id = 0;
	new->cmd = NULL;
	new->builtin = 0;
	new->arg = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->pipein = false;
	new->pipeout = false;
	new->heredoc = false;
	new->append = false;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_exp	*explast(t_exp *lst)
{
	t_exp	*last;
	int		i;
	int		j;

	last = lst;
	if (!last)
		return (NULL);
	i = 1;
	j = expsize(last);
	while (i != j)
	{
		last = last->next;
		i++;
	}
	return (last);
}

int	expsize(t_exp *lst)
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

void	expadd_back(t_exp **lst, t_exp *new)
{
	t_exp	*last;

	if (*lst != NULL)
	{
		last = *lst;
		last = explast(*lst);
		new->prev = last;
		last->next = new;
		return ;
	}
	*lst = new;
}
