# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: -tdontos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/02 12:58:40 by tdontos-          #+#    #+#              #
#    Updated: 2019/01/06 13:54:10 by tdontos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

LIBFT	= ../libft/
LIBFTLIB	= libft.a

SRC		= ft_printf.c check_format.c save_conf.c output.c read_flags.c read_arg.c

OBJDIR	= ./obj
OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror

all: obj $(NAME)

obj: 
	mkdir -p $(OBJDIR)

$(NAME):$(OBJ)
	@make -C $(LIBFT)
	@cp $(LIBFT)$(LIBFTLIB) $(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all