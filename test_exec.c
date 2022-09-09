/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:58:10 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/09 20:08:12 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	g_exit_status;

#include "./inc/minishell.h"

void	exec_builtin(t_node *node, t_shell *shell)
{
	if (!ft_strncmp(node->cmds->word->str, "echo", \
			ft_strlen(node->cmds->word->str)))
		g_exit_status = echo(node->cmds->word);
	else if (!ft_strncmp(node->cmds->word->str, "env", \
			ft_strlen(node->cmds->word->str)))
		g_exit_status = env(node->cmds->word, shell);
	else if (!ft_strncmp(node->cmds->word->str, "pwd", \
			ft_strlen(node->cmds->word->str)))
		g_exit_status = pwd(node->cmds->word);
	else if (!ft_strncmp(node->cmds->word->str, "cd", \
			ft_strlen(node->cmds->word->str)))
		g_exit_status = cd(node->cmds->word, shell);
	else if (!ft_strncmp(node->cmds->word->str, "export", \
			ft_strlen(node->cmds->word->str)))
		g_exit_status = export(node->cmds->word, shell);
	else if (!ft_strncmp(node->cmds->word->str, "unset", \
			ft_strlen(node->cmds->word->str)))
		g_exit_status = unset(node->cmds->word, shell);
	else if (!ft_strncmp(node->cmds->word->str, \
			"exit", ft_strlen(node->cmds->word->str)))
		builtin_exit(node->cmds->word);
	else
		no_builtin();
}

void	no_builtin(void)
{
	ft_putstr_fd("no match command\n", 2);
	g_exit_status = 2;
}

bool	set_redir_in(t_redir *redir_in)
{
	int	fd;

	if (redir_in == NULL)
		return (true);
	fd = -1;
	if (redir_in->kind == REDIR_IN)
	{
		fd = open(redir_in->str, O_RDONLY);
		if (fd < 0)
		{
			printf("minishell: %s: ", redir_in->str);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (false);
		}
	}
	else if (redir_in->kind == REDIR_HEREDOC)
		fd = redir_in->fd;
	else
		redir_in_error();
	dup2(fd, 0);
	close(fd);
	return (set_redir_in(redir_in->next));
}

void	redir_in_error(void)
{
	ft_putstr_fd("error: set_redir_in()", 2);
	g_exit_status = 1;
}

void	redir_out_error(void)
{
	ft_putstr_fd("error: set_redir_in()", 2);
	g_exit_status = 1;
}

bool	set_redir_out(t_redir *redir_out)
{
	int	fd;
	int	oflag;

	if (redir_out == NULL)
		return (true);
	oflag = 0;
	if (redir_out->kind == REDIR_OUT)
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir_out->kind == REDIR_APPEND)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	else
		redir_out_error();
	fd = open(redir_out->str, oflag, 0664);
	if (fd < 0)
	{
		printf("minishell: %s: ", redir_out->str);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (false);
	}
	dup2(fd, 1);
	close(fd);
	return (set_redir_out(redir_out->next));
}

int	fail_exec(t_node *node)
{
	g_exit_status = 126;
	if (errno == ENOENT)
		g_exit_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->cmds->pathname, 2);
	ft_putstr_fd(": Permission denied\n", 2);
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

void	exec_file(t_node *node, t_shell *shell)
{
	int		pid;
	char	**cmd_argv;
	char	**cmd_envp;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
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

void	exec_cmd(t_node *node, t_shell *shell)
{
	if (!set_redir_in(node->cmds->redir_in)
		|| !set_redir_out(node->cmds->redir_out)
		|| node->cmds->word == NULL)
	{
		dup2(shell->fdin, 1);
		dup2(shell->fdout, 0);
		g_exit_status = 1;
		return ;
	}
	if (node->cmds->is_builtin)
		exec_builtin(node, shell);
	else
		exec_file(node, shell);
	dup2(shell->fdout, 1);
	dup2(shell->fdin, 0);
}

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
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
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

void	exec_pipe(t_node *pipe_node, t_shell *shell)
{
	int	pid;
	int	sts;

	expander(pipe_node, shell);
	if (pipe_node->lhs == NULL)
		exec_no_pipe(pipe_node, shell);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			exec_multi_pipes(pipe_node, shell);
			exit(g_exit_status);
		}
		sts = 0;
		waitpid(pid, &sts, 0);
		g_exit_status = WEXITSTATUS(sts);
	}
}
