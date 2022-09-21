/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:49:18 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/08 16:57:40 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	signal_init_handle(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit.exit_status = 128 + SIGINT;
}

void	signal_init(void)
{
	signal(SIGINT, signal_init_handle);
	signal(SIGQUIT, SIG_IGN);
	g_exit.interrupt = false;
}
