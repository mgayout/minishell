/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:48:59 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 21:11:00 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_missing(t_env *env, t_env *export)
{
	t_env	*env_tmp;
	t_env	*export_tmp;

	if (!export)
		return (1);
	env_tmp = env;
	export_tmp = export;
	while (env_tmp)
	{
		if (env_tmp->name[0] != '_')
		{
			while (export_tmp && ft_strncmp(env_tmp->name, export_tmp->name,
					ft_strlen(env_tmp->name)))
				export_tmp = export_tmp->next;
			if (!export_tmp)
				return (1);
			export_tmp = export;
		}
		env_tmp = env_tmp->next;
	}
	return (0);
}

void	find_export_target(t_env **export, char **envp)
{
	char	*target;
	int		i;

	target = NULL;
	i = 0;
	while (envp[i])
	{
		if (!target)
			target = ft_strdup(envp[i]);
		else if (is_before(export, target, envp[i]))
		{
			free(target);
			target = ft_strdup(envp[i]);
		}
		i++;
	}
	fill_export(export, target);
	free(target);
}

int	is_before(t_env **export, char *target, char *envp)
{
	int		result;
	int		letter;

	result = 0;
	letter = 0;
	while (!result && (target[letter] != '\0' || envp[letter] != '\0'))
	{
		result = (unsigned char)target[letter] - (unsigned char)envp[letter];
		letter++;
	}
	if (is_in_export(export, envp))
		return (0);
	if (is_in_export(export, target))
		return (1);
	if ((!result && target[letter] == '\0') || result > 0)
		return (1);
	return (0);
}

int	is_in_export(t_env **export, char *target)
{
	t_env	*tmp;
	int		max;

	max = 0;
	while (target[max] != '=')
		max++;
	tmp = *export;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, target, max))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
