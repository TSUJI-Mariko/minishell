/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:48:33 by msuji             #+#    #+#             */
/*   Updated: 2022/09/08 15:50:52 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exit	g_exit;

static char	*ft_readline(char **res)
{
	char	*path;
	int		i;

	path = getcwd(NULL, 0);
	if (!path)
		return (readline("\e[33m[minishell]>\e[0m "));
	i = ft_strlen(path) - 1;
	while (path[i] && path[i] != '/')
		i--;
	*res = ft_calloc(sizeof(char), 60);
	if (!*res)
		return (free(path), readline("\e[33m[minishell]>\e[0m "));
	ft_strlcat(*res, "\e[33m[minishell]\e[0m \e[34m", 27 + 1);
	ft_strlcat(*res, path + i + 1, 27 + ft_strlen(path + i + 1) + 1);
	ft_strlcat(*res, "\e[0m-> ", 27 + ft_strlen(path + i + 1) + 8 + 1);
	return (free(path), readline(*res));
}

void	start_command(char *str, t_shell *shell)
{
	t_command	*command_line;
	t_node		*node;

	command_line = lexer(str);
	if (command_line == NULL)
		return (g_exit.exit_status = 2, (void)0);
	node = parser(command_line->first_token);
	free_lexer(command_line);
	if (node)
	{
		signal_heredoc();
		expander_set_heredoc(node, shell);
		signal_exec();
		exec_pipe(node, shell);
		free_node(node);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;
	char	*res;

	if (argc)
		shell = create_shell(envp, argv);
	while (shell)
	{
		signal_init();
		line = ft_readline(&res);
		free(res);
		if (line == NULL)
			break ;
		if (only_space(line) && !first_word_colon_exclamation(line))
		{
			add_history(line);
			if (first_word_is_pipe(line) == 0)
				start_command(line, shell);
		}
		free(line);
	}
	ft_putstr_fd("\e[31mexit\e[0m\n", 2);
	return (exit_shell(shell, g_exit.exit_status), 0);
}
