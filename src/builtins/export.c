/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:47:23 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/28 14:45:58 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	export_builtin(t_data *data, t_pid child)
{
	if (!data->prompt)
		return;
	if (!child.lst->arg)
		print_export(data);
	return ;
}

void	print_export(t_data *data)
{
	t_env	*tmp;
	int		i;

	tmp = data->export;
	while (tmp)
	{
		i = 0;
		printf("declare -x %s=\"", tmp->name);
		while (tmp->value[i])
		{
			printf("%s", tmp->value[i]);
			i++;
			if (tmp->value[i])
				printf(":");
		}
		printf("\"\n");
		tmp = tmp->next;
	}
}
