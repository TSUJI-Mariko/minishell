/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:36:50 by msuji             #+#    #+#             */
/*   Updated: 2022/09/09 11:31:09 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*parser(t_token *token)
{
	t_node	*node;

	node = pipe_cmd(&token);
	if (g_exit_status == 5)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_exit_status = 2;
		return (NULL);
	}
	else if (g_exit_status == 6)
	{
		g_exit_status = 2;
		return (NULL);
	}
	else
	{
		token = skip(token, TOKEN_EOF, NULL);
		return (node);
	}
}
