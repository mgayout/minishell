/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:51:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/28 14:45:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../minishell.h"

//BUILTINS

void	exec_builtins(t_data *data, t_pid child);

//ECHO

void	echo_builtin(t_pid child);
int		echo_arg(t_exp *lst);

//CD

void	cd_builtin(t_data *data, t_pid child);
int		is_a_directory(t_data *data, char *str);

//PWD

void	pwd_builtin(t_data *data, t_pid child);
int		pwd_error(t_data *data, char *arg);

//EXPORT

void	export_builtin(t_data *data, t_pid child);
void	print_export(t_data *data);

//UNSET

int		unset_builtin(t_data *data, t_pid child);

//ENV

void	env_builtin(t_data *data, t_pid child);
void	env_error(t_data *data, char *arg);

//EXIT

int		exit_builtin(t_data *data, t_pid child);

#endif