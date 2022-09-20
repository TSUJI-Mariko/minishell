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

#include "../../inc/minishell.h"

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
		printf("minishell : export: ");
		printf("%s : event not found\n", ft_strchr(&str[i], '!'));
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
		printf("minishell : export: ");
		printf("`%c%c' : invalid option\n", str[0], str[1]);
		return (2);
	}
	else if (res == 3)
	{
		while (str[i] != '!')
			i++;
		printf("minishell : export: ");
		printf("%s : event not found\n", &str[i]);
		return (0);
	}
	return (0);
}

void	export_error(char *str)
{
	printf("minishell : export: ");
	printf("`%s' : not a valid identifier\n", str);
}
