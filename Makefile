# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 09:16:25 by mgayout           #+#    #+#              #
#    Updated: 2024/06/10 12:23:12 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CFLAG		= -Wall -Wextra -Werror -g
RLFLAG		= -lreadline

GREEN=\033[0;32m
BLUE=\033[0;36m
RED=\033[0;31m
CLEAR_PREVIOUS_LINE = \033[2K\r
MOVE_CURSOR_UP = \033[1A

SRCDIR 		= src
OBJDIR 		= obj

SRCS		= $(shell find $(SRCDIR) -name '*.c')
OBJS		= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

INCLUDE		= includes
HEADER		= ./includes/minishell.h

TOTAL_OBJS	= $(words $(OBJS))
COUNTER		= 0
MSG_COUNTER = 0

centered_echo = \
  MESSAGE="$1"; \
  TERM_WIDTH=$$(tput cols); \
  MESSAGE_LENGTH=$$(( $$(echo "$$MESSAGE" | wc -c) - 1 )); \
  PADDING=$$(( (TERM_WIDTH - MESSAGE_LENGTH) / 2 )); \
  COLOR="$2"; \
  RESET="\033[0m"; \
  printf "%b%*s%b\n" "$$COLOR" $$((PADDING + MESSAGE_LENGTH)) "$$MESSAGE" "$$RESET"

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@$(call centered_echo, "\|" "Updating" "libft" "\|", $(BLUE))
	@make --no-print-directory all -C ./libft+/
	@$(call centered_echo, "\|" "Libft" "is" "updated" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Compiling" "minishell" "\|", $(BLUE))	
	@gcc $(CFLAG) -I$(INCLUDE) -o $(NAME) $(OBJS) ./libft+/libft.a $(RLFLAG)
	@$(call centered_echo, "\|" "Minishell" "is" "updated" "\|", $(GREEN))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER)+1))))
	@$(call centered_echo, "Compiling" $< ($$(($(COUNTER)))/$(TOTAL_OBJS)), $(BLUE))
	@$(eval MSG_COUNTER=$(shell echo $$(($(MSG_COUNTER)+1))))
	@if [ $$(($(MSG_COUNTER) % 5)) -eq 0 ]; then \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
			printf "$(MOVE_CURSOR_UP)$(CLEAR_PREVIOUS_LINE)"; \
    fi
	@gcc $(CFLAG) -I$(INCLUDE) -c $< -o $@

clean:
	@$(call centered_echo, "\|" "Removing" "objects" "from" "libft" "\|", $(RED))
	@make --no-print-directory clean -C ./libft+
	@$(call centered_echo, "\|" "All" "objects" "from" "libft" "have" "been" "deleted" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Removing" "objects" "\|", $(RED))
	@rm -rf $(OBJDIR)
	@$(call centered_echo, "\|" "All" "objects" "have" "been" "deleted" "\|", $(GREEN))

fclean: clean
	@$(call centered_echo, "\|" "Removing" "libft" "\|", $(RED))
	@make --no-print-directory fclean -C ./libft+
	@$(call centered_echo, "\|" "Libft" "have" "been" "deleted" "\|", $(GREEN))
	@$(call centered_echo, "\|" "Removing" "minishell" "\|", $(RED))
	@rm -rf $(NAME)
	@$(call centered_echo, "\|" "Minishell" "have" "been" "deleted" "\|", $(GREEN))

re: fclean all

.PHONY: all clean fclean re