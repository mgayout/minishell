/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:51:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/23 15:03:49 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

#include "../../minishell.h"

//BUILTINS

void	exec_builtins(t_data *data, t_pid child);

//ECHO

void	echo_builtin(t_data *data, t_pid child);

//CD

int		cd_builtin(t_data *data, t_pid child);

//PWD

int		pwd_builtin(t_data *data, t_pid child);

//EXPORT

int		export_builtin(t_data *data, t_pid child);

//UNSET

int		unset_builtin(t_data *data, t_pid child);

//ENV

void	env_builtin(t_data *data, t_pid child);
void	env_error(t_data *data, char *arg);

//EXIT

int		exit_builtin(t_data *data, t_pid child);

#endif