/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:47:34 by mtsuji            #+#    #+#             */
/*   Updated: 2022/08/12 18:47:36 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*int parser(t_token *tkn)
{

    return (0);
}
*/
/*
construction de parsing:
en utilisant la regle EBNF(Extended BNF(Backs-Naur form)) par chque token,
apres on parse par chaque resultat de token.
ordre d'algo : 
1 word
2 redir in /out
3 command(builtin)
4 pipe command (separateur)
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

## EBNF pour Minishell 
parser    = pipe_cmd EOF
pipe_cmd  = command ("|" command)*
command   = word (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...
EOF       = ε (nothing (= 0))
*/

t_token *skip(t_token *tok, t_token_kind kind, char *str) 
{
	if (tok->kind != kind)
		printf("skip error : unexpected kind\n");//error
	if (str != NULL && ft_strncmp(tok->string, str, tok->len))
		printf("skip error : unexpectrd str\n");//error
	return tok->next;
}

bool equal(t_token *tok, t_token_kind kind, char *str) 
{
	if (tok->kind != kind)
		return false;
	if (str != NULL && ft_strncmp(tok->string, str, tok->len))
		return false;
	return true;
}
t_node *new_node_pipe(t_node *lhs, t_node *rhs) {
    t_node *node = ft_calloc(1, sizeof(t_node));
    node->kind = PIPE;
    node->lhs = lhs;
    node->rhs = rhs;
    return (node);
}

t_node *new_node_command() {
    t_node *node = ft_calloc(1, sizeof(t_node));
    node->kind = BUILTIN;
    return node;    
}

void add_command(t_node *cmd, t_node *word) {
    if (cmd->cmds == NULL) {
        cmd->cmds = word;
        return ;
    }
    t_node *last = cmd->cmds;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = word;
}

void add_command_redir_in(t_node *cmd, t_node *redir_in) {
    if (cmd->redir_in == NULL) {
        cmd->redir_in = redir_in;
        return ;
    }
    t_node *last = cmd->redir_in;
    while (last->next != NULL)
        last = last->next;
    last->next = redir_in;
}

void add_command_redir_out(t_node *cmd, t_node *redir_out) {
    if (cmd->redir_out == NULL) {
        cmd->redir_out = redir_out;
        return ;
    }
    t_node *last = cmd->redir_out;
    while (last->next != NULL)
        last = last->next;
    last->next = redir_out;
}

t_node *new_node_word(t_token *tok) {
    t_node *node = ft_calloc(1, sizeof(t_node));
    node->kind = ARGUMENT;
    node->str = ft_substr(tok->string, 0, tok->len);
    return node;
}

t_node *parser(t_token *tok);
t_node *pipe_cmd(t_token **tok);
t_node *command(t_token **tok);
t_node *redir_in(t_token **tok);
t_node *redir_out(t_token **tok);
t_node *word(t_token **tok);

// parser = pipe_cmd EOF
t_node *parser(t_token *tok) {
    t_node *node = pipe_cmd(&tok);
    if (!equal(tok, TOKEN_EOF, NULL))
    {
        printf("parser error: expected EOF\n");//error
        exit(0);
    }
    tok = skip(tok, TOKEN_EOF, NULL);
    return (node);
}

// pipe_cmd = command ("|" command)*
t_node *pipe_cmd(t_token **tok) {
    t_node *node = new_node_pipe(NULL, command(tok));

    while (equal(*tok, OP, "|")) {
        *tok = skip(*tok, OP, "|");
        node = new_node_pipe(node, command(tok));
    }
    return (node);
}

// command = word (word | redir_in | redir_out)*
t_node *command(t_token **tok) {
    t_node *node = new_node_command();
    add_command(node, word(tok));
    while (true) {
        if (equal(*tok, ARGUMENT, NULL))
            add_command(node, word(tok));
        else if (equal(*tok, OP, "<") || equal(*tok, OP, "<<"))
            add_command_redir_in(node, redir_in(tok));
        else if (equal(*tok, OP, ">") || equal(*tok, OP, ">>"))
            add_command_redir_out(node, redir_out(tok));
        else
            break;
    }
    return node;
}

// redir_in = ("<" | "<<") word
t_node *redir_in(t_token **tok) {
    if (equal(*tok, OP, "<"))
        *tok = skip(*tok, OP, "<");
    else if (equal(*tok, OP, "<<"))
        *tok = skip(*tok, OP, "<<");
    else
        printf("parser error: expected '<' or '<<'");//error
    t_node *node = word(tok);
    return node;
}

// redir_out = (">" | ">>") word
t_node *redir_out(t_token **tok) {
    if (equal(*tok, OP, ">"))
        *tok = skip(*tok, OP, ">");
    else if (equal(*tok, OP, ">>"))
        *tok = skip(*tok, OP, ">>");
    else
        printf("parser error: expected '>' or '>>'");//error
    t_node *node = word(tok);
    return node;
}

// word = (e.g.) "ls", "-l", "file", ...
t_node *word(t_token **tok) {
    t_node *node;
    if (equal(*tok, ARGUMENT, NULL))
        node = new_node_word(*tok);
    *tok = skip(*tok, ARGUMENT, NULL);
    return node;
}

void free_node(t_node *node) {
    if (node == NULL)
        return;
    free_node(node->lhs);
    free_node(node->rhs);
    free_node(node->next);
    free_node(node->cmds);
    free_node(node->redir_in);
    free_node(node->redir_out);
    free(node);
}
