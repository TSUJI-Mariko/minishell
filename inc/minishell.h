/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:06:07 by mtsuji            #+#    #+#             */
/*   Updated: 2022/07/09 17:06:08 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MINISHELL "MINISHELL$ "
# define STDERR 2
# define STDIN 0
# define STDOUT 1
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

extern int valeur_exit; 

typedef struct s_command
{
	char    **copy_env;
	int		cur;
	char	*str;
	char *argv;
	struct s_command	*next;
}		t_command;

typedef struct s_token
{
	int				cur;
	int 			len;
    char            *string;
	struct s_token	*next;
}		t_token;



void    signal_input(int signal);
int quote_check(char *str);
int simple_quote(char *str);
int double_quote(char *str);
int quoting(char *str);
int lexer(char *str, t_command **command_line);
int get_command_line(char *str, t_command **command_line);
int split_command_to_token(char *str, t_command **command_line);
int split_command_line(t_command **token);
void init_command_line(t_command *command_line);
# endif