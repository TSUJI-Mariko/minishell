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
	printf("minishell : unset: ");
	printf("`%s' : not a valid identifier\n", str);
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
		printf("minishell : unset: ");
		printf("`%c%c' : invalid option\n", str[0], str[1]);
		return (2);
	}
	else if (res == 3)
	{
		while (str[i] != '!')
			i++;
		printf("minishell : unset: ");
		printf("%s : event not found\n", &str[i]);
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
