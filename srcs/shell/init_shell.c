/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 02:16:40 by ahocine           #+#    #+#             */
/*   Updated: 2022/07/22 02:16:42 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char   **ft_init_shell(void)
{
	char	**res;
	char	*value;
	char	*str;

	res = (char **)ft_calloc(sizeof(char *), 4);
	value = getcwd(NULL, 0);
	if (!value || !res)
		return (free(res), free(value), NULL);
	str = ft_strjoin("PWD=", value);
	free(value);
	if (!str)
		return (free(res), NULL);
	res[1] = str;
	value = ft_strdup("SHLVL=1");
	if (!value)
		return (free(str), free(res), NULL);
	res[0] = value;
	value = ft_strdup("OLDPWD=");
	if (!value)
		return (free(res[1]), free(str), free(res), NULL);
	res[2] = value;
	int	i = 0;
	while (i < 3)
		printf("%s\n", res[i++]);
	return (res);
}

void	free_envp_init(t_shell *shell)
{
	char	**envp;
	int		i;

	if (!shell)
		return ;
	i = 0;
	envp = shell->envp;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
