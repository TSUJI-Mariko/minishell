/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:22:19 by msuji             #+#    #+#             */
/*   Updated: 2022/09/08 16:25:23 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_add(char *str, t_shell *shell)
{
	char	*name;
	char	*body;

	name = create_env_name(str);
	body = create_env_body(str);
	if (shell->env == NULL)
		return (shell->env = new_env(name, body), (void)0);
	env_rewrite(shell, name, body);
}

void	env_add_with_plus(char *str, t_shell *shell)
{
	char	*name;
	char	*body;

	name = create_env_name_with_plus(str);
	body = create_env_body_with_plus(str);
	if (shell->env == NULL)
		return (shell->env = new_env(name, body), (void)0);
	env_rewrite_with_plus(shell, name, body);
}

t_env	*new_env(char *name, char *body)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = name;
	env->body = body;
	return (env);
}

void	env_rewrite(t_shell *shell, char *name, char *body)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(name);
			if (body)
			{
				free(env->body);
				env->body = body;
			}
			return ;
		}
		if (env->next == NULL)
			return (env->next = new_env(name, body), (void)0);
		env = env->next;
	}
}

void	env_rewrite_with_plus(t_shell *shell, char *name, char *body)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->body = ft_strjoin_and_free(env->body, 1, body, 1), \
			free(name));
		if (env->next == NULL)
			return (env->next = new_env(name, body), (void)0);
		env = env->next;
	}
}
