/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:12:27 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/08 16:21:24 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_shell	*create_shell(char **envp, char **argv)
{
	t_shell	*shell;

	shell = NULL;
	shell = init_all();
	shell->envp = get_paths(shell, envp);
	shell->fdin = dup(0);
	shell->fdout = dup(1);
	if (shell->fdin == -1)
		perror("fdin");
	if (shell->fdout == -1)
		perror("fdout");
	if (!shell->envp)
	{
		printf("NULL ENVP\n");
		exit (1);
	}
	fill_data(shell, argv);
	shell->env = create_env(envp);
	return (shell);
}

char	*create_env_name(char *str)
{
	char	*name;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (eq == NULL)
		name = ft_strdup(str);
	else
		name = ft_strndup(str, eq - str);
	return (name);
}

char	*create_env_body(char *str)
{
	char	*body;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (eq == NULL)
		return (NULL);
	body = ft_strdup(eq + 1);
	return (body);
}

char	*create_env_name_with_plus(char *str)
{
	char	*name;
	char	*eq;

	eq = ft_strnstr(str, "+=", ft_strlen(str));
	if (eq == NULL)
		name = ft_strdup(str);
	else
		name = ft_strndup(str, eq - str);
	return (name);
}

char	*create_env_body_with_plus(char *str)
{
	char	*body;
	char	*eq;

	eq = ft_strnstr(str, "+=", ft_strlen(str));
	if (eq == NULL)
		return (NULL);
	body = ft_strdup(eq + 2);
	return (body);
}
