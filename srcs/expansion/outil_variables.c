/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:23:11 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/09 14:30:45 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

long	after_doller(char *str, long i, char **new, t_shell *shell)
{
	char	*name;
	char	*body;

	name = get_var_name(&str[i]);
	if (name[0] != '\0')
	{
		body = get_env_body(name, shell);
		if (body == NULL)
		{
			new = NULL;
			i += ft_strlen(name);
			free(name);
			return (i);
		}
		*new = ft_strjoin_and_free(*new, 1, body, 0);
		i += ft_strlen(name);
	}
	free(name);
	return (i);
}

long	at_doller_mark(char *str, char **new, long i, t_shell *shell)
{
	i++;
	if (str[i] == '?')
	{
		*new = ft_strjoin_and_free(*new, 1, ft_itoa(g_exit_status), 1);
		i++;
	}
	else if (!is_var_name_char_1st(str[i]))
		*new = ft_strjoin_and_free(*new, 1, "$", 0);
	else
		i = after_doller(str, i, new, shell);
	return (i);
}

char	*get_var_name(char *str)
{
	char	*name;
	long	len;

	len = 0;
	while (str[len])
	{
		if (len == 0 && !is_var_name_char(str[len]))
			break ;
		else if (!is_var_name_char(str[len]))
			break ;
		len++;
	}
	name = ft_strndup(str, len);
	return (name);
}

char	*get_env_body(char *name, t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env->body);
		env = env->next;
	}
	return (NULL);
}
