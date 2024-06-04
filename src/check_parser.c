/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:09:21 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/04 17:09:32 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer/lexer.h"
#include "expander/expander.h"

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
		{
			print_error(data, ft_strjoin_free(ft_strjoin_free("minishell: ", file, 2), ": No such file or directory\n", 1), 1);
			return (1);
		}
		free(file);
	}
	return (0);
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
		if (create_outfile(data, last, file, n))
			return (1);
	}
	return (0);
}

int	create_outfile(t_data *data, t_lstr *last, char *file, t_lex_redir n)
{
	if (!file || file[0] == '\0')
	{
		print_error(data, ft_strjoin_free(ft_strjoin_free("minishell: ", lstrjoin(last), 2), ": ambiguous redirect\n", 1), 1);
		return (1);
	}
	if (n == OUTFILE)
		open(file, O_CREAT, 0777);
	else if (n == APPEND)
		open(file, O_TRUNC, O_CREAT, 0777);
	free(file);
	return (0);
}

int	check_last_infile(t_data *data, t_par *parser)
{
	t_lstr	*tmp;
	char	*file;

	tmp = parser->last_infile;
	if (parser->heredoc)
		return (1);
	while (tmp)
	{
		if (!file)
			file = modify_lstr(data, tmp->str);
		else
			file = ft_strjoin_free(file, modify_lstr(data, tmp->str), 1);
		tmp = tmp->next;
	}
	if (open(file, O_RDONLY) == -1)
	{
		print_error(data, ft_strjoin_free(ft_strjoin_free("minishell: ", file, 2), ": No such file or directory\n", 1), 1);
		return (1);
	}
	free(file);
	return (0);
}

int	check_last_outfile(t_data *data, t_par *parser)
{
	t_lstr	*tmp;
	char	*file;

	tmp = parser->last_outfile;
	file = NULL;
	while (tmp)
	{
		if (!file)
			file = modify_lstr(data, tmp->str);
		else
			file = ft_strjoin_free(file, modify_lstr(data, tmp->str), 1);
		tmp = tmp->next;
	}
	if (!file || file[0] == '\0')
	{
		free(file);
		file = lstrjoin(parser->last_outfile);
		printf("file = %s\n", file);
		print_error(data, ft_strjoin_free(ft_strjoin_free("minishell: ", file, 2), ": ambiguous redirect\n", 1), 1);
		return (1);
	}
	return (0);
}

void	wrong_heredoc(char *stop)
{
	char	*buf;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		buf = get_next_line(STDIN_FILENO);
		if (ft_strncmp(buf, stop, ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(stop) + 1)
			break ;
		free(buf);
	}
	free(buf);
}
