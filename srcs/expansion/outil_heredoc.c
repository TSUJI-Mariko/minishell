/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:12:13 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/14 12:04:18 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_var_heredoc(t_redir *redir, char *str, t_shell *shell)
{
	char			*new;
	long			i[2];

	i[0] = 0;
	i[1] = NO;
	new = ft_strdup("");
	while (str[i[0]])
	{
		if (redir->no_expand == false && i[1] != SINGLE && str[i[0]] == '$')
		{
			i[0] = at_doller_mark(str, &new, i, shell);
			i[0] = after_doller_check(str, new, i[0]);
			continue ;
		}
		if (str[i[0]] == '"' && i[1] != SINGLE)
			i[1] = DOUBLE;
		if (str[i[0]] == '\'' && i[1] != DOUBLE)
			i[1] = SINGLE;
		new = ft_str_add_char(new, str[i[0]]);
		i[0]++;
	}
	free(str);
	return (new);
}

t_quote_check	quote_check2(char *str, t_quote_check quote)
{
	long	i;

	i = 0;
	while (str[i])
	{
		if (quote == NO && str[i] == '"')
			quote = DOUBLE;
		else if (quote == NO && str[i] == '\'')
			quote = SINGLE;
		else if (quote == DOUBLE && str[i] == '"')
			quote = D_CLOSE;
		else if (quote == SINGLE && str[i] == '\'')
			quote = S_CLOSE;
		i++;
	}
	return (quote);
}
