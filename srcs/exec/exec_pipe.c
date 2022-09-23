/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:02:19 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/09 18:47:35 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

extern t_exit	g_exit;

void	exec_pipe(t_node *pipe_node, t_shell *shell)
{
	int	pid;
	int	sts;

	expander(pipe_node, shell);
	if (pipe_node->lhs == NULL)
		return (exec_no_pipe(pipe_node, shell));
	pid = my_fork();
	if (pid == 0)
	{
		exec_multi_pipes(pipe_node, shell);
		close(shell->fdin);
		close(shell->fdout);
		free_all(shell);
		free_node(pipe_node);
		exit(g_exit.exit_status);
	}
	sts = 0;
	waitpid(pid, &sts, 0);
	g_exit.exit_status = WEXITSTATUS(sts);
}
