/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:30:17 by msuji             #+#    #+#             */
/*   Updated: 2022/09/09 11:28:39 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

void	free_redirection(t_redir *redirection)
{
	if (!redirection)
		return ;
	if (redirection->fd >= 0)
		close(redirection->fd);
	free_redirection(redirection->next);
	free(redirection->str);
	free(redirection);
}

void	free_word(t_word *word)
{
	if (!word)
		return ;
	free_word(word->next);
	free(word->str);
	free(word);
}

t_node	*new_node_pipe(t_node *cmd_node)
{
	t_node	*node;

	if (g_exit.exit_status == 5 || g_exit.exit_status == 6)
		return (NULL);
	node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->kind = PIPE;
	node->rhs = cmd_node;
	return (node);
}

t_node	*add_node_pipe(t_node *node, t_node *cmd_node)
{
	t_node	*new;

	new = new_node_pipe(cmd_node);
	if (g_exit.exit_status != 6 && g_exit.exit_status != 5)
		new->lhs = node;
	return (new);
}

t_node	*new_node_command(void)
{
	t_node	*node;

	if (g_exit.exit_status == 5 || g_exit.exit_status == 6)
		return (NULL);
	node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->cmds = ft_calloc(1, sizeof(t_cmd));
	if (node->cmds == NULL)
		return (free(node), NULL);
	node->kind = COMMAND;
	return (node);
}
