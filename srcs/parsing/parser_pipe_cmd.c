/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:29:19 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/09 11:54:40 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

t_node	*pipe_cmd(t_token **token)
{
	t_node	*node;

	if (g_exit.exit_status != 5 && g_exit.exit_status != 6)
	{
		node = new_node_pipe(command(token));
		if (g_exit.exit_status == 5 || g_exit.exit_status == 6)
			return (NULL);
		while (consume(*token, TOKEN_PIPE, "|"))
		{
			*token = skip(*token, TOKEN_PIPE, "|");
			node = add_node_pipe(node, command(token));
		}
	}
	return (node);
}
