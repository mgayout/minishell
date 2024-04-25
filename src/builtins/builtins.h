/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:51:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/25 17:42:50 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

#include "../../minishell.h"

//BUILTINS

void	exec_builtins(t_data *data);

//ECHO

int	echo_builtin(void);

//CD

int		cd_builtin(void);

//PWD

int		pwd_builtin(void);

//EXPORT

int		export_builtin(void);

//UNSET

int		unset_builtin(void);

//ENV
int		env_builtin(void);

//EXIT

int		exit_builtin(void);

#endif