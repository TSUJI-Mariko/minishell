/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:25:14 by msuji             #+#    #+#             */
/*   Updated: 2022/09/11 18:53:29 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

int	check_env(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '=')
		i++;
	j = i;
	while (str[j])
		j++;
	if (str[j - 1] == '!')
		return (0);
	else if (ft_strchr(&str[i], '!'))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(ft_strchr(&str[i], '!'), 2);
		ft_putstr_fd(": event not found\n", 2);
		return (1);
	}
	return (0);
}

int	export_option(int res, char *str)
{
	int	i;

	i = 0;
	if (res == 2)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putchar_fd(str[0], 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd("': invalid option\n", 2);
		ft_putstr_fd("export: usage: export [name[=value]\n", 2);
		return (2);
	}
	else if (res == 3)
	{
		while (str[i] != '!')
			i++;
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(&str[i], 2);
		ft_putstr_fd(": event not found\n", 2);
		return (0);
	}
	return (0);
}

void	export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
