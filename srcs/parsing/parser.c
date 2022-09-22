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

extern t_exit	g_exit;

t_node	*parser(t_token *token)
{
	t_node	*node;

	node = pipe_cmd(&token);
	if (g_exit.exit_status == 5)
	{
		ft_putstr_fd("minishell: syntax error near unexpected \
token `newline'\n", 2);
		return (g_exit.exit_status = 2, NULL);
	}
	else if (g_exit.exit_status == 6)
		return (g_exit.exit_status = 2, NULL);
	token = skip(token, TOKEN_EOF, NULL);
	return (node);
}
