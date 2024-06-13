/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:35:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/13 16:32:04 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_heredoc(t_data *data, char *stop)
{
	char	*buf;
	int		file;

	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	setup_signal_handlers(true);
	while (!g_global.heredoc)
	{
		write(data->exec->std_in, "> ", 2);
		buf = get_next_line(data->exec->std_in);
		handle_signal_heredoc(buf);
		if (g_global.heredoc == true || (ft_strncmp(buf, stop,
					ft_strlen(buf) - 1) == 0
				&& (ft_strlen(buf) - 1) == ft_strlen(stop)))
			break ;
		else
			write(file, buf, ft_strlen(buf));
		free(buf);
	}
	setup_signal_handlers(false);
	g_global.heredoc = false;
	free(buf);
	close(file);
	return (open(".temp", O_RDONLY));
}
