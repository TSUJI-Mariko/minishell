/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 23:54:18 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/21 23:54:23 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd(t_word *word)
{
    (void)word;
	char buff[PATH_MAX];

    ft_memset(buff, 0, PATH_MAX);
	if (!getcwd(buff, PATH_MAX))
		perror("pwd");
	ft_putendl_fd(buff, 1);
    return (0);
}