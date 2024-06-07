/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:35:31 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/07 16:52:46 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_heredoc(t_data *data, char *stop)
{
	char	*buf;
	int		file;

	file = open(".temp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		write(data->exec->std_out, "> ", 2);
		buf = get_next_line(data->exec->std_in);
		if (ft_strncmp(buf, stop, ft_strlen(buf) - 1) == 0
			&& ft_strlen(buf) == ft_strlen(stop) + 1)
			break ;
		else
			write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	return (open(".temp", O_RDONLY));
}
