/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:17 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/29 16:34:52 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_builtin(t_data *data, t_pid child)
{
	t_env	*tmp;

	if (child.lst->arg)
		return(env_error(data, child.lst->arg));
	tmp = data->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	env_error(t_data *data, char *arg)
{
	data->error = 1;
	if (arg[0] == '-' && &arg[1])
		printf("env: invalid option -- '%s'\n", &arg[1]);
	else
		printf("env: '%s': No such file or directory\n", arg);
}
