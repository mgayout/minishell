/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:08:47 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 16:52:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		fill_env(&env, envp[i]);
		i++;
	}
	return (env);
}

void	fill_env(t_env **env, char *envp)
{
	t_env	*new;
	int		i;

	i = 0;
	while (ft_strncmp(&envp[i], "=", 1) != 0)
		i++;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = malloc(sizeof(char) * i + 1);
	ft_strlcpy(new->name, envp, i + 1);
	new->value = ft_strdup(&envp[i + 1]);
	new->next = NULL;
	new->prev = NULL;
	envadd_back(env, new);
}

t_env	*init_export(t_env *env, char **envp)
{
	t_env	*export;

	export = NULL;
	while (export_missing(env, export))
		find_export_target(&export, envp);
	return (export);
}

void	fill_export(t_env **export, char *target)
{
	t_env	*new;
	int		i;

	i = 0;
	while (ft_strncmp(&target[i], "=", 1) != 0)
		i++;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = malloc(sizeof(char) * i + 1);
	ft_strlcpy(new->name, target, i + 1);
	new->value = ft_strdup(&target[i + 1]);
	new->next = NULL;
	new->prev = NULL;
	envadd_back(export, new);
}
