/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:28:01 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/08 16:35:55 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_paths(t_shell *shell)
{
	int	i;

	if (shell->paths)
	{
		i = -1;
		while (shell->paths[++i])
		{
			free(shell->paths[i]);
			shell->paths[i] = NULL;
		}
		free(shell->paths);
		shell->paths = NULL;
	}
}

void	free_all(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmds)
			free_cmds(shell);
		if (shell->paths)
			free_paths(shell);
		if (shell->env)
			free_env(shell);
		if (shell->fdin > 2)
			close(shell->fdin);
		if (shell->fdout > 2)
			close(shell->fdout);
		free(shell);
		shell = NULL;
	}
}

void	fill_data(t_shell *shell, char **args)
{
	int		i;
	t_comm	*new;

	i = 0;
	if (!args || !shell)
		return ;
	while (args[i + 1])
	{
		new = (t_comm *)malloc(sizeof(t_comm));
		if (!new)
			return (free_all(shell));
		new->args = ft_split(args[i + 1], ' ');
		new->next = NULL;
		new->isbuiltin = isbuiltin(new->args[0]);
		lst_addback(&(shell->cmds), new);
		i++;
	}
	return ;
}

bool	isbuiltin(char *str)
{
	int			i;
	const char	*args[] = {"echo", "cd", "pwd", \
				"export", "unset", "env", "exit", NULL};

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(str, args[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	lst_addback(t_comm **lst, t_comm *new)
{
	t_comm	*a;

	a = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (a->next)
			a = a->next;
		a->next = new;
	}
}
