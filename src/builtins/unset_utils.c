/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:08:54 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 21:08:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_all(t_data *data, t_env *tmp, int n)
{
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	if (n == 0)
		data->export = NULL;
	else
		data->env = NULL;
}

void	remove_first(t_data *data, t_env *tmp, int n)
{
	if (n == 0)
		data->export = data->export->next;
	else
		data->env = data->env->next;
	data->env->prev = NULL;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}

void	remove_last(t_env *tmp)
{
	t_env	*prev;

	prev = tmp->prev;
	prev->next = NULL;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}
