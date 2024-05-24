/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:33 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/24 16:51:59 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_builtin(t_data *data, t_pid child)
{
	if (!child.lst->arg)
		return ;
	if (is_a_directory(child.lst->arg))
		data->error = 1;
	chdir(child.lst->arg);
}

int	is_a_directory(char *str)
{
	DIR	*tmp;
	int	file;

	tmp = opendir(str);
	if (tmp)
		return (0);
	file = open(str, O_TRUNC);
	if (!file)
		printf("bash: cd: %s: No such file or directory\n", str);
	else
		printf("bash: cd: %s: Not a directory\n", str);
	close(file);
	return (1);
}
