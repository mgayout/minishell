/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:49:55 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/31 13:59:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../minishell.h"

//ENV

t_env	*init_env(char **envp);
void	fill_env(t_env **env, char *envp);
t_env	*init_export(t_data *data, char **envp);
void	fill_export(t_env **export, char *target);

//EXPORT

int		export_missing(t_env *env, t_env *export);
void	find_export_target(t_env **export, char **envp);
int		is_before(t_env **export, char *target, char *envp);
int		is_in_export(t_env **export, char *target);

//ENV_FUNCTION

t_env	*envlast(t_env *lst);
int		envsize(t_env *lst);
void	envadd_back(t_env **lst, t_env *new);

#endif