/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:33 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 21:00:59 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_builtin(t_data *data, t_pid child)
{
	char	cwd[1024];
	t_env	*tmp;

	if (!child.lst->arg)
		return ;
	if (is_a_directory(child.lst->arg))
		return ;
	chdir(child.lst->arg);
	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", ft_strlen("PWD")))
			break ;
		tmp = tmp->next;
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		free(tmp->value);
		tmp->value = ft_strdup(cwd);
	}
}

int	is_a_directory(char *str)
{
	DIR	*tmp;
	int	file;

	tmp = opendir(str);
	if (tmp)
	{
		closedir(tmp);
		return (0);
	}
	file = open(str, O_RDONLY);
	if (file == -1)
		print_error(ft_strjoin_free(ft_strjoin("minishell: cd: ", str),
				": No such file or directory\n", 1), 1);
	else
	{
		print_error(ft_strjoin_free(ft_strjoin("minishell: cd: ", str),
				": Not a directory\n", 1), 1);
		close(file);
	}
	return (1);
}
