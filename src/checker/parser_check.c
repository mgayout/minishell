/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:09:21 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 21:09:44 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_parser(t_data *data, t_par *parser)
{
	t_par	*tmp;

	tmp = parser;
	while (tmp)
	{
		check_heredoc(tmp);
		if (tmp->infile_lst && check_infile(data, tmp))
			return (0);
		if (tmp->last_infile && check_last_infile(data, tmp))
			return (0);
		if (tmp->outfile_lst && check_outfile(data, tmp, OUTFILE))
			return (0);
		if (tmp->outfile_lst && check_outfile(data, tmp, APPEND))
			return (0);
		if (tmp->last_outfile && check_last_outfile(data, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	check_heredoc(t_par *parser)
{
	t_lstr	*tmp;
	char	*stop;
	int		id;

	tmp = parser->heredoc_lst;
	while (tmp)
	{
		stop = NULL;
		id = tmp->id;
		while (tmp && tmp->id <= id)
		{
			if (!stop)
				stop = ft_strdup(tmp->str);
			else
				stop = ft_strjoin_free(stop, tmp->str, 1);
			tmp = tmp->next;
		}
		wrong_heredoc(stop);
		free(stop);
	}
}

int	check_infile(t_data *data, t_par *parser)
{
	t_lstr	*tmp;
	char	*file;
	int		id;

	tmp = parser->infile_lst;
	while (tmp)
	{
		file = NULL;
		id = tmp->id;
		while (tmp && tmp->id <= id)
		{
			if (!file)
				file = modify_lstr(data, tmp->str);
			else
				file = ft_strjoin_free(file, modify_lstr(data, tmp->str), 1);
			tmp = tmp->next;
		}
		if (open(file, O_RDONLY) == -1)
			return (print_check_infile(file));
		free(file);
	}
	return (0);
}

int	print_check_infile(char *file)
{
	print_error(ft_strjoin_free(ft_strjoin("minishell: ", file),
			": No such file or directory\n", 1), 1);
	free(file);
	return (1);
}

int	check_outfile(t_data *data, t_par *parser, t_lex_redir n)
{
	t_lstr	*tmp;
	t_lstr	*last;
	char	*file;
	int		id;

	tmp = parser->outfile_lst;
	if (n == APPEND)
		tmp = parser->append_lst;
	while (tmp)
	{
		last = tmp;
		file = NULL;
		id = tmp->id;
		while (tmp && tmp->id <= id)
		{
			if (!file)
				file = modify_lstr(data, tmp->str);
			else
				file = ft_strjoin_free(file, modify_lstr(data, tmp->str), 1);
			tmp = tmp->next;
		}
		if (create_outfile(last, file, n))
			return (1);
	}
	return (0);
}
