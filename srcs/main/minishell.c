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

#include "../../inc/minishell.h"

int	g_exit_status;

void	start_command(char *str, t_shell *shell)
{
	t_command	*command_line;
	t_node		*node;

	command_line = lexer(str);
	if (command_line == NULL)
	{
		g_exit_status = 2;
		return ;
	}
	node = parser(command_line->first_token);
	free_lexer(command_line);
	if (node)
	{
		signal_heredoc();
		expander_set_heredoc(node, shell);
		signal_exec();
		exec(node, shell);
		free_node(node);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	*shell;

	rl_outstream = stderr;
	if (argc)
		shell = create_shell(envp, argv);
	while (1)
	{
		signal_init();
		line = readline(">minishell ");
		if (line == NULL)
			break ;
		if (only_space(line)
			&& !first_word_colon_exclamation(line))
		{
			add_history(line);
			if (first_word_is_pipe(line) == 0)
				start_command(line, shell);
		}
		if (line)
			free(line);
	}
	ft_putstr_fd("exit\n", 2);
	exit_shell(shell, g_exit_status);
}
