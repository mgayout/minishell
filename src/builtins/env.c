/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:17 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/23 15:04:38 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_builtin(t_data *data, t_pid child)
{
	t_env	*tmp;
	int		i;

	if (child.lst->arg)
		return(env_error(data, child.lst->arg));
	tmp = data->env;
	while (tmp)
	{
		i = 0;
		printf("%s=", tmp->name);
		while (tmp->value[i] != NULL)
		{
			printf("%s", tmp->value[i]);
			i++;
			if (tmp->value[i])
				printf(":");
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	env_error(t_data *data, char *arg)
{
	data->error = 1;
	if (arg[0] == '-')
	{
		if (&arg[1])
			printf("env: invalid option -- '%s'\n", &arg[1]);
		else
			printf("env: invalid option\n");
	}
	else
		printf("env: '%s': No such file or directory\n", arg);
}
