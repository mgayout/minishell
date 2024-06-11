/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:28:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/11 18:18:41 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_global;

void	print_error(char *error_msg, int error_code)
{
	ft_putstr_fd(error_msg, 2);
	g_global.error = error_code;
	free(error_msg);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	if (argc != 1 || argv[1])
		return (0);
	data.env = init_env(envp);
	data.export = init_export(data.env, envp);
	data.last_prompt = NULL;
	g_global.error = 0;
	g_global.heredoc = 0;
	setup_signal_handlers(false);
	minishell_loop(&data);
	return (0);
}

int	minishell_loop(t_data *data)
{
	init_data(data);
	data->prompt = readline("minishell$ ");
	handle_signal(data, data->prompt);
	if (init_prompt(data))
	{
		if (lexer(data) && check_lexer(data, data->lexer))
		{
			if (parser(data) && check_parser(data, data->parser))
			{
				expander(data);
				exec(data);
			}
		}
		free_all(data, 0);
	}
	return (minishell_loop(data));
}

int	init_prompt(t_data *data)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	if (!data->prompt)
		return (status);
	while (data->prompt[i] && status == 0)
	{
		if ((data->prompt[i] >= 9 && data->prompt[i] <= 13)
			|| data->prompt[i] == ' ')
			i++;
		else
			status = 1;
	}
	if (!data->last_prompt || ft_strncmp(data->last_prompt,
			data->prompt, ft_strlen(data->prompt) + 1))
		add_history(data->prompt);
	if (data->last_prompt)
		free(data->last_prompt);
	data->last_prompt = ft_strdup(data->prompt);
	return (status);
}

void	init_data(t_data *data)
{
	t_env	*env;
	int		i;

	env = data->env;
	i = 0;
	g_global.heredoc = 0;
	data->lexer = NULL;
	data->parser = NULL;
	data->expander = NULL;
	data->exec = NULL;
	data->envp = malloc(sizeof(char *) * (envsize(data->env) + 1));
	if (!data->envp)
	{
		print_error(ft_strdup("minishell: malloc error\n"), 1);
		free_all(data, 1);
		exit(g_global.error);
	}
	while (env)
	{
		data->envp[i] = ft_strjoin_free(ft_strjoin(env->name, "="),
				env->value, 1);
		i++;
		env = env->next;
	}
	data->envp[i] = NULL;
}
