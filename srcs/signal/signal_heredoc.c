/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:37:54 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/26 19:37:56 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signal_heredoc_handle(int signal)
{
	(void)signal;
	//shell->interrupt = true;
	g_exit_status = 130;
	close(0);
	ft_putstr_fd("\n", 2);
}

void	signal_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_heredoc_handle);
}
