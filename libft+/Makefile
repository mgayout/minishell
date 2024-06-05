# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 14:27:16 by mgayout           #+#    #+#              #
#    Updated: 2023/11/09 14:27:16 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
CC				=	@gcc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	@rm -rf
PATH_PF			=	./ft_printf+/
PATH_GN			=	./get_next_line+/
SRC 			=	ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii \
					ft_isdigit ft_isprint ft_memchr ft_memcmp ft_memcpy ft_memmove \
					ft_memset ft_strchr ft_strdup ft_strdup_free ft_strlcat ft_strlcpy ft_strncpy \
					ft_strlen ft_strncmp ft_strnstr ft_strrchr ft_tolower ft_toupper ft_substr \
					ft_strjoin ft_strjoin_free ft_strtrim ft_split ft_itoa ft_itoa_char ft_strmapi ft_striteri \
					ft_putchar_fd ft_putstr_fd ft_putstr_fd_free ft_putendl_fd ft_putnbr_fd ft_lstnew \
					ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone \
					ft_lstclear ft_lstiter ft_lstmap \

SRC_PF			=	$(PATH_PF)ft_printf $(PATH_PF)libft/ft_putchar_fd $(PATH_PF)libft/ft_putnbr_fd \
					$(PATH_PF)libft/ft_putstr_fd $(PATH_PF)libft/ft_strlen \

SRC_GN			=	$(PATH_GN)get_next_line $(PATH_GN)get_next_line_utils \

SRC_A			=	$(addsuffix .c, ${SRC}) $(addsuffix .c, ${SRC_PF}) $(addsuffix .c, ${SRC_GN})

OBJ				=	$(SRC_A:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJ) 
					@ar -rc $(NAME) $(OBJ)

clean:
					$(RM) $(OBJ)

fclean: 		clean
					$(RM) $(NAME)

re:				fclean all

.PHONY: 		all clean fclean re
