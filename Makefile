# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msuji <mtsuji@student.42.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 12:35:48 by msuji             #+#    #+#              #
#    Updated: 2022/09/19 17:12:59 by msuji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell

SRCS	=	./srcs/main/minishell.c	\
			./srcs/main/outil_main.c	\
			./srcs/signal/signal_init.c		\
			./srcs/signal/signal_exec.c			\
			./srcs/signal/signal_heredoc.c		\
			./srcs/parsing/outil_lexer.c			\
			./srcs/parsing/quoting.c 			\
			./srcs/parsing/lexer.c 				\
			./srcs/parsing/get_command_line.c \
			./srcs/parsing/split_token.c 	\
			./srcs/parsing/outil_split_token.c 	\
			./srcs/parsing/outil.c			\
			./srcs/parsing/parser_cmd_redir.c			\
			./srcs/parsing/parser_pipe_cmd.c			\
			./srcs/parsing/parser.c			\
			./srcs/parsing/outil_parser.c			\
			./srcs/parsing/outil_parser2.c			\
			./srcs/parsing/outil_parser3.c	\
			./srcs/shell/get_env.c		\
			./srcs/shell/get_env2.c		\
			./srcs/shell/create_shell.c		\
			./srcs/shell/create_shell2.c		\
			./srcs/shell/create_envp.c		\
			./srcs/shell/env_add.c			\
			./srcs/shell/del_env.c			\
			./srcs/expansion/expansion.c		\
			./srcs/expansion/variables.c		\
			./srcs/expansion/outil_variables.c		\
			./srcs/expansion/outil_variables_2.c		\
			./srcs/expansion/split_string.c		\
			./srcs/expansion/outil_split.c		\
			./srcs/expansion/remove_quote.c		\
			./srcs/expansion/path_generator.c		\
			./srcs/expansion/outil_path.c		\
			./srcs/expansion/heredoc.c			\
			./srcs/expansion/outil_heredoc.c			\
			./srcs/builtin/echo.c			\
			./srcs/builtin/cd.c				\
			./srcs/builtin/outil_cd.c				\
			./srcs/builtin/env.c			\
			./srcs/builtin/pwd.c			\
			./srcs/builtin/outil_export.c			\
			./srcs/builtin/export.c			\
			./srcs/builtin/unset.c			\
			./srcs/builtin/exit.c			\
			./srcs/exec/exec.c				\
			./srcs/exec/exec_pipe.c			\
			./srcs/exec/exec_multi_pipe.c			\
			./srcs/exec/exec_command.c			\
			./srcs/exec/exec_outil.c			\
			./srcs/exec/exec_outil2.c			\
			./srcs/exec/exec_builtin.c			\
			./srcs/exec/exec_redir.c			\
			./srcs/exec/exec_file.c			\



OBJS	=	$(SRCS:.c=.o)

HEADER	=	./inc/

LIBFT	=	./libft/

LIBFT_A	=	./libft/libft.a

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address -fsanitize=leak

.c.o:
	$(CC) $(CFLAGS) -I$(HEADER) -I$(LIBFT) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
			@make -C $(LIBFT)
			ar rcs $(LIBFT_A) $(OBJS)
			ranlib $(LIBFT_A)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) -lreadline

all:	$(NAME)

clean:
		$(MAKE) clean -C $(LIBFT)
		$(RM) $(OBJS)

fclean:	clean
		$(MAKE) fclean -C $(LIBFT)
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
