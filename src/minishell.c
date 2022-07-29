/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:15:09 by mtsuji            #+#    #+#             */
/*   Updated: 2022/07/28 12:15:11 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/* memo;
pour complier :
gcc -Wall -Wextra -Werror  minishell.h lexer.c outil.c -lreadline libft/libft.a
*/
int valeur_exit;
/*
    valeur_exit : variable global pour la valeur de retour, mais on pourrait enlever
*/

//int main(int argc, char **argv, char **envp)
int main(int argc, char **argv)
{
    char *line;
    t_command *command_line;

    //int i;
    //char **env_cpy;

    //i = 0;
    /*env_cpy = malloc(sizeof(char) * **envp + 1);
    while (*envp[i])
    {
        *env_cpy[i] = *envp[i];
        i++; 
    }*/
    /*
    ** il faut elaborer get_env
    */
    command_line = NULL;
    //line = NULL;
    if (argc && argv)
    {
        while (1)
        {
            signal(SIGQUIT, SIG_IGN);
            if (signal(SIGINT, signal_input) == SIG_ERR)
                exit(1);
            line = readline(">team_90's ");
            if (line == NULL) 
            {
                free(line);
                break;
            }
            //if (!quote_check(line))
            if (!lexer(line, &command_line))
                printf("%s\n", line);
            add_history(line);
            free(line);
        }
    }
    printf("exit\n");
    free(line);
    //free(*env_cpy);
    return (valeur_exit);
}
/*
**
** quote_check : checker des quotes impares dans le string
*/
int quote_check(char *str)
{
    int cur;
    int s_quote;
    int d_quote;

    cur  = 0;
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
/*
** simple_quote : checker des quotes simples
**
*/
/*
int pipe_check(char *str)
{
    int cur;
    int pipe;

    cur  = 0;
    pipe = 0;
    while (str[cur])
    {
        if (str[cur] != '|')

    }
}

int string_check(char *str)
{
    int result;

    result = quote_check(str);
    result = 
}*/

int lexer(char *str, t_command **command_line)
{
    int res;

    res = quote_check(str);
    if (res > 0)
        return (1);
    if (get_command_line(str, command_line) > 0)
        return (1);
    if (split_command_to_token(str, command_line) > 0)
        return (1);
    return (0);
}

int get_command_line(char *str, t_command **command_line)
{
    t_command *data;    

    data = malloc(sizeof(t_command));
    if (data == NULL)
        return (1);
    init_command_line(data);
    return (0);
}

void init_command_line(t_command *command_line)
{  
    command_line->str = NULL;
    command_line->argv = NULL;
}

int split_command_to_token(char *str, t_command **command_line)
{
    t_command *token;

    token = *command_line;
    while (token)
    {
        if (split_command_line(&token) > 0)
            return (1);
        token = token->next;
    } 
    return (0);
}

int split_command_line(t_command **token)
{
    return (0);
}


//memo ; コマンドラインのフィリングが必要（ゲットコマンド関数内）