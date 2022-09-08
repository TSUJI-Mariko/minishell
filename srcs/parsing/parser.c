/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:36:50 by msuji             #+#    #+#             */
/*   Updated: 2022/09/08 18:01:56 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

t_node	*pipe_cmd(t_token **token)
{
	t_node	*node;

	if (g_exit_status != 5 && g_exit_status != 6)
	{
	node = new_node_pipe(command(token));
		if (g_exit_status == 5 || g_exit_status == 6)
			return (NULL);
		while (consume(*token, TOKEN_PIPE, "|"))
		{
			*token = skip(*token, TOKEN_PIPE, "|");
			node = add_node_pipe(node, command(token));
		}
	}
	return (node);
}

void	redir_in(t_token **token, t_node *node)
{
	if (ft_strnstr((*token)->string, "<<<", ft_strlen((*token)->string)))
	{
		g_exit_status = 6;
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
		return ;
	}
	if (consume(*token, TOKEN_OP, "<"))
	{
		*token = skip(*token, TOKEN_OP, "<");
		redir_in_addback(node->cmds, REDIR_IN, (*token)->string, (*token)->len);
	}
	else if (consume(*token, TOKEN_OP, "<<"))
	{
		*token = skip(*token, TOKEN_OP, "<<");
		redir_in_addback(node->cmds, REDIR_HEREDOC, \
				(*token)->string, (*token)->len);
	}
}

void	redir_out(t_token **token, t_node *node)
{
	if (ft_strnstr((*token)->string, ">>>", ft_strlen((*token)->string)))
	{
		g_exit_status = 6;
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
		return ;
	}
	if (consume(*token, TOKEN_OP, ">"))
	{
		*token = skip(*token, TOKEN_OP, ">");
		redir_out_addback(node->cmds, REDIR_OUT, \
					(*token)->string, (*token)->len);
	}
	else if (consume(*token, TOKEN_OP, ">>"))
	{
		*token = skip(*token, TOKEN_OP, ">>");
		redir_out_addback(node->cmds, REDIR_APPEND, \
					(*token)->string, (*token)->len);
	}
}

t_node	*command(t_token **token)
{
	t_node	*node;

	node = new_node_command();
	while (true)
	{
		if (g_exit_status == 5 || g_exit_status == 6)
		{
			free_node(node);
			return (node);
		}
		if (consume(*token, TOKEN_ARGUMENT, NULL))
			word_addback(node->cmds, (*token)->string, (*token)->len);
		else if (consume_redir(*token, TOKEN_OP, "<")
			|| consume_redir(*token, TOKEN_OP, "<<"))
			redir_in(token, node);
		else if (consume_redir(*token, TOKEN_OP, ">")
			|| consume_redir(*token, TOKEN_OP, ">>"))
			redir_out(token, node);
		else
		{
			if (node->cmds->word == NULL && node->cmds->redir_in == NULL
				&& node->cmds->redir_out == NULL)
				syntax_error(node);
			return (node);
		}
		if (g_exit_status != 6)
			*token = skip(*token, TOKEN_ARGUMENT, NULL);
	}
}
