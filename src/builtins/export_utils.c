/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:22:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/10 14:13:00 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_export_arg(t_data *data, char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '=')
		{
			print_error(ft_strdup("minishell: export: '=': \
not a valid identifier\n"), 1);
		}
		else if (!check_name_arg(ft_split(args[i], '=')))
		{
			init_new_export(data, args[i]);
			if (ft_strchr(args[i], '='))
				init_new_env(data, args[i]);
		}
		i++;
	}
}

int	check_name_arg(char **arg)
{
	int	i;

	i = 0;
	if (!arg[0])
	{
		print_error(ft_strdup("minishell: export: '=': \
not a valid identifier\n"), 1);
		return (1);
	}
	while (arg[0][i])
	{
		if ((arg[0][i] < 'a' || arg[0][i] > 'z')
			&& (arg[0][i] < 'A' || arg[0][i] > 'Z'))
		{
			print_error(ft_strjoin_free(ft_strjoin("minishell: export: '",
						arg[0]), "': not a valid identifier\n", 1), 1);
			free_tab(arg);
			return (1);
		}
		i++;
	}
	free_tab(arg);
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
