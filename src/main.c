/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:28:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/24 16:12:51 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "exec/exec.h"
#include "expander/expander.h"

int	is_a_prompt(char *str)
{
	int	i;

	if (!str || !ft_strlen(str))
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			i++;
		else
			return (1);
	}
	add_history(str);
	return (0);
}

void	minishell_loop(t_data *data)
{
	init_data(data);
	data->prompt = readline("minishell :");
	if (is_a_prompt(data->prompt))
	{
		add_history(data->prompt);
		lexer(data);
		//print_lex(data);
		if (check_lexer(data, data->lexer))
		{
			parser(data);
			//print_par(data);
			expander(data);
			//print_exp(data);
			exec(data);
		}
		free (data->last_prompt);
		data->last_prompt = ft_strdup(data->prompt);
		free_all(data);
	}
	minishell_loop(data);
}

void	init_data(t_data *data)
{
	data->lexer = NULL;
	data->parser = NULL;
	data->expander = NULL;
	data->exec = NULL;
	data->error = 0;
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	if (argc != 1 || argv[1])
		return (0);
	data.envp = envp;
	data.env = init_env(&data);
	data.last_prompt = NULL;
	minishell_loop(&data);
}
