/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:36:50 by msuji             #+#    #+#             */
/*   Updated: 2022/08/12 16:16:36 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
construction de parsing:
en utilisant la regle EBNF(Extended BNF(Backs-Naur form)) par chque token,
apres on parse par chaque resultat de token.
*/

/*
## EBNF pour  VRAI shell
parser    = stmt EOF
stmt      = pipe_cmd ("||" | "&&") pipe_cmd)*  ";"? separator
pipe_cmd  = bracket ("|" bracket)*
bracket   = "(" stmt ")"
          | cmd
cmd       = (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word 
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...

=============

## EBNF pour Minishell de mtsuji 
parser    = pipe_cmd EOF
pipe_cmd  = command ("|" command)*
command   = word (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...
EOF       = ε (nothing (= 0))
*/

//parser    = pipe_cmd EOF
t_node *parser(t_token *token)
{
     t_node *node;

    node = pipe_cmd(&token);
    if (exit_status == 5)
    {
        printf("minishell: syntax error near unexpected token `newline'\n");
        exit_status = 2;
        return (NULL);
    }
    else if (exit_status == 6)
    {
        exit_status = 2;
        return (NULL);
    }
    else
    {
        token = skip(token, TOKEN_EOF, NULL);
        return (node);
    }
}   


//pipe_cmd  = command ("|" command)*
t_node *pipe_cmd(t_token **token)
{
    t_node *node;
    if (exit_status != 5 && exit_status != 6)
    {
        node =  new_node_pipe(command(token));
        if (exit_status == 5 || exit_status == 6)
            return (NULL);
        while (consume(*token, TOKEN_PIPE, "|"))
        {
            *token = skip(*token, TOKEN_PIPE, "|");
            node  = add_node_pipe(node, command(token));
        }
    } 
    return (node);
}

//redir_in  = ("<" | "<<") word
void redir_in(t_token **token, t_node *node)
{
    if (ft_strnstr((*token)->string, "<<<", ft_strlen((*token)->string)))
    {
        exit_status = 6;
        ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
        return ;
    }
    if (consume(*token, TOKEN_OP, "<"))
    {
        *token = skip(*token, TOKEN_OP, "<");
        redir_in_addback(node->cmds, REDIR_IN, (*token)->string, (*token)->len);
    }
    else if (consume(*token, TOKEN_OP, "<<"))
    {
        *token = skip(*token, TOKEN_OP, "<<");
        redir_in_addback(node->cmds, REDIR_HEREDOC, (*token)->string, (*token)->len);
    } 
}

//redir_out = (">" | ">>") word
void redir_out(t_token **token, t_node *node)
{
    if (ft_strnstr((*token)->string, ">>>", ft_strlen((*token)->string)))
    {

        exit_status = 6;
        ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
        return ;
    }
    if (consume(*token, TOKEN_OP, ">"))
    {
        *token = skip(*token, TOKEN_OP, ">");
        redir_out_addback(node->cmds, REDIR_OUT, (*token)->string, (*token)->len);
    }
    else if (consume(*token, TOKEN_OP, ">>"))
    {
        *token = skip(*token, TOKEN_OP, ">>");
        redir_out_addback(node->cmds, REDIR_APPEND, (*token)->string, (*token)->len);
    } 
}

//command   = word (word | redir_in | redir_out)*
t_node *command(t_token **token)
{
    t_node *node;

    node = new_node_command();
    while (true)
    {
        if (exit_status == 5 || exit_status == 6)
        {
            free_node(node);
            return (node);
        }
        if (consume(*token, TOKEN_ARGUMENT, NULL))
            word_addback(node->cmds, (*token)->string, (*token)->len);
        else if (consume_redir(*token, TOKEN_OP, "<") || consume_redir(*token, TOKEN_OP, "<<"))
            redir_in(token, node);
        else if (consume_redir(*token, TOKEN_OP, ">") || consume_redir(*token, TOKEN_OP, ">>"))
            redir_out(token, node);
        else  
        {
            if (node->cmds->word == NULL && node->cmds->redir_in == NULL
                && node->cmds->redir_out == NULL)
                syntax_error(node);
            return (node);
        }
        if (exit_status != 6)
            *token = skip(*token, TOKEN_ARGUMENT, NULL); 
    }
}

void syntax_error(t_node *node)
{
    ft_putstr_fd("minishell: syntax error near unexpected token", 2);
    exit_status = 6;
    free_node(node);
}