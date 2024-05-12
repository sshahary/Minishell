/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:44:33 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/12 22:20:25 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_sigint(int sig);

void	configure_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHO | ICANON | ISIG);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	signal_handler(void)
{
	struct	sigaction sig_int;
	struct	sigaction sig_quit;

	configure_terminal();
	ft_memset(&sig_int, 0, sizeof(struct sigaction));
	ft_memset(&sig_quit, 0, sizeof(struct sigaction));
	sig_int.sa_handler = handle_sigint;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	if (!g_sig)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}