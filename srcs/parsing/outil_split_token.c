/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_split_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:22:59 by msuji             #+#    #+#             */
/*   Updated: 2022/09/09 11:00:08 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	put_eof(t_command *command_line, char *str, int len)
{
	t_token	*token;
	t_token	*end;

	end = NULL;
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	token->kind = TOKEN_EOF;
	token->string = str;
	token->len = len;
	token_addback(&command_line->first_token, token);
	token->next = end;
	return (0);
}
