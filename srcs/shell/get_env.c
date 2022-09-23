/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:28:01 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/08 16:32:41 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path_line(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (ft_strncmp("PATH=", paths[i], 5) == 0)
			return (paths[i] + 5);
		i++;
	}
	return (NULL);
}

char	**get_paths(t_shell *shell, char **envp)
{
	char	**paths;
	char	*path;

	path = get_path_line(envp);
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	shell->paths = paths;
	if (paths)
		return (paths);
	return (NULL);
}

t_shell	*init_all(void)
{
	t_shell	*shell;

	shell = (t_shell *)malloc((sizeof(t_shell)) * 1);
	if (!shell)
		exit_shell(shell, EXIT_FAILURE);
	shell->nb_cmds = 0;
	shell->cmds = NULL;
	shell->envp = NULL;
	shell->paths = NULL;
	shell->env = NULL;
	return (shell);
}

void	exit_shell(t_shell *shell, int code)
{
	if (shell)
	{
		close(shell->fdin);
		close(shell->fdout);
		free_all(shell);
	}
	exit(code);
}

void	free_cmds(t_shell *shell)
{
	int		i;
	t_comm	*tmp;

	while (shell->cmds)
	{
		i = -1;
		while (shell->cmds->args[++i])
		{
			free(shell->cmds->args[i]);
			shell->cmds->args[i] = NULL;
		}
		if (shell->cmds->args)
			free(shell->cmds->args);
		shell->cmds->args = NULL;
		tmp = shell->cmds;
		shell->cmds = shell->cmds->next;
		free(tmp);
	}
}
