/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:08:47 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/28 17:27:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_env(t_data *data)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	while (data->envp[i] != NULL)
	{
		fill_env(&env, data->envp[i]);
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
	new->value = ft_split(&envp[i + 1], ':');
	new->next = NULL;
	new->prev = NULL;
	envadd_back(env, new);
}

/*t_env	*init_export(t_data *data)
{
	t_env	*export;

	export = NULL;
	while (1)
	{
		
	}
	return (export);
}*/

t_env	*fill_export(char	*envp)
{
	t_env	*new;
	int		i;

	new = NULL;
	i = 0;
	while (ft_strncmp(&envp[i], "=", 1) != 0)
		i++;
	new = malloc(sizeof(t_env));
	if (!new)
		return (new);
	new->name = malloc(sizeof(char) * i + 1);
	ft_strlcpy(new->name, envp, i + 1);
	new->value = ft_split(&envp[i + 1], ':');
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	print_env(t_env *env)
{
	int	i;

	while (env != NULL)
	{
		i = 0;
		printf("Name = %s\n", env->name);
		while (env->value[i] != NULL)
		{
			printf("Value = %s\n", env->value[i]);
			i++;
		}
		env = env->next;
	}
}
