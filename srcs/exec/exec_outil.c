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

#include "../../includes/minishell.h"

extern t_exit	g_exit;

int	fail_exec(char *cmd)
{
	g_exit.exit_status = 126;
	if (errno == ENOENT)
		g_exit.exit_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (free(cmd), g_exit.exit_status);
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
	if (!argv)
		return (NULL);
	i = 0;
	while (word)
	{
		argv[i++] = strdup(word->str);
		word = word->next;
	}
	return (argv);
}

bool	check_cmd(t_cmd *cmd)
{
	if (cmd->pathname == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->word->str, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit.exit_status = 127;
		return (false);
	}
	if (is_directory(cmd->pathname))
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(cmd->pathname, 2);
		ft_putstr_fd(" is a directory\n", 2);
		g_exit.exit_status = 126;
		return (false);
	}
	return (true);
}

void	set_exit_status(void)
{
	if (WIFSIGNALED(g_exit.exit_status))
	{
		g_exit.exit_status = 128 + WTERMSIG(g_exit.exit_status);
		if (g_exit.exit_status == 128 + SIGQUIT)
			return (ft_putstr_fd("Quit (core dumped)\n", 2), (void)0);
	}
	else
		g_exit.exit_status = WEXITSTATUS(g_exit.exit_status);
}
