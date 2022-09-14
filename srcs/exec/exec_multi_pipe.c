/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:58:10 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/10 16:41:40 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_exit_status;

void	exec_no_pipe(t_node *pipe_node, t_shell *shell)
{
	exec_cmd(pipe_node->rhs, shell);
}

void	exec_multi_pipes(t_node *pipe_node, t_shell *shell)
{
	int	fd[2];
	int	pid;

	if (pipe_node == NULL)
		return ;
	pipe(fd);
	pid = my_fork();
	if (pid == 0)
	{
		if (pipe_node->lhs)
			dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		exec_cmd(pipe_node->rhs, shell);
		exit(g_exit_status);
	}
	else
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		exec_multi_pipes(pipe_node->lhs, shell);
	}
	waitpid(pid, &(g_exit_status), 0);
	g_exit_status = WEXITSTATUS(g_exit_status);
}