/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:22:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/31 12:25:32 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_export_arg(char **args)
{
	char	**split_arg;
	int		status;
	int		i;

	status = 0;
	i = 0;
	while (args[i])
	{
		split_arg = ft_split(args[i], '=');
		status = check_split_arg(split_arg);
		free_tab(split_arg);
		i++;
	}
	return (status);
}

int	check_split_arg(char **split_arg)
{
	int	j;
	int	status;

	status = 0;
	j = 0;
	while (split_arg[0][j])
	{
		if ((split_arg[0][j] < 'a' || split_arg[0][j] > 'z')
			&& (split_arg[0][j] < 'A' || split_arg[0][j] > 'Z'))
		{
			printf("bash: export: '%s': not a valid identifier\n", split_arg[0]);
			status = 1;
		}
		j++;
	}
	return (status);
}

void	print_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->export;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
}
