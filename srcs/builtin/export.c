/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:19:08 by msuji             #+#    #+#             */
/*   Updated: 2022/09/11 18:44:53 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	display_env_for_export(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->body)
			ft_printf("export %s=\"%s\"\n", env->name, env->body);
		else
			ft_printf("export %s\n", env->name);
		env = env->next;
	}
}

int	check_argument_for_export(char *str)
{
	int	res;

	res = 0;
	if (str[0] == '=' || str[0] == '+'
		|| (str[0] == '+' && str[1] == '='))
	{
		export_error(str);
		return (1);
	}
	res = inside_checker_export(str);
	if (res != 0)
		return (res);
	if (ft_strchr(str, '='))
		return (check_env(str));
	return (0);
}

int	inside_checker_export(char *str)
{
	int	i;

	i = 0;
	while ((str[i] && str[i] != '='
			&& (str[i] != '+' || str[i + 1] != '=')) || str[0] == '\0')
	{
		if (i == 0 && ft_isdigit(str[i]) != 0)
		{
			export_error(str);
			return (1);
		}
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			if (str[0] == '-')
				return (2);
			else if (str[i] == '!' && str[i + 1] != '\0'
				&& str[i + 1] != '=')
				return (3);
			export_error(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_export(t_word *word, t_shell *shell)
{
	int	res;

	if (word->next == NULL)
	{
		display_env_for_export(shell);
		return (0);
	}
	word = word->next;
	while (word)
	{
		res = check_argument_for_export(word->str);
		if (res != 0)
		{
			if (res == 2 || res == 3)
				g_exit.exit_status = export_option(res, word->str);
			else
				g_exit.exit_status = res;
		}
		else if (ft_strnstr(word->str, "+=", ft_strlen(word->str)) != 0)
			env_add_with_plus(word->str, shell);
		else
			env_add(word->str, shell);
		word = word->next;
	}
	return (g_exit.exit_status);
}
