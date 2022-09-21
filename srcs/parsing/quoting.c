/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:15:39 by msuji             #+#    #+#             */
/*   Updated: 2022/09/11 19:43:52 by msuji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quote_check(char *str)
{
	int				i;
	t_quote_check	quote;

	i = 0;
	quote = NO;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (quote == NO)
				quote = DOUBLE;
			else if (quote == DOUBLE)
				quote = NO;
		}
		if (str[i] == '\'')
		{
			if (quote == NO)
				quote = SINGLE;
			else if (quote == SINGLE)
				quote = NO;
		}
		i++;
	}
	return (quote);
}
