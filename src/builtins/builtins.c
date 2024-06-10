/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:53:04 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 16:56:09 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtins(t_data *data, t_pid child)
{
	if (child.lst->builtin == 1)
		echo_builtin(data, child);
	else if (child.lst->builtin == 2)
		pwd_builtin(data, child);
	else if (child.lst->builtin == 3)
		env_builtin(data, child);
	else if (child.lst->builtin == 4)
		export_builtin(data, child);
	else if (child.lst->builtin == 5)
		unset_builtin(data, child);
	else if (child.lst->builtin == 6)
		cd_builtin(data, child);
	else if (child.lst->builtin == 7)
		exit_builtin(data, child);
}
