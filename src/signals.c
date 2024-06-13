/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:23:06 by mgayout           #+#    #+#             */
/*   Updated: 2024/06/13 15:55:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	g_global.heredoc = true;
}

void	setup_signal_handlers(bool heredoc)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (!heredoc)
		sa_int.sa_handler = sigint_handler;
	else
		sa_int.sa_handler = sigint_handler_heredoc;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	handle_signal(t_data *data, char *prompt)
{
	if (!prompt)
	{
		ft_putstr_fd("exit\n", 2);
		free_all(data, 1);
		exit(g_global.error);
	}
}
