/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:22:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 16:53:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_export_arg(char **args)
{
	char	**split_arg;
	int		i;

	i = 0;
	while (args[i])
	{
		split_arg = ft_split(args[i], '=');
		if (check_name_arg(split_arg[0]))
		{
			free_tab(split_arg);
			return (1);
		}
		i++;
		free_tab(split_arg);
	}
	return (0);
}

int	check_name_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
	{
		print_error(ft_strdup("minishell: export: '=': not a valid identifier\n"), 1);
		return (1);
	}
	while (arg[i])
	{
		if ((arg[i] < 'a' || arg[i] > 'z')
			&& (arg[i] < 'A' || arg[i] > 'Z'))
			{
				print_error(ft_strjoin_free(ft_strjoin("minishell: export: '", arg), "': not a valid identifier\n", 1), 1);
				return (1);
			}
		i++;
	}
	return (0);
}

void	print_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->export;
	while (tmp && tmp->name)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}
