/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:28:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/21 13:14:27 by mgayout          ###   ########.fr       */
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
	data->prompt = readline("minishell :");
	if (is_a_prompt(data->prompt))
	{
		if (!data->last_prompt || ft_strncmp(data->prompt, data->last_prompt, ft_strlen(data->prompt)))
			add_history(data->prompt);
		lexer(data);
		print_lex(data);
		if (check_lexer(data->lexer))
		{
			parser(data);
			print_par(data);
			if (check_parser(data->parser))
			{
				expander(data);
				print_exp(data);
				exec(data);
			}
		}
		data->last_prompt = ft_strdup(data->prompt);
		free_all(data);	
	}
	minishell_loop(data);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	if (argc != 1 || argv[1])
		return (0);
	data.envp = envp;
	env(&data);
	//print_env(data.env);
	if (!data.envp[0])
		return (0);
	data.last_prompt = NULL;
	data.error = 0;
	minishell_loop(&data);
}
