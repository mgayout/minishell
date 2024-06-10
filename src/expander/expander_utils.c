/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:29:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 15:29:24 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_dollar(char *str)
{
	int	dollar;
	int	status;
	int	i;

	dollar = 0;
	status = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (status == 0)
			{
				dollar++;
				if (str[i + 1] == '$')
					status++;
			}
			else if (status == 1)
				status = 0;
		}
		i++;
	}
	return (dollar);
}

char	**copy_tab(char **old)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!old)
		return (NULL);
	while (old[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		new[j] = ft_strdup(old[j]);
		j++;
	}
	new[j] = NULL;
	return (new);
}

int	is_a_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (2);
	else if (!ft_strncmp(cmd, "env", 4))
		return (3);
	else if (!ft_strncmp(cmd, "export", 7))
		return (4);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (5);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (6);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (7);
	return (0);
}
