/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:56:53 by msuji             #+#    #+#             */
/*   Updated: 2022/09/08 17:25:19 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_exit	g_exit;

int	first_word_is_pipe(char *str)
{
	int				res;
	t_quote_check	quote;

	quote = NO;
	quote = quote_check2(str, quote);
	if (quote == NO)
	{
		res = pipe_check(str);
		if (res)
			return (1);
	}
	return (0);
}

int	pipe_check(char *str)
{
	int	cur;
	int	p;

	cur = 0;
	p = 0;
	while (str[cur])
	{
		if (!ft_isspace(str[cur]) && str[cur] != '|')
			p = 1;
		if (str[cur] == '|')
		{
			if (p == 0)
			{
				ft_putstr_fd("minishell: syntax error ", 2);
				ft_putstr_fd("near unexpected token `|'\n", 2);
				g_exit.exit_status = 2;
				return (1);
			}
			p = 0;
		}
		cur++;
	}
	return (0);
}

int	first_word_colon_exclamation(char *str)
{
	if ((str[0] == ':' || str[0] == '!')
		&& str[1] == '\0')
	{
		if (str[0] == '!')
			g_exit.exit_status = 1;
		return (1);
	}
	return (0);
}
