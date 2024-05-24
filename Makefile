# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 09:16:25 by mgayout           #+#    #+#              #
#    Updated: 2024/05/24 16:52:55 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
MINIFLAG = -lreadline -g
SRC_DIR = src/
SRC_LEX_DIR = src/lexer/
SRC_PAR_DIR = src/parser/
SRC_EXP_DIR = src/expander/
SRC_EXE_DIR = src/exec/
SRC_BUI_DIR = src/builtins/
OBJ_DIR = obj/
LIBFT = libft+/libft.a

SRC =	main \
		env \
		check_errors \
		free \
		free2 \

SRC_LEX	=	lexer \
			lexer_type \
			lexer_quote \
			lexer_utils \
			lexer_function \
			lstr_function \

SRC_PAR =	parser \
			parser_init \
			parser_function \

SRC_EXP =	expander \
			expander_init \
			expander_env \
			expander_utils \
			expander_function \

SRC_EXE =	exec \
			exec_init \
			exec_file_cmd \
			exec_file_pipeline \
			exec_utils \
			exec_cmd \

SRC_BUI =	builtins echo cd pwd export unset env exit \

SRCS =	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

SRCS_LEX = $(addprefix $(SRC_LEX_DIR), $(addsuffix .c, $(SRC_LEX)))

SRCS_PAR = $(addprefix $(SRC_PAR_DIR), $(addsuffix .c, $(SRC_PAR)))

SRCS_EXP =	$(addprefix $(SRC_EXP_DIR), $(addsuffix .c, $(SRC_EXP)))
		
SRCS_EXE =	$(addprefix $(SRC_EXE_DIR), $(addsuffix .c, $(SRC_EXE)))

SRCS_BUI = $(addprefix $(SRC_BUI_DIR), $(addsuffix .c, $(SRC_BUI)))

SRCSS =	$(SRCS) $(SRCS_LEX) $(SRCS_PAR) $(SRCS_EXP) $(SRCS_EXE) $(SRCS_BUI)

#OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft+/

$(NAME):
	@$(CC) $(SRCSS) $(LIBFT) $(CFLAGS) $(MINIFLAG) -o $(NAME) 

#$(OBJ_DIR)%.o: $(SRC_DIR)%.c
#	mkdir -p $(@D)
#	$(CC) $(LIBFT) $(CFLAGS) -c $< -o $@

clean:
#	$(RM) $(OBJ_DIR)
	make clean -C libft+/

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft+/

re: fclean all

.PHONY: all clean fclean re