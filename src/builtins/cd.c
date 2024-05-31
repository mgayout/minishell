/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:33 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/29 16:26:09 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_builtin(t_data *data, t_pid child)
{
	char	cwd[1024];
	t_env	*tmp;

	if (!child.lst->arg)
		return ;
	if (is_a_directory(data, child.lst->arg))
		return ;
	chdir(child.lst->arg);
	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", ft_strlen("PWD")))
			break;
		tmp = tmp->next;
	}
	if (getcwd(cwd, sizeof(cwd)))
		tmp->value = ft_strdup(cwd);
}

int	is_a_directory(t_data *data, char *str)
{
	DIR	*tmp;
	int	file;

	tmp = opendir(str);
	if (tmp)
		return (0);
	file = open(str, O_RDONLY);
	if (file == -1)
		printf("bash: cd: %s: No such file or directory\n", str);
	else
	{
		printf("bash: cd: %s: Not a directory\n", str);
		close(file);
	}
	data->error = 1;
	return (1);
}
