/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:30:17 by msuji             #+#    #+#             */
/*   Updated: 2022/09/08 17:44:31 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	parser_error(char *str, long len)
{
	char	*str_tmp;

	str_tmp = strndup(str, len);
	ft_putstr_fd("minishell : syntax error near unexpected \
token `newline'", 2);
	ft_putchar_fd('\n', 2);
	free(str_tmp);
	g_exit.exit_status = 2;
}

bool	consume(t_token *token, t_token_kind kind, char *str)
{
	if (token)
	{
		if (token->kind != kind)
			return (false);
		if (str != NULL && ft_strncmp(token->string, str, token->len))
			return (false);
	}
	return (true);
}

bool	consume_redir(t_token *token, t_token_kind kind, char *str)
{
	if (token)
	{
		if (token->kind != kind)
			return (false);
		if (str != NULL && !ft_strnstr(token->string, str, token->len))
			return (false);
	}
	return (true);
}

t_token	*skip(t_token *token, t_token_kind kind, char *str)
{
	if (!token)
		return (NULL);
	if (token->kind != kind)
	{
		g_exit.exit_status = 5;
	}
	if (str != NULL && (token->len != (long)ft_strlen(str)
			|| ft_strncmp(token->string, str, token->len)))
		g_exit.exit_status = 5;
	return (token->next);
}

void	free_node(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind != COMMAND)
	{
		free_node(node->lhs);
		free_node(node->rhs);
	}
	else
	{
		free_word(node->cmds->word);
		free_redirection(node->cmds->redir_in);
		free_redirection(node->cmds->redir_out);
		free(node->cmds->pathname);
		free(node->cmds);
	}
	free(node);
	node = NULL;
}
