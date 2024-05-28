/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:19:58 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/28 15:50:48 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		last->next = new;
		return ;
	}
	*lst = new;
}

/*void	exportadd(t_env **lst, t_env *new)
{
	t_env	*next;

	if (*lst != NULL)
	{
		
	}
	*lst = new;
}*/

/*t_env	*next_new_export(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if(ft_strncmp(tmp->name, new->name, ft_strlen(tmp->name)) > 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}*/
