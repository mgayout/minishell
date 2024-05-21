/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:24:36 by mgayout           #+#    #+#             */
/*   Updated: 2024/05/21 17:36:34 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "../lexer/lexer.h"

void	expander(t_data *data)
{
	t_exp	*tmp;
	t_par	*parser;

	data->expander = NULL;
	parser = data->parser;
	while (parser != NULL)
	{
		tmp = init_expander(data, parser);
		expadd_back(&data->expander, tmp);
		parser = parser->next;
	}
}

t_exp	*init_expander(t_data *data, t_par *parser)
{
	t_exp	*expander;

	expander = malloc(sizeof(t_exp));
	expander->id = parser->id;
	//printf("id %d\n", expander->id);
	expander->cmd = dollar_exp(data, parser->cmd);
	//printf("cmd %s\n", expander->cmd);
	expander->builtin = is_a_builtin(expander->cmd);
	//printf("builtin %d\n", expander->builtin);
	expander->arg = dollar_exp(data, parser->arg);
	//printf("arg %s\n", expander->arg);
	expander->infile = check_infiles(data, parser->infile, parser->infile_count);
	//printf("infile %s\n", expander->infile);
	expander->outfile = open_outfiles(data, parser->outfile, parser->outfile_count);
	//printf("outfile %s\n", expander->outfile);
	expander->pipein = parser->pipein;
	expander->pipeout = parser->pipeout;
	expander->append = parser->append;
	expander->heredoc = false;
	expander->prev = NULL;
	expander->next = NULL;
	return (expander);
}

char	*dollar_exp(t_data *data, t_lstr *lst)
{
	t_lstr	*tmp;
	char	*new;

	tmp = lst;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '$'))
			tmp->str = modify_expander(data, tmp->str);
		tmp = tmp->next;
	}
	new = lstrjoin(lst);	
	return (new);
}

char	*check_infiles(t_data *data, t_lstr *infile, int count)
{
	t_lstr	*lst;
	char	*file;
	int		i;
	int		id;

	lst = infile;
	file = NULL;
	i = 0;
	while (i != count)
	{
		id = lst->id;
		file = joinfile(data, lst, id);
		if (lst->heredoc)
			wrong_heredoc(file);
		if (id < count)
			while (lst->id <= id)
				lst = lst->next;
		i++;
	}
	return (file);
}

char	*joinfile(t_data *data, t_lstr *lst, int count)
{
	char	*file;

	file = NULL;
	while (lst && lst->id <= count)
	{
		if (ft_strchr(lst->str, '$'))
			lst->str = modify_expander(data, lst->str);
		if (!file)
			file = ft_strdup(lst->str);
		else
			file = ft_strjoin(file, lst->str);
		lst = lst->next;
	}
	return (file);
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

char	*open_outfiles(t_data *data, t_lstr *outfile, int count)
{
	t_lstr	*lst;
	char	*file;
	int		i;
	int		id;

	lst = outfile;
	file = NULL;
	i = 0;
	while (i != count)
	{
		id = lst->id;
		file = joinfile(data, lst, id);
		open(file, O_CREAT, 0777);
		if (id < count)
			while (lst->id <= id)
				lst = lst->next;
		i++;
	}
	return (file);
}
