/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:58:10 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/10 17:14:48 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	printer_redir(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_exit.exit_status = 1;
	g_exit.redir_interrupt = true;
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
			return (printer_redir(redir_in->str), false);
	}
	else if (redir_in->kind == REDIR_HEREDOC)
		fd = redir_in->fd;
	else
		return (redir_in_error(), false);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (g_exit.redir_interrupt == false)
		return (set_redir_in(redir_in->next));
	else
		return (false);
}

void	redir_in_error(void)
{
	ft_putstr_fd("error: set_redir_in()", 2);
	g_exit.exit_status = 1;
	g_exit.redir_interrupt = true;
}

void	redir_out_error(void)
{
	ft_putstr_fd("error: set_redir_in()", 2);
	g_exit.exit_status = 1;
	g_exit.redir_interrupt = true;
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
		return (redir_out_error(), false);
	fd = open(redir_out->str, oflag, 0664);
	if (fd < 0)
		return (printer_redir(redir_out->str), false);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (g_exit.redir_interrupt == false)
		return (set_redir_out(redir_out->next));
	else
		return (false);
}
