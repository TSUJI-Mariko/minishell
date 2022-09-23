/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:58:10 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/10 17:14:27 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	exec_builtin(t_node *start, t_node *node, t_shell *shell)
{
	if (!ft_strncmp(node->cmds->word->str, "echo", \
			ft_strlen(node->cmds->word->str)))
		g_exit.exit_status = echo(node->cmds->word);
	else if (!ft_strncmp(node->cmds->word->str, "env", \
			ft_strlen(node->cmds->word->str)))
		g_exit.exit_status = env(node->cmds->word, shell);
	else if (!ft_strncmp(node->cmds->word->str, "pwd", \
			ft_strlen(node->cmds->word->str)))
		g_exit.exit_status = pwd(node->cmds->word);
	else if (!ft_strncmp(node->cmds->word->str, "cd", \
			ft_strlen(node->cmds->word->str)))
		g_exit.exit_status = cd(node->cmds->word, shell);
	else if (!ft_strncmp(node->cmds->word->str, "export", \
			ft_strlen(node->cmds->word->str)))
		g_exit.exit_status = builtin_export(node->cmds->word, shell);
	else if (!ft_strncmp(node->cmds->word->str, "unset", \
			ft_strlen(node->cmds->word->str)))
		g_exit.exit_status = unset(node->cmds->word, shell);
	else if (!ft_strncmp(node->cmds->word->str, \
			"exit", ft_strlen(node->cmds->word->str)))
	{
		builtin_exit(start, node->cmds->word, shell, node);
	}
	else
		no_builtin();
}

void	no_builtin(void)
{
	ft_putstr_fd("no match command\n", 2);
	g_exit.exit_status = 2;
}
