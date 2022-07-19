/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:04:50 by mtsuji            #+#    #+#             */
/*   Updated: 2022/07/09 17:04:54 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//void minishell(char **envp);/
void sig_int_input();
void sig_quit_input();

// int main(int argc, char **argv, char **envp)
int main(int argc, char **argv, char **envp)
{
   if (argc == 1)
    {
       minishell(envp);
    }
    else 
    {
        printf("%s\n", argv[1]);
        while (envp != NULL)
        {
            printf("%s\n",*envp);
            envp++;
        }
    }
    return (0);
}

void minishell(char **envp)
{
    char *prompt;
    char *line;
    char **copy_env;
    //t_arg copy;
    int i;

    i = 0;
    copy_env = malloc(sizeof(envp));
    line = malloc(sizeof(char *) + 10000);
    if (line == NULL)
        return ;

    while(envp[i])
    {
        copy_env[i] = strdup(envp[i]);
        i++;
    }
    while (1)
    {
        prompt = readline(line);
        if (prompt == NULL)
        {   
            free(line);
            break;
        }
        else
            ft_putstr_fd(prompt, 1);
    }
    i = 0;
    while (copy_env[i])
    {
        free(copy_env[i]);
        i++;
    }
}
/*
void minishell(char **envp)
{
  char *line;
  int  ret;
  
  ret = 0;
  while(1)
  {
      //char *line;
      
      ft_putstr_fd(MINISHELL, STDERR);
	   // ctrl+C, ctrl+\ の指示
	   if (signal(SIGINT, sig_int_input) == SIG_ERR)
	   {
	       ft_putstr_fd(strerror(errno), STDERR);
		   exit (1);
	   }
	   if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
	   {
	       ft_putstr_fd(strerror(errno), STDERR);
		   exit (1);
  	   }
      // 文字を受け取る
      if ((get_next_line(0, &line) == 0))
		{
	        ft_putstr_fd("exit\n", STDERR);
			exit (ret);
		}
      ft_putstr_fd(line, STDERR);
      ft_putstr_fd("\n", STDERR);
      free(line);
  }
}


void	sig_int_input()
{
	ft_putstr_fd("\b\b  \b\n", STDERR);
	ft_putstr_fd(MINISHELL, STDERR);
}

void	sig_quit_input()
{
	ft_putstr_fd("\b\b  \b\b", STDERR);
}
*/

