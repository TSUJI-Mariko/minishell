/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:33:41 by msuji             #+#    #+#             */
/*   Updated: 2022/09/09 18:44:32 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	unset_error(char *str)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	inside_checker_unset(char *str)
{
	int	i;

	i = 0;
	while (str[i] || str[0] == '\0')
	{
		if (i == 0 && ft_isdigit(str[i]) != 0)
		{
			unset_error(str);
			return (1);
		}
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			if (str[0] == '-')
				return (2);
			else if (str[i] == '!' && str[i + 1] != '\0'
				&& str[i + 1] != '=')
				return (3);
			unset_error(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset_argument_check(char *str)
{
	int	res;

	res = 0;
	if (str[0] == '=')
	{
		unset_error(str);
		return (1);
	}
	res = inside_checker_unset(str);
	return (res);
}

int	unset_option(int res, char *str)
{
	int	i;

	i = 0;
	if (res == 2)
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putchar_fd(str[0], 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd("': invalid option\n", 2);
		return (2);
	}
	else if (res == 3)
	{
		while (str[i] != '!')
			i++;
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(&str[i], 2);
		ft_putstr_fd(": event not found\n", 2);
		return (1);
	}
	return (0);
}

int	unset(t_word *word, t_shell *shell)
{
	int	res;

	res = 0;
	g_exit.exit_status = 0;
	word = word->next;
	while (word)
	{
		res = unset_argument_check(word->str);
		if (res != 0)
		{
			if (res == 2 || res == 3)
				g_exit.exit_status = unset_option(res, word->str);
			else
				g_exit.exit_status = res;
		}
		if (word->str)
			del_env(word->str, shell);
		word = word->next;
	}
	return (g_exit.exit_status);
}
