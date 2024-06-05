/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:51:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/05 16:15:05 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../minishell.h"

//BUILTINS

void	exec_builtins(t_data *data, t_pid child);

//ECHO

void	echo_builtin(t_data *data, t_pid child);
int		echo_arg(t_exp *lst);

//CD

void	cd_builtin(t_data *data, t_pid child);
int		is_a_directory(t_data *data, char *str);

//PWD

void	pwd_builtin(t_data *data, t_pid child);
int		pwd_error(t_data *data, char *arg);

//EXPORT

void	export_builtin(t_data *data, t_pid child);
void	init_new_export(t_data *data, char *arg);
void	init_new_env(t_data *data, char *arg);
void	find_pos_export(t_data *data, t_env *new);
void	add_new_export(t_env *pos, t_env *new);

//EXPORT_UTILS

int		check_export_arg(t_data *data, char **args);
int		check_name_arg(t_data *data, char *arg);
void	print_export(t_data *data);

//UNSET

void	unset_builtin(t_data *data, t_pid child);
void	search_pos(t_data *data, char *arg);
void	remove_var(t_data *data, t_env *tmp, int n);
void	remove_all(t_data *data, t_env *tmp, int n);
void	remove_first(t_data *data, t_env *tmp, int n);
void	remove_last(t_env *tmp);

//ENV

void	env_builtin(t_data *data, t_pid child);

//EXIT

void	exit_builtin(t_data *data, t_pid child);
void	print_exit(t_data *data, char *arg, int status);

#endif