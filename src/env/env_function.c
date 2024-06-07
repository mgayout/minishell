/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:19:58 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 16:52:52 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*envlast(t_env *lst)
{
	t_env	*last;
	int		i;
	int		j;

	last = lst;
	if (!last)
		return (NULL);
	i = 1;
	j = envsize(last);
	while (i != j)
	{
		last = last->next;
		i++;
	}
	return (last);
}

int	envsize(t_env *lst)
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

void	envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst != NULL)
	{
		last = *lst;
		last = envlast(*lst);
		new->prev = last;
		last->next = new;
		return ;
	}
	*lst = new;
}
