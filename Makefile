# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtsuji <mtsuji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 17:01:55 by mtsuji            #+#    #+#              #
#    Updated: 2022/07/09 17:01:56 by mtsuji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell

SRCS	=	./src/minishell.c	\
#			./src/key_hook.c	\
#			./src/error_message.c\
#			./src/actions.c	\
#			./src/drawing.c	\
#			./src/render_map.c	\
#			./src/init_images.c	\
#			./bonus/printer_ascii.c	\
#			./bonus/action_enemy.c	\

OBJS	=	$(SRCS:.c=.o)

HEADER	=	./inc/

LIBFT	=	./lib/libft/

LIBFT_A	=	./lib/libft/libft.a

CC	=	gcc

RM	=	rm -f

#CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address 

.c.o:
	$(CC) $(CFLAGS) -I$(HEADER) -I$(LIBFT) $(LIB) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
			@make -C $(LIBFT)
			ar rcs $(LIBFT_A) $(OBJS)
			ranlib $(LIBFT_A)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

all:	$(NAME)

clean:
		$(MAKE) clean -C $(LIBFT)
		$(RM) $(OBJS)

fclean:	clean
		$(MAKE) fclean -C $(LIBFT)
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
