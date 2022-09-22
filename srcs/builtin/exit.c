/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:46:47 by msuji             #+#    #+#             */
/*   Updated: 2022/09/12 19:04:55 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

int	overflow_check(char **str)
{
	long long	res;
	long		i;

	res = 0;
	i = 0;
	if (!strncmp(*str, "-9223372036854775808", 21))
		return (*str[i] = '0', (*str)[i + 1] = 0, 0);
	if ((*str)[i] == '-' || (*str)[i] == '+')
		i++;
	while ((*str)[i])
	{
		res = res * 10 + (*str)[i] - '0';
		i++;
		if ((unsigned long long)res > 9223372036854775807)
			return (2);
	}
	return (0);
}

int	check_int(char **str)
{
	int	i;

	i = 0;
	if ((*str)[i] == '-' || (*str)[i] == '+')
		i++;
	while ((*str)[i])
	{
		if ((*str)[i] < '0' || (*str)[i] > '9')
			return (2);
		i++;
	}
	return (overflow_check(str));
}

int	builtin_exit(t_word *word)
{
	if (word->next == NULL || word->next->str == NULL)
		exit(g_exit.exit_status);
	if (check_int(&(word->next->str)))
	{
		ft_putstr_fd("\e[31mminishell:\e[0m exit: ", 2);
		ft_putstr_fd(word->next->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (word->next->next != NULL)
	{
		ft_putstr_fd("\e[31mminishell:\e[0m exit: too many arguments\n", 2);
		g_exit.exit_status = 1;
		return (1);
	}
	exit(ft_atoi(word->next->str));
	return (0);
}
