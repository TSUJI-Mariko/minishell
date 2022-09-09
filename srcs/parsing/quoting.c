/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:15:39 by msuji             #+#    #+#             */
/*   Updated: 2022/09/09 10:44:53 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quote_check(char *str)
{
	int	cur;
	int	s_quote;
	int	d_quote;

	cur = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[cur])
	{
		if (str[cur] == '\'')
			s_quote++;
		else if (str[cur] == '\"')
			d_quote++;
	cur++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
	{
		printf("miss_quote\n");
		return (STDERR);
	}
	return (0);
}
