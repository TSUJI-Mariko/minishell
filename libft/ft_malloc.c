/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <ahocine@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:23:59 by mtsuji            #+#    #+#             */
/*   Updated: 2022/09/09 13:35:23 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	g_crash_every = 550;
static int	g_test_number = 0;

void	*ft_malloc(size_t size)
{
	if (g_crash_every > 0 && g_test_number++ >= g_crash_every)
		return (g_test_number = 0, \
		ft_putstr_fd("Out of memory\n", 2), NULL);
	return (malloc(size));
}
