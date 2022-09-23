/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:58:10 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/14 12:03:02 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	exec_cmd(t_node *start, t_node *node, t_shell *shell)
{
	bool	redir_in;
	bool	redir_out;

	g_exit.redir_interrupt = false;
	if (g_exit.interrupt == true)
		return ;
	redir_in = set_redir_in(node->cmds->redir_in);
	redir_out = set_redir_out(node->cmds->redir_out);
	if (!redir_in || !redir_out || node->cmds->word == NULL)
	{
		dup2(shell->fdin, STDIN_FILENO);
		close(shell->fdin);
		dup2(shell->fdout, STDOUT_FILENO);
		close(shell->fdout);
		return ;
	}
	if (node->cmds->is_builtin)
		exec_builtin(start, node, shell);
	else
		exec_file(start, node, shell);
	dup2(shell->fdin, STDIN_FILENO);
	dup2(shell->fdout, STDOUT_FILENO);
}
