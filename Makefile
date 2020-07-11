# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: -tdontos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/02 12:58:40 by tdontos-          #+#    #+#              #
#    Updated: 2019/05/29 15:37:44 by tdontos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap

SRCDIR	= ./src
OBJDIR	= ./obj

# src / obj files
SRC		= main.c utils.c flags.c validation.c search_median.c command.c

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# ft library
FTDIR	= libft
PFTDIR	= ft_printf
FT_LIB	= $(addprefix $(FTDIR)/,libft.a)
PFT_LIB	= $(addprefix $(PFTDIR)/,libftprintf.a)
FT_INC	= -I $(FTDIR)
H_INC	= -I inc
PFT_INC	= -I $(PFTDIR)
FT_LNK	= -L $(FTDIR) -lft
PFT_LNK	= -L $(PFTDIR) -lftprintf

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(H_INC) $(FT_INC) $(PFT_INC) -o $@ -c $<

$(FT_LIB):
	@make -C $(PFTDIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FT_LNK) $(PFT_LNK) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(PFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(PFTDIR) fclean

re: fclean all
