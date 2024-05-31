/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:48:41 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/31 17:51:06 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exit_builtin(t_data *data, t_pid child)
{
	ft_putstr_fd("exit\n", 2);
	if (child.lst->arg)
		print_error(data, ft_strjoin_free(ft_strjoin("bash: exit: ", child.lst->arg), ": numeric argument required\n", 1), 2);
	data->exit = true;
}
