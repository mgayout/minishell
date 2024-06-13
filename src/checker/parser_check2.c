/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:56:27 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/08 20:56:27 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_outfile(t_lstr *last, char *file, t_lex_redir n)
{
	if (!file || file[0] == '\0')
	{
		print_error(ft_strjoin_free(ft_strjoin_free("minishell: ",
					lstrjoin(last), 2), ": ambiguous redirect\n", 1), 1);
		return (1);
	}
	if (n == OUTFILE)
		open(file, O_CREAT, 0777);
	else if (n == APPEND)
		open(file, O_APPEND, O_CREAT, 0777);
	free(file);
	return (0);
}

int	check_last_infile(t_data *data, t_par *parser)
{
	t_lstr	*tmp;
	char	*file;

	tmp = parser->last_infile;
	file = NULL;
	if (parser->heredoc)
		return (0);
	while (tmp)
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
		print_error(ft_strjoin_free(ft_strjoin_free("minishell: ", file, 2),
				": ambiguous redirect\n", 1), 1);
		return (1);
	}
	free(file);
	return (0);
}

void	wrong_heredoc(char *stop)
{
	char	*buf;

	setup_signal_handlers(true);
	while (!g_global.heredoc)
	{
		buf = readline("> ");
		handle_signal_heredoc(buf);
		if (g_global.heredoc == true || (ft_strncmp(buf, stop,
					ft_strlen(buf) - 1) == 0
				&& ft_strlen(buf) == ft_strlen(stop) + 1))
			break ;
		free(buf);
	}
	setup_signal_handlers(false);
	g_global.heredoc = false;
	free(buf);
}

void	handle_signal_heredoc(char *prompt)
{
	if (!prompt)
	{
		ft_putstr_fd("minishell : warning: here-document delimited \
by end-of-file (wanted 'stop')\n", 2);
		g_global.heredoc = true;
	}
}
