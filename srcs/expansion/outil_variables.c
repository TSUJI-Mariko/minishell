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

extern t_exit	g_exit;

long	after_doller(char *str, long i, char **new, t_shell *shell)
{
	char	*name;
	char	*body;

	name = get_var_name(&str[i]);
	if (!name)
		return (i);
	if (name[0] != '\0')
	{
		body = get_env_body(name, shell);
		if (body == NULL)
		{
			new = NULL;
			i += ft_strlen(name);
			return (free(name), i);
		}
		*new = ft_strjoin_and_free(*new, 1, body, 0);
		i += ft_strlen(name);
	}
	return (free(name), i);
}

long	at_doller_mark(char *s, char **new, long i[2], t_shell *shell)
{
	i[0]++;
	if (s[i[0]] == '?')
	{
		*new = ft_strjoin_and_free(*new, 1, ft_itoa(g_exit.exit_status), 1);
		i[0]++;
	}
	else if (!is_valid_1st_char(s[i[0]]) && !ft_isdigit(s[i[0]]) \
	&& ((s[i[0]] != '"' && s[i[0]] != '\'') || i[1] == (long)DOUBLE))
		*new = ft_strjoin_and_free(*new, 1, "$", 0);
	else if (ft_isdigit(s[i[0]]))
		i[0]++;
	else if (is_valid_1st_char(s[i[0]]))
		i[0] = after_doller(s, i[0], new, shell);
	return (i[0]);
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
	if (!name)
		return (NULL);
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
