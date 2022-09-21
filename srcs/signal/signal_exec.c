/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:51:53 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/08 16:56:01 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	signal_exec_handle(int signal)
{
	g_exit.exit_status += signal;
	if (signal == 2)
	{
		g_exit.exit_status = 128 + SIGINT;
		g_exit.interrupt = true;
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_exec(void)
{
	signal(SIGINT, signal_exec_handle);
	signal(SIGQUIT, SIG_IGN);
}
