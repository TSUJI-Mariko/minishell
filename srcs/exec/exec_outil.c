/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:58:10 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/10 17:00:29 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_exit_status;

int	fail_exec(t_node *node)
{
	g_exit_status = 126;
	if (errno == ENOENT)
		g_exit_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->cmds->pathname, 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (g_exit_status);
}

bool	is_directory(char *pathname)
{
	struct stat	st;

	if (stat(pathname, &st) != 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}

char	**create_argv(t_word *word)
{
	char	**argv;
	long	len;
	t_word	*now;
	long	i;

	len = 0;
	now = word;
	while (now)
	{
		len++;
		now = now->next;
	}
	argv = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (word)
	{
		argv[i] = word->str;
		i++;
		word = word->next;
	}
	return (argv);
}

bool	check_cmd(t_cmd *cmd)
{
	if (g_exit_status == 1)
		return (false);
	if (cmd->pathname == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->word->str, 2);
		ft_putstr_fd(" command not found\n", 2);
		g_exit_status = 127;
		return (false);
	}
	if (is_directory(cmd->pathname))
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(cmd->pathname, 2);
		ft_putstr_fd(" is a directory\n", 2);
		g_exit_status = 126;
		return (false);
	}
	return (true);
}

void	set_exit_status(void)
{
	if (WIFSIGNALED(g_exit_status))
	{
		g_exit_status = 128 + WTERMSIG(g_exit_status);
		if (g_exit_status == 128 + SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
		}
	}
	else
		g_exit_status = WEXITSTATUS(g_exit_status);
}
