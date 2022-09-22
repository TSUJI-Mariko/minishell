/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:08:20 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/09 13:36:50 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	word_add_back_for_split(t_word *word, char *str)
{
	t_word	*new;
	t_word	*last;

	if (str == NULL)
		return ;
	new = ft_calloc(1, sizeof(t_word));
	if (!new)
		return ;
	new->str = str;
	while (word->next)
		word = word->next;
	last = word;
	last->next = new;
}

t_word	*word_last(t_word *word)
{
	while (word->next)
		word = word->next;
	return (word);
}
