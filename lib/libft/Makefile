# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bplante <bplante@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 01:24:00 by yothmani          #+#    #+#              #
#    Updated: 2024/03/19 12:59:43 by bplante          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 				= libft.a

CC 					= gcc
CFLAGS 				= -Wall -Wextra -Werror

RM					= rm -rf

SRC_DIR 			= src
INC_DIR 			= includes

INC 				= -I $(INC_DIR)

SRC = $(SRC_DIR)/ft_strlen.c $(SRC_DIR)/ft_memset.c $(SRC_DIR)/ft_bzero.c $(SRC_DIR)/ft_isalnum.c \
$(SRC_DIR)/ft_isalpha.c $(SRC_DIR)/ft_isdigit.c $(SRC_DIR)/ft_isprint.c $(SRC_DIR)/ft_memcpy.c\
$(SRC_DIR)/ft_toupper.c $(SRC_DIR)/ft_tolower.c $(SRC_DIR)/ft_memmove.c $(SRC_DIR)/ft_memchr.c\
$(SRC_DIR)/ft_memcmp.c $(SRC_DIR)/ft_strncmp.c $(SRC_DIR)/ft_strrchr.c $(SRC_DIR)/ft_strlcpy.c\
$(SRC_DIR)/ft_strlcat.c $(SRC_DIR)/ft_strcpy.c  $(SRC_DIR)/ft_atoi.c $(SRC_DIR)/ft_strcat.c\
$(SRC_DIR)/ft_strnstr.c $(SRC_DIR)/ft_calloc.c $(SRC_DIR)/ft_strdup.c $(SRC_DIR)/ft_substr.c\
$(SRC_DIR)/ft_strjoin.c $(SRC_DIR)/ft_strtrim.c $(SRC_DIR)/ft_split.c $(SRC_DIR)/ft_putnbr_fd.c\
$(SRC_DIR)/ft_strmapi.c $(SRC_DIR)/ft_itoa.c $(SRC_DIR)/ft_putchar_fd.c $(SRC_DIR)/ft_putstr_fd.c\
$(SRC_DIR)/ft_putendl_fd.c $(SRC_DIR)/ft_putnbr_fd.c $(SRC_DIR)/ft_putnbr_fd.c $(SRC_DIR)/ft_strmapi.c\
$(SRC_DIR)/ft_strchr.c $(SRC_DIR)/ft_isascii.c $(SRC_DIR)/ft_striteri.c $(SRC_DIR)/ft_lstmap.c\
$(SRC_DIR)/ft_lstiter.c $(SRC_DIR)/ft_lstclear.c $(SRC_DIR)/ft_lstdelone.c $(SRC_DIR)/ft_lstdeletenode.c\
$(SRC_DIR)/ft_lstsize.c $(SRC_DIR)/ft_lstlast.c $(SRC_DIR)/ft_lstadd_front.c\
$(SRC_DIR)/ft_lstnew.c $(SRC_DIR)/ft_putstr.c $(SRC_DIR)/ft_putchar.c $(SRC_DIR)/ft_lstadd_back.c\
$(SRC_DIR)/printf/ft_printf_convertion.c $(SRC_DIR)/printf/ft_printf_utils.c $(SRC_DIR)/printf/ft_printf.c \
$(SRC_DIR)/lstauto_add_back.c

OBJ 				= $(SRC:.c=.o)

all: $(NAME)

	
$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@printf $(CUT)$(CUT)$(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) libft is ready! 💪💥$(RESET)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC) 
	@echo $(BOLD)$(GREEN) "Compiled $<"

norm :
	@echo $(BOLD)$(PINK)"_____LIBFT NORMINETTE!_____"$(MINT)
	@norminette $(SRC) $(INC_DIR)

clean :
	@printf $(CUT)$(CUT)
	@$(RM) $(OBJ) libft.dSYM
	

fclean : clean
	@$(RM) $(NAME)
	@printf $(CUT)$(CUT)
	

re: fclean all

.PHONY: all clean fclean re

# ######################### Colors #########################

GREEN="\033[32m"
MINT="\033[38;5;51m"
L_PURPLE="\033[38;5;55m"
MAUVE="\033[38;5;147m"
PINK="\033[38;5;175m"
RESET="\033[0m"
BOLD="\033[1m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"