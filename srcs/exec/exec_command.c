/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:58:10 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/10 16:41:01 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_exit_stats;

void	exec_cmd(t_node *node, t_shell *shell)
{
	if ((!set_redir_in(node->cmds->redir_in)
		&& node->cmds->redir_out == NULL)
		|| (!set_redir_out(node->cmds->redir_out)
		&& node->cmds->redir_in == NULL)
		|| node->cmds->word == NULL)
	{
		dup2(shell->fdin, 1);
		dup2(shell->fdout, 0);
		return ;
	}
	if (node->cmds->is_builtin)
		exec_builtin(node, shell);
	else
		exec_file(node, shell);
	dup2(shell->fdout, 1);
	dup2(shell->fdin, 0);
}
