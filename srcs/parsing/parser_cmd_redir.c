/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:30:12 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/09 11:54:48 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	redir_in(t_token **token, t_node *node)
{
	if (ft_strnstr((*token)->string, "<<<", ft_strlen((*token)->string)))
	{
		g_exit.exit_status = 6;
		ft_putstr_fd("minishell: syntax error near unexpected \
token `<<'\n", 2);
		return ;
	}
	if (consume(*token, TOKEN_OP, "<"))
	{
		*token = skip(*token, TOKEN_OP, "<");
		redir_in_addback(node->cmds, REDIR_IN, (*token)->string, *token);
	}
	else if (consume(*token, TOKEN_OP, "<<"))
	{
		*token = skip(*token, TOKEN_OP, "<<");
		redir_in_addback(node->cmds, REDIR_HEREDOC, \
				(*token)->string, *token);
	}
}

void	redir_out(t_token **token, t_node *node)
{
	if (ft_strnstr((*token)->string, ">>>", ft_strlen((*token)->string)))
	{
		g_exit.exit_status = 6;
		ft_putstr_fd("minishell: syntax error near unexpected \
token `>>'\n", 2);
		return ;
	}
	if (consume(*token, TOKEN_OP, ">"))
	{
		*token = skip(*token, TOKEN_OP, ">");
		redir_out_addback(node->cmds, REDIR_OUT, \
					(*token)->string, *token);
	}
	else if (consume(*token, TOKEN_OP, ">>"))
	{
		*token = skip(*token, TOKEN_OP, ">>");
		redir_out_addback(node->cmds, REDIR_APPEND, \
			(*token)->string, *token);
	}
}

t_node	*command(t_token **token)
{
	t_node	*node;

	node = new_node_command();
	while (true)
	{
		if (g_exit.exit_status == 5 || g_exit.exit_status == 6)
		{
			free_node(node);
			return (NULL);
		}
		if (consume(*token, TOKEN_ARGUMENT, NULL))
			word_addback(node->cmds, (*token)->string, (*token)->len);
		else if (consume_redir(*token, TOKEN_OP, "<"))
			redir_in(token, node);
		else if (consume_redir(*token, TOKEN_OP, ">"))
			redir_out(token, node);
		else
		{
			command_error_check(node);
			return (node);
		}
		if (g_exit.exit_status != 6 && g_exit.exit_status != 5)
			*token = skip(*token, TOKEN_ARGUMENT, NULL);
	}
}

void	command_error_check(t_node *node)
{
	if (node->cmds->word == NULL && node->cmds->redir_in == NULL
		&& node->cmds->redir_out == NULL)
		syntax_error(node);
}
