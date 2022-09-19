/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shell2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:20:29 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/08 16:21:37 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_addback(t_env *env, char *name, char *body)
{
	t_env	*now;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->name = name;
	new->body = body;
	if (env == NULL)
		return (new);
	else
	{
		now = env;
		while (now->next)
			now = now->next;
		now->next = new;
	}
	return (env);
}

t_env	*create_env(char **envp)
{
	t_env	*env;
	long	i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		env = env_addback(env, create_env_name(envp[i]),
				create_env_body(envp[i]));
		i++;
	}
	return (env);
}

void	free_env(t_shell *shell)
{
	t_env	*env;

	while (shell->env)
	{
		env = shell->env->next;
		free(shell->env->name);
		free(shell->env->body);
		free(shell->env);
		shell->env = env;
	}
}
