/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:26:06 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/12 19:04:05 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": invalid option\n", 2);
}

int	cd_argument_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-')
		{
			if (str[1] != '\0' && str[1] != '-')
			{
				cd_error(str);
				return (2);
			}
			else if (str[1] == '-' && str[2] != '\0')
			{
				cd_error("--");
				return (2);
			}
			else if (str[1] == '-' && str[2] == '\0')
				return (3);
		}
		i++;
	}
	return (0);
}
