/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:59 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/29 16:28:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd_builtin(t_data *data, t_pid child)
{
	t_env	*tmp;

	if (child.lst->arg)
		if (pwd_error(data, child.lst->arg))
			return;
	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", ft_strlen("PWD")))
			printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

int	pwd_error(t_data *data, char *arg)
{
	if (arg[0] == '-' && &arg[1])
	{
		data->error = 2;
		printf("pwd: invalid option -- '%s'\n", &arg[1]);
		return (1);
	}
	return (0);
}