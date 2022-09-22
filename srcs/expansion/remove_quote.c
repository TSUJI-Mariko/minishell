/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:55:54 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/14 12:04:43 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quote_string(char *str)
{
	char	*new;
	int		single_quote;
	int		double_quote;
	long	i;

	new = ft_strdup("");
	if (!new)
		return (NULL);
	single_quote = 0;
	double_quote = 0;
	i = -1;
	while (str[++i])
	{
		if (!single_quote && !double_quote && str[i] == '"')
			double_quote = 1;
		else if (!single_quote && !double_quote && str[i] == '\'')
			single_quote = 1;
		else if (double_quote && str[i] == '"')
			double_quote = 0;
		else if (single_quote && str[i] == '\'')
			single_quote = 0;
		else
			new = ft_str_add_char(new, str[i]);
	}
	return (free(str), new);
}

void	remove_quote_word(t_word *word)
{
	if (word == NULL)
		return ;
	word->str = remove_quote_string(word->str);
	remove_quote_word(word->next);
}

void	remove_quote_redir(t_redir *redir)
{
	if (redir == NULL)
		return ;
	redir->str = remove_quote_string(redir->str);
	remove_quote_redir(redir->next);
}

void	remove_quote_heredoc(t_redir *redir)
{
	t_quote_check	quote;

	quote = NO;
	if (redir == NULL)
		return ;
	if (redir->kind == REDIR_HEREDOC)
	{
		quote = quote_check2(redir->str, quote);
		redir->str = remove_quote_string(redir->str);
		if (quote == D_CLOSE || quote == S_CLOSE)
			redir->no_expand = true;
	}
	remove_quote_heredoc(redir->next);
}

void	remove_quote(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == NODE_EOF)
		return ;
	if (node->kind == COMMAND)
	{
		remove_quote_word(node->cmds->word);
		remove_quote_redir(node->cmds->redir_in);
		remove_quote_redir(node->cmds->redir_out);
	}
	else
	{
		remove_quote(node->lhs);
		remove_quote(node->rhs);
	}
}
