/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:20 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/09 15:18:57 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

long	after_doller_check(char *str, char *new, long i)
{
	int	cur;

	cur = 1;
	if (str[0] == '$' && ft_isdigit(str[1]))
	{
		new[0] = str[2];
		i += 2;
	}
	else if (str[0] == '$' && (str[cur] == '\'' || str[cur] == '"'))
	{
		while (str[cur] != '\'' && str[cur] != '"')
			cur++;
		new[0] = str[cur];
		i += cur;
	}
	return (i);
}

char	*expand_var_in_str(char *str, t_shell *shell)
{
	char	*new;
	long	i;
	bool	double_quote;
	bool	single_quote;

	i = 0;
	new = ft_strdup("");
	while (str[i])
	{
		if (!single_quote && str[i] == '$')
		{
			i = at_doller_mark(str, &new, i, shell);
			i = after_doller_check(str, new, i);
			continue ;
		}
		if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		new = ft_str_add_char(new, str[i]);
		i++;
	}
	free(str);
	return (new);
}

void	expand_var_in_redir(t_redir *redir, t_shell *shell)
{
	if (redir == NULL)
		return ;
	if (redir->kind != REDIR_HEREDOC)
		redir->str = expand_var_in_str(redir->str, shell);
	expand_var_in_redir(redir->next, shell);
}

void	expand_var_in_word(t_word *word, t_shell *shell)
{
	if (word == NULL)
		return ;
	word->str = expand_var_in_str(word->str, shell);
	expand_var_in_word(word->next, shell);
}

void	expand_var(t_node *node, t_shell *shell)
{
	if (node == NULL)
		return ;
	if (node->kind == NODE_EOF)
		return ;
	if (node->kind == COMMAND)
	{
		expand_var_in_word(node->cmds->word, shell);
		expand_var_in_redir(node->cmds->redir_in, shell);
		expand_var_in_redir(node->cmds->redir_out, shell);
	}
	else
	{
		expand_var(node->lhs, shell);
		expand_var(node->rhs, shell);
	}
}
