/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:29:54 by msuji             #+#    #+#             */
/*   Updated: 2022/09/08 17:08:55 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*lexer(char *str)
{
	int			res;
	t_command	*command_line;

	res = quote_check(str);
	if (res > 0)
		return (ft_putstr_fd("miss_quote\n", 2), NULL);
	command_line = get_command_line(str);
	if (!command_line)
		return (NULL);
	if (split_command_line(command_line) > 0)
		return (free_lexer(command_line), NULL);
	return (command_line);
}

int	free_lexer(t_command *command_line)
{
	if (command_line)
	{
		if (command_line->whole_str)
			free(command_line->whole_str);
		if (command_line->first_token)
			free_token(&command_line);
		free(command_line);
	}
	return (1);
}

void	free_token(t_command **command_line)
{
	t_token	*token;

	while ((*command_line)->first_token)
	{
		token = (*command_line)->first_token->next;
		if ((*command_line)->first_token->string)
			free((*command_line)->first_token->string);
		free((*command_line)->first_token);
		(*command_line)->first_token = token;
	}
}
