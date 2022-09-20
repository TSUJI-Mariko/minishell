/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_parser3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:30:17 by msuji             #+#    #+#             */
/*   Updated: 2022/09/09 11:27:36 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_exit	g_exit;

void	word_addback(t_cmd *command, char *str, long len)
{
	t_word	*word;
	t_word	*last;

	word = ft_calloc(1, sizeof(t_word));
	word->str = ft_strndup(str, len);
	if (command->word == NULL)
	{
	command->word = word;
		return ;
	}
	last = command->word;
	while (last->next != NULL)
		last = last->next;
	last->next = word;
}

void	redir_in_addback(t_cmd *command, \
				t_redir_kind kind, char *str, int len)
{
	t_redir	*rdr;
	t_redir	*last;

	rdr = ft_calloc(1, sizeof(t_redir));
	rdr->kind = kind;
	rdr->str = ft_strndup(str, len);
	if (command->redir_in == NULL)
	{
		command->redir_in = rdr;
		return ;
	}
	last = command->redir_in;
	while (last->next != NULL)
		last = last->next;
	last->next = rdr;
}

void	redir_out_addback(t_cmd *command, \
				t_redir_kind kind, char *str, int len)
{
	t_redir	*rdr;
	t_redir	*last;

	rdr = ft_calloc(1, sizeof(t_redir));
	rdr->kind = kind;
	rdr->str = ft_strndup(str, len);
	if (command->redir_out == NULL)
	{
		command->redir_out = rdr;
		return ;
	}
	last = command->redir_out;
	while (last->next != NULL)
		last = last->next;
	last->next = rdr;
}

void	syntax_error(t_node *node)
{
	ft_putstr_fd("minishell: syntax error near unexpected token", 2);
	g_exit.exit_status = 6;
	free_node(node);
}

void	add_redir_in(t_node *node, t_redir_kind kind, char *str, long len)
{
	t_redir	*redir;
	t_redir	*now;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->fd = -1;
	redir->str = ft_strndup(str, len);
	redir->kind = kind;
	if (!node->redir_in)
		node->redir_in = redir;
	else
	{
		now = node->redir_in;
		while (now->next)
			now = now->next;
		now->next = redir;
	}
}
