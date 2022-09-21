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

#include "../../includes/minishell.h"

long	after_doller_check(char *str, char *new, long i)
{
	int	cur;

	cur = i + 1;
	if (str[i] == '$' && ft_isdigit(str[cur]))
	{
		new[ft_strlen(new)] = str[i + 2];
		i += 3;
	}
	else if (str[i] == '$' && (str[cur] == '\'' || str[cur] == '"'))
	{
		new[i] = str[cur];
		i += cur;
	}
	return (i);
}

char	*expand_var_in_str(char *str, t_shell *shell)
{
	char			*new;
	long			i[2];

	i[0] = 0;
	i[1] = NO;
	new = ft_strdup("");
	while (str[i[0]])
	{
		if (i[1] != SINGLE && str[i[0]] == '$')
		{
			i[0] = at_doller_mark(str, &new, i, shell);
			i[0] = after_doller_check(str, new, i[0]);
			continue ;
		}
		if ((str[i[0]] == '"' && i[1] != SINGLE) || \
		(str[i[0]] == '\'' && i[1] != DOUBLE))
			i[1] = ft_handle_quote(i[1], str[i[0]]);
		new = ft_str_add_char(new, str[i[0]++]);
	}
	return (free(str), new);
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
