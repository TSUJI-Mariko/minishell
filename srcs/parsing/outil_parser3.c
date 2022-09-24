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

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	word_addback(t_cmd *command, char *str, long len)
{
	t_word	*word;
	t_word	*last;

	if (!command)
		return ;
	word = ft_calloc(1, sizeof(t_word));
	if (word == NULL)
		return ;
	word->str = ft_strndup(str, len);
	word->next = NULL;
	if (command->word == NULL)
		return (command->word = word, (void)0);
	last = command->word;
	while (last && last->next != NULL)
		last = last->next;
	if (last)
		last->next = word;
}

void	redir_in_addback(t_cmd *command, t_redir_kind kind, \
	char *str, t_token *token)
{
	t_redir	*rdr;
	t_redir	*last;

	if (token->kind == TOKEN_EOF)
		return (g_exit.exit_status = 5, (void)0);
	rdr = ft_calloc(1, sizeof(t_redir));
	if (rdr == NULL)
		return ;
	rdr->fd = -1;
	rdr->kind = kind;
	rdr->str = ft_strndup(str, token->len);
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
				t_redir_kind kind, char *str, t_token *token)
{
	t_redir	*rdr;
	t_redir	*last;

	if (token->kind == TOKEN_EOF)
		return (g_exit.exit_status = 5, (void)0);
	rdr = ft_calloc(1, sizeof(t_redir));
	if (rdr == NULL)
		return ;
	rdr->kind = kind;
	rdr->fd = -1;
	rdr->str = ft_strndup(str, token->len);
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
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	g_exit.exit_status = 6;
	free_node(node);
}
