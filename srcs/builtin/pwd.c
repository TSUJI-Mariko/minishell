/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 23:54:18 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/12 19:03:27 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_error(char *str)
{
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": invalid option\n", 2);
}

int	pwd_argument_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-')
		{
			if (str[1] != '\0' && str[1] != '-')
			{
				pwd_error(str);
				return (2);
			}
			else if (str[1] == '-' && str[2] != '\0')
			{
				pwd_error("--");
				return (2);
			}
		}
		i++;
	}
	return (0);
}

int	pwd(t_word *word)
{
	char	buff[PATH_MAX];
	int		res;

	if (word->next != NULL)
	{
		word = word->next;
		res = pwd_argument_check(word->str);
		if (res != 0)
			return (res);
	}
	ft_memset(buff, 0, PATH_MAX);
	if (!getcwd(buff, PATH_MAX))
		return (perror("pwd"), errno);
	return (ft_putendl_fd(buff, 1), 0);
}
