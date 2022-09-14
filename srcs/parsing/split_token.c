/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:22:59 by msuji             #+#    #+#             */
/*   Updated: 2022/09/14 12:03:33 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	redirection_end(char *str, int *cur)
{
	char	c;

	c = str[*cur];
	while (c == str[*cur] && str[*cur])
		(*cur)++;
}

int	word_end(char *str, int *cur)
{
	t_quote_check	quote;

	quote = NO;
	while (str[(*cur)])
	{
		quote = is_quote(str[*cur], quote);
		if (is_separator(str[*cur]) == 1 && quote == NO)
			break ;
		if (quote == NO && (str[*cur] == '|')
			&& str[*cur + 1] != ' ' && str[*cur + 1] != '\0')
		{
			(*cur)++;
			break ;
		}
		else if (str[*cur] && str[*cur + 1] == '|')
		{
			(*cur)++ ;
			break ;
		}
		(*cur)++ ;
	}
	return (0);
}

void	init_type(t_token *new)
{
	int	len;

	if (new->string)
		len = ft_strlen(new->string);
	if (len == 1)
	{
		if (new->string[0] == '>' || new->string[0] == '<')
			new->kind = TOKEN_OP;
		if (new->string[0] == '|')
			new->kind = TOKEN_PIPE;
	}
	if (len >= 2)
	{
		if (new->string[0] == '>' && new->string[1] == '>')
			new->kind = TOKEN_OP;
		if (new->string[0] == '<' && new->string[1] == '<')
			new->kind = TOKEN_OP;
	}
	if (len != 0 && new->kind == DEFAULT)
		new->kind = TOKEN_ARGUMENT;
}

static int	tokenization(int cur, int start, char *str, t_command *command_line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (1);
	init_token(token);
	token->string = malloc(sizeof(char *) * (cur - start + 1));
	if (token->string == NULL)
	{
		if (token)
			free(token);
		return (1);
	}
	token->string = ft_strncpy(token->string, str + start, cur - start);
	token->len = cur - start;
	init_type(token);
	if (g_exit_status == 5)
	{
		if (token)
			free(token);
		return (1);
	}
	token_addback(&(command_line)->first_token, token);
	return (0);
}

int	split_command_line(t_command *command_line)
{
	int	cur;
	int	len;
	int	start;

	cur = 0;
	len = 0;
	start = 0;
	if (command_line->whole_str != NULL)
		len = ft_strlen(command_line->whole_str + 1);
	while (cur <= len)
	{
		while (cur <= len && command_line->whole_str[cur] == ' ' )
			cur++;
		start = cur;
		if (is_redirection(command_line->whole_str[cur])
			&& command_line->whole_str[cur])
			redirection_end(command_line->whole_str, &cur);
		else
			word_end(command_line->whole_str, &cur);
		if (tokenization(cur, start, command_line->whole_str, command_line) > 0)
			return (1);
	}
	if (put_eof(command_line, 0, 0) > 0)
		free(command_line);
	return (0);
}
