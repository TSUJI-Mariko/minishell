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

#include "../../inc/minishell.h"

void	pwd_error(char *str)
{
	printf("minishell : pwd: ");
	printf("%s : invalid option\n", str);
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
		perror("pwd");
	ft_putendl_fd(buff, 1);
	return (0);
}
