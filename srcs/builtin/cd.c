/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:34:32 by msuji             #+#    #+#             */
/*   Updated: 2022/09/12 19:04:33 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

void	after_cd(t_shell *shell)
{
	char	buff[PATH_MAX];
	char	*new;

	if (get_env_body("PWD", shell))
	{
		new = ft_strjoin("OLDPWD=", get_env_body("PWD", shell));
		env_add(new, shell);
		free(new);
	}
	ft_memset(buff, 0, PATH_MAX);
	if (!getcwd(buff, PATH_MAX))
	{
		perror("getcwd");
		return ;
	}
	new = ft_strjoin("PWD=", buff);
	env_add(new, shell);
	free(new);
}

int	go_home(t_shell *shell)
{
	char	*home;

	home = get_env_body("HOME", shell);
	if (home == NULL)
	{
		ft_putstr_fd("Home not set\n", 2);
		return (1);
	}
	if (chdir(home) != 0)
	{
		ft_putstr_fd("minishell:  cd: ", 2);
		ft_putstr_fd(home, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	after_cd(shell);
	return (0);
}

int	cd(t_word *word, t_shell *shell)
{
	int	res;

	if (word->next != NULL && word->next->next != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (word->next == NULL || !ft_strcmp(word->next->str, "$HOME"))
		return (go_home(shell));
	res = cd_argument_check(word->next->str);
	if (res != 0)
	{
		if (res == 3)
			return (go_home(shell));
		return (res);
	}
	if (chdir(word->next->str) != 0)
	{
		ft_putstr_fd("minishell:  cd: ", 2);
		ft_putstr_fd(word->next->str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	after_cd(shell);
	return (0);
}
