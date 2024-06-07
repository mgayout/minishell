/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:49:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 16:51:46 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(t_data *data, int status)
{
	if (data->envp)
		free_tab(data->envp);
	if (data->lexer)
		free_lex(&data->lexer);
	if (data->parser)
		free_par(&data->parser);
	if (data->expander)
		free_exp(&data->expander);
	if (data->exec != NULL)
		free_exe(&data->exec);
	if (status == 1)
	{
		free_env(data->env);
		free_env(data->export);
		free(data->last_prompt);
		rl_clear_history();
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	free_lex(t_lex **lexer)
{
	t_lex	*tmp;

	while (*lexer != NULL)
	{
		tmp = *lexer;
		*lexer = (*lexer)->next;
		free(tmp);
	}
}

void	free_lstr(t_lstr **lstr)
{
	t_lstr	*tmp;

	while (*lstr != NULL)
	{
		tmp = *lstr;
		*lstr = (*lstr)->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	free_par(t_par **parser)
{
	t_par	*tmp;

	while (*parser != NULL)
	{
		tmp = *parser;
		if ((*parser)->cmd)
			free_lstr(&(*parser)->cmd);
		if ((*parser)->arg)
			free_lstr(&(*parser)->arg);
		if ((*parser)->infile_lst)
			free_lstr(&(*parser)->infile_lst);
		if ((*parser)->heredoc_lst)
			free_lstr(&(*parser)->heredoc_lst);
		if ((*parser)->outfile_lst)
			free_lstr(&(*parser)->outfile_lst);
		if ((*parser)->append_lst)
			free_lstr(&(*parser)->append_lst);
		if ((*parser)->last_infile)
			free_lstr(&(*parser)->last_infile);
		if ((*parser)->last_outfile)
			free_lstr(&(*parser)->last_outfile);
		*parser = (*parser)->next;
		free(tmp);
	}
}
