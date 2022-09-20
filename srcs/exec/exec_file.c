/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:58:10 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/10 17:15:09 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

void	exec_file(t_node *node, t_shell *shell)
{
	int		pid;
	char	**cmd_argv;
	char	**cmd_envp;

	pid = my_fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (!check_cmd(node->cmds))
			exit(g_exit_status);
		cmd_argv = create_argv(node->cmds->word);
		cmd_envp = create_envp(shell);
		execve(node->cmds->pathname, cmd_argv, cmd_envp);
		free(cmd_argv);
		free_envp(cmd_envp);
		exit(fail_exec(node));
	}
	waitpid(pid, &(g_exit_status), 0);
	set_exit_status();
}
