/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:07:32 by msuji             #+#    #+#             */
/*   Updated: 2022/09/08 17:05:59 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_command_line(t_command *command_line)
{
	command_line->whole_str = NULL;
	command_line->first_token = NULL;
}

t_command	*get_command_line(char *str)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (new == NULL)
		return (NULL);
	init_command_line(new);
	new->whole_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new->whole_str == NULL)
	{
		if (new)
			free(new);
		return (NULL);
	}
	new->whole_str = ft_strcpy(new->whole_str, str);
	return (new);
}

void	commandline_addback(t_command *line, t_command *new)
{
	t_command	*a;

	a = line;
	if (a == NULL)
		line = new;
	else
	{
		while (a->next)
			a = a->next;
		a->next = new;
	}
}
