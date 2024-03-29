/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:10:23 by msuji             #+#    #+#             */
/*   Updated: 2022/09/13 12:22:44 by mtsuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MINISHELL "MINISHELL$ "
# define STDERR 2
# define STDIN 0
# define STDOUT 1
# define PATH_MAX 4096
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_exit
{
	int			exit_status;
	bool		interrupt;
}	t_exit;

extern t_exit	g_exit;

typedef enum e_quote_check
{
	NO,
	SINGLE,
	DOUBLE,
	S_CLOSE,
	D_CLOSE,
}	t_quote_check;

typedef enum e_token_kind
{
	DEFAULT,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_OP,
	TOKEN_EOF,
}	t_token_kind;

typedef enum e_node_kind
{
	BUILTIN,
	COMMAND,
	PIPE,
	NODE_EOF,
}	t_node_kind;

typedef enum e_redir_kind
{
	REDIR_OUT,
	REDIR_IN,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_kind;

typedef struct s_redir
{
	t_redir_kind	kind;
	char			*str;
	int				fd;
	int				cur;
	bool			no_expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_node
{
	t_node_kind		kind;
	struct s_node	*next;
	int				val;
	char			*str;
	int				len;
	struct s_node	*lhs;
	struct s_node	*rhs;
	struct s_cmd	*cmds;
	t_redir			*redir_in;
	t_redir			*redir_out;
}t_node;

typedef struct s_word
{
	struct s_word	*next;
	char			*str;
}	t_word;

typedef struct s_cmd
{
	t_redir	*redir_in;
	t_redir	*redir_out;
	t_word	*word;
	bool	is_builtin;
	char	*pathname;
}	t_cmd;

typedef struct s_token
{
	int				cur;
	int				len;
	char			*string;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	int					cur;
	char				*whole_str;
	char				*command;
	t_token				*first_token;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*name;
	char			*body;
	struct s_env	*next;
}	t_env;

typedef struct s_comm
{
	int				isbuiltin;
	int				pipe[2];
	char			**args;
	char			**files;
	struct s_comm	*next;
}	t_comm;

typedef struct s_shell
{
	int			ret;
	int			definput;
	int			defoutput;
	int			fdin;
	int			fdout;
	char		*outfile;
	int			nb_cmds;
	t_comm		*cmds;
	char		**envp;
	char		**paths;
	t_env		*env;
	int			interrupt;
}				t_shell;

void			start_command(char *str, t_shell *shell);
int				only_space(char *str);
int				pipe_check(char *str);

//signal
void			signal_init_handle(int signal);
void			signal_init(void);
void			signal_exec_handle(int signal);
void			signal_exec(void);
void			signal_heredoc_handle(int signal);
void			signal_heredoc(void);

//env | shell
t_shell			*create_shell(char **envp, char **argv);
t_env			*create_env(char **envp);
t_env			*env_addback(t_env *env, char *name, char *body);
char			*create_env_name(char *str);
char			*create_env_name_with_plus(char *str);
char			*create_env_body(char *str);
char			*create_env_body_with_plus(char *str);
long			get_env_size(t_shell *shell);
char			**create_envp(t_shell *shell);
char			**create_argv(t_word *word);
void			env_add(char *str, t_shell *shell);
void			env_add_with_plus(char *str, t_shell *shell);
t_env			*new_env(char *name, char *body);
void			env_rewrite(t_shell *shell, char *name, char *body);
void			env_rewrite_with_plus(t_shell *shell, char *name, char *body);
void			del_env(char *str, t_shell *shell);

//lexer
t_command		*lexer(char *str);
int				quote_check(char *str);
int				simple_quote(char *str);
int				double_quote(char *str);
int				quoting(char *str);
int				first_word_is_pipe(char *str);
int				first_word_colon_exclamation(char *str);
void			ft_error(char *str);

//get_command_line
t_command		*get_command_line(char *str);
int				filling_command_line(char *str, int cur, int start, \
				t_command **command_line);
void			commandline_addback(t_command *line, t_command *new);
void			check_pipe(int cur, char *str);

//tokenization
void			init_type(t_token *new);

int				split_command_line(t_command *command_line);
int				split_command_to_token(t_command *command_line);
void			token_addback(t_token **tkn, t_token *new);
void			init_token(t_token *new);
int				is_redirection(char c);
int				is_separator(char c);
t_quote_check	is_quote(char c, t_quote_check quote);
int				word_end(char *str, int *cur);
int				put_eof(t_command *command_line, char *str, int len);

//parser
t_node			*stmt(t_token **token);
t_node			*parser(t_token *token);
t_node			*pipe_cmd(t_token **token);
t_node			*command(t_token **token);
t_node			*word(t_token **token);
void			syntax_error(t_node *node);
void			command_error_check(t_node *node);

//util_for_parser
bool			consume(t_token *token, t_token_kind kind, char *str);
bool			consume_redir(t_token *token, t_token_kind kind, char *str);
t_token			*skip(t_token *token, t_token_kind kind, char *str);
void			parser_error(char *str, long len);
t_node			*new_node_pipe(t_node *cmd_node);
t_node			*add_node_pipe(t_node *node, t_node *cmd_node);
t_node			*new_node_command(void);
t_node			*new_node_word(t_token *token);
void			word_addback(t_cmd *command, char *str, long len);
void			redir_in(t_token **token, t_node *node);
void			redir_out(t_token **token, t_node *node);
void			redir_in_addback(t_cmd *command, t_redir_kind kind, \
				char *str, int len);
void			redir_out_addback(t_cmd *command, t_redir_kind kind, \
				char *str, int len);

//expension
void			expander(t_node *node, t_shell *shell);
void			expand_var(t_node *node, t_shell *shell);
void			expand_var_in_word(t_word *word, t_shell *shell);
void			expand_var_in_redir(t_redir *redir, t_shell *shell);
char			*expand_var_in_str(char *str, t_shell *shell);
long			at_doller_mark(char *str, char **new, long i, t_shell *shell);
void			split_space(t_node *node);
t_word			*split_space_in_word(t_word *word);
t_word			*create_splited_words(char *str);
long			get_word_len_to_space(char *str);
t_node			expension(t_node *node);
char			*remove_quote_string(char *str);
void			remove_quote_word(t_word *word);
void			remove_quote_redir(t_redir *redir);
void			remove_quote_heredoc(t_redir *redir);
void			remove_quote(t_node *node);
void			pathname_generator(t_node *node, t_shell *shell);
char			*get_pathname_str(char *str, t_shell *shell);
t_quote_check	quote_check2(char *str, t_quote_check quote);

//util for expansion
char			*add_char(char *str, char c);
char			*ft_strjoin_and_free(char *s1, int i1, char *s2, int i2);
char			*get_env_body(char *name, t_shell *shell);
char			*get_var_name(char *str);
int				is_var_name_char(char c);
int				is_var_name_char_1st(char c);
char			*ft_str_add_char(char *str, char c);
void			word_add_back_for_split(t_word *word, char *str);
t_word			*word_last(t_word *word);
char			*sarch_pathname(char *str, t_shell *shell);
int				check_pathname(char *pathname);
long			after_doller_check(char *str, char *new, long i);

//free
int				free_lexer(t_command *command_line);
void			free_token(t_command **command_line);
void			free_node(t_node *node);
void			free_word(t_word *word);
void			free_redirection(t_redir *redir_in);
void			free_envp(char **envp);
void			free_env(t_shell *shell);
void			free_end(t_command *command_line, char *str);
void			free_for_unset(t_env *env);

//echo
int				echo(t_word *word);
int				echo_option(char *str);

//env
int				env(t_word *word, t_shell *shell);

//pwd
int				pwd(t_word *word);
int				pwd_argument_check(char *str);
void			pwd_error(char *str);

//cd
int				cd(t_word *word, t_shell *shell);
void			after_cd(t_shell *shell);
int				go_home(t_shell *shell);
int				cd_argument_check(char *str);
void			cd_error(char *str);

//export
int				builtin_export(t_word *word, t_shell *shell);
void			display_env_for_export(t_shell *shell);
int				check_argument_for_export(char *str);
int				export_option(int res, char *str);
void			export_error(char *str);
int				check_env(char *str);
int				inside_checker_export(char *str);

//unset
int				unset(t_word *word, t_shell *shell);
void			unset_error(char *str);
int				inside_checker_unset(char *str);
int				unset_argument_check(char *str);
int				unset_option(int res, char *str);

//exit
int				builtin_exit(t_word *word);
int				overflow_check(char *str);
int				check_int(char *str);

//shell
t_shell			*init_all(void);
char			*get_path_line(char **paths);
char			**get_paths(t_shell *shell, char **envp);
void			exit_shell(t_shell *shell, int code);
void			free_all(t_shell *shell);
void			free_paths(t_shell *shell);
void			free_path(char **paths);
void			free_cmds(t_shell *shell);
void			fill_data(t_shell *shell, char **args);
void			lst_addback(t_comm **lst, t_comm *new);
bool			isbuiltin(char *str);

//heredoc
bool			is_heredoc_eof(char *line, char *eof);
void			write_heredoc_to_fd(t_redir *redir, t_shell *shell, int fd);
void			set_heredoc(t_redir *redir, t_shell *shell);
void			expander_set_heredoc(t_node *node, t_shell *shell);
char			*expand_var_heredoc(t_redir *redir, char *str, t_shell *shell);

//exec
void			exec(t_node *node, t_shell *shell);
void			exec_pipe(t_node *pipe_node, t_shell *shell);
void			exec_multi_pipes(t_node *pipe_node, t_shell *shell);
void			exec_no_pipe(t_node *pipe_node, t_shell *shell);
void			exec_cmd(t_node *node, t_shell *shell);
void			exec_file(t_node *node, t_shell *shell);
void			set_exit_status(void);
bool			check_cmd(t_cmd *cmd);
bool			is_directory(char *pathname);
int				fail_exec(t_node *node);
bool			set_redir_out(t_redir *redir_out);
bool			set_redir_in(t_redir *redir_in);
void			exec_builtin(t_node *node, t_shell *shell);
void			no_builtin(void);
void			redir_in_error(void);
void			redir_out_error(void);
pid_t			my_fork(void);
void			printer_redir(char *str);
#endif
