<<<<<<< HEAD
#------------------------------------#
#             COMPILATION            #
#------------------------------------#

NAME		= minishell

FLAGS		= -Wall -Wextra -Werror -g3
INCLUDE		= -I $(HEAD_DIR) -L/usr/include -lreadline
CC			= gcc

#------------------------------------#
#               SOURCES              #
#------------------------------------#

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_FILE))
SRC_DIR		=	srcs/
SRC_FILE	=	main/minishell.c				\
				main/outil_main.c				\
				\
				signal/signal_init.c			\
				signal/signal_exec.c			\
				signal/signal_heredoc.c			\
				\
				parsing/outil_lexer.c			\
				parsing/quoting.c 				\
				parsing/lexer.c 				\
				parsing/get_command_line.c 		\
				parsing/split_token.c 			\
				parsing/outil_split_token.c 	\
				parsing/outil.c					\
				parsing/parser_cmd_redir.c		\
				parsing/parser_pipe_cmd.c		\
				parsing/parser.c				\
				parsing/outil_parser.c			\
				parsing/outil_parser2.c			\
				parsing/outil_parser3.c			\
				\
				shell/get_env.c					\
				shell/get_env2.c				\
				shell/create_shell.c			\
				shell/create_shell2.c			\
				shell/create_envp.c				\
				shell/env_add.c					\
				shell/del_env.c					\
				\
				expansion/expansion.c			\
				expansion/variables.c			\
				expansion/outil_variables.c		\
				expansion/outil_variables_2.c	\
				expansion/split_string.c		\
				expansion/outil_split.c			\
				expansion/remove_quote.c		\
				expansion/path_generator.c		\
				expansion/outil_path.c			\
				expansion/heredoc.c				\
				expansion/outil_heredoc.c		\
				\
				builtin/echo.c					\
				builtin/cd.c					\
				builtin/outil_cd.c				\
				builtin/env.c					\
				builtin/pwd.c					\
				builtin/outil_export.c			\
				builtin/export.c				\
				builtin/unset.c					\
				builtin/exit.c					\
				\
				exec/exec.c						\
				exec/exec_pipe.c				\
				exec/exec_multi_pipe.c			\
				exec/exec_command.c				\
				exec/exec_outil.c				\
				exec/exec_outil2.c				\
				exec/exec_builtin.c				\
				exec/exec_redir.c				\
				exec/exec_file.c

#------------------------------------#
#               OBJECTS              #
#------------------------------------#

OBJS	=	$(addprefix $(OBJ_DIR), $(OBJ))
OBJ		=	$(SRC_FILE:.c=.o)
OBJ_DIR	=	obj/

#------------------------------------#
#              INCLUDES              #
#------------------------------------#

HEADER		= $(addprefix $(HEAD_DIR), $(HEAD_FILE))
HEAD_DIR	= includes/
HEAD_FILE	= minishell.h

LIBFT		= $(addprefix $(LIB_DIR), $(LIBFT_A))
LIB_DIR		= libft/
LIBFT_A		= libft.a

#------------------------------------#
#               COLORS               #
#------------------------------------#

NONE		= "\033[0m"
GREEN		= "\033[32m"
YELLOW		= "\033[33m"
GRAY		= "\033[2;37m"
CURSIVE		= "\033[3m"

#------------------------------------#
#                RULES               #
#------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(CURSIVE)$(GREEN) "     ~ Making $(LIB_DIR)..." $(END)
	make -C $(LIB_DIR)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(INCLUDE) -I includes -o $(NAME)
	@echo $(GREEN)"- Project compiled -"$(NONE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)/parsing/ $(OBJ_DIR)/main/ $(OBJ_DIR)/expansion/ $(OBJ_DIR)/exec/ $(OBJ_DIR)/builtin/ $(OBJ_DIR)/shell/ $(OBJ_DIR)/signal/ 
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@ -I inc

=======
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
>>>>>>> master

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	make clean -C $(LIB_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -f $(NAME)
	make fclean -C $(LIB_DIR)
	@echo $(YELLOW)"- Project removed -"$(NONE)

re: fclean all

.PHONY : clean fclean re