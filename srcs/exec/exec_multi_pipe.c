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

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	exec_no_pipe(t_node *pipe_node, t_shell *shell)
{
	exec_cmd(pipe_node, pipe_node->rhs, shell);
}

void	close_all(int fd_0, int fd_1)
{
	close(fd_0);
	close(fd_1);
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
			dup2(fd[0], STDIN_FILENO);
		close_all(fd[1], fd[0]);
		close_all(shell->fdin, shell->fdout);
		exec_cmd(pipe_node, pipe_node->rhs, shell);
		exit(g_exit.exit_status);
	}
	else
	{
		dup2(fd[1], STDOUT_FILENO);
		close_all(fd[1], fd[0]);
		exec_multi_pipes(pipe_node->lhs, shell);
	}
	waitpid(pid, &(g_exit.exit_status), 0);
	g_exit.exit_status = WEXITSTATUS(g_exit.exit_status);
}
