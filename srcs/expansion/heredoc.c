/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:41:43 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/14 12:05:07 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_heredoc_eof(char *line, char *eof)
{
	long	line_len;
	long	eof_len;

	line_len = ft_strlen(line);
	eof_len = ft_strlen(eof);
	return (line_len > 0 && line_len == eof_len
		&& ft_strncmp(line, eof, line_len) == 0);
}

void	write_heredoc_to_fd(t_redir *redir, t_shell *shell, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (is_heredoc_eof(line, redir->str))
		{
			free(line);
			break ;
		}
		if (line)
			line = expand_var_heredoc(redir, line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	set_heredoc(t_redir *redir, t_shell *shell)
{
	int		fd[2];

	if (redir == NULL)
		return ;
	if (g_exit.interrupt == true)
		return ;
	if (redir->kind == REDIR_HEREDOC)
	{
		pipe(fd);
		redir->fd = fd[0];
		write_heredoc_to_fd(redir, shell, fd[1]);
		dup2(shell->fdin, 0);
		close(fd[1]);
	}
	set_heredoc(redir->next, shell);
}

void	expander_set_heredoc(t_node *node, t_shell *shell)
{
	if (node == NULL)
		return ;
	if (node->kind == COMMAND)
	{
		remove_quote_heredoc(node->cmds->redir_in);
		set_heredoc(node->cmds->redir_in, shell);
	}
	else
	{
		expander_set_heredoc(node->rhs, shell);
		expander_set_heredoc(node->lhs, shell);
	}
}
