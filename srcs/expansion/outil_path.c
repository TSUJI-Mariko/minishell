/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:23:59 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/09 13:35:23 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_path(char **paths)
{
	long	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

int	check_pathname(char *pathname)
{
	struct stat	s;

	if (access(pathname, F_OK) != 0)
		return (1);
	if (stat(pathname, &s) != 0)
		return (1);
	return (S_ISDIR(s.st_mode));
}

char	*sarch_pathname(char *str, t_shell *shell)
{
	char	**paths;
	char	*base;
	char	*pathname;
	long	i;

	pathname = NULL;
	paths = ft_split(get_env_body("PATH", shell), ':');
	if (paths == NULL)
		return (ft_strdup(str));
	i = 0;
	while (paths[i])
	{
		base = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin_and_free(base, 1, str, 0);
		if (!check_pathname(pathname))
		{
			free_path(paths);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free_path(paths);
	return (NULL);
}
