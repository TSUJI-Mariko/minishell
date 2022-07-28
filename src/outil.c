/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:16:07 by mtsuji            #+#    #+#             */
/*   Updated: 2022/07/28 12:16:08 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//int valeur_exit;

/*
** signal_input : gerer l'interruprion par clavier (Ctrl + c)
**
*/
void    signal_input(int signal)
{
    int valeur_exit;

    valeur_exit = 0;
    valeur_exit += signal;
    if (valeur_exit == 2)
    {
        valeur_exit = 130; //valeur de retour avec Ctrl + C
        printf("\n");
        printf(">team_90's ");
    }
}
