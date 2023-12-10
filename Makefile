# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yothmani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 15:11:03 by yothmani          #+#    #+#              #
#    Updated: 2023/12/09 02:35:12 by yothmani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= minishell

CC 					= gcc
CFLAGS 				= -g 
# -Wall -Wextra -Werror 

RM					= rm -rf

LIBFT 				= $(LIBFT_DIR)/libft.a

SRC_DIR 			= src
INC_DIR 			= includes 
LIBFT_DIR 			= lib/libft

INC 				= -I$(INC_DIR) -I$(LIBFT_DIR) -lreadline



SRC = $(SRC_DIR)/main.c $(SRC_DIR)/prompt.c $(SRC_DIR)/builtin/pwd.c\
$(SRC_DIR)/utils.c $(SRC_DIR)/builtin/cd.c\


OBJ 				= $(SRC:.c=.o)


all: $(NAME)


$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(INC) 
	@printf $(CUT)$(CUT)$(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) "Notre minishell est plus mignon qu’un vrai shell  💪💥" $(RESET)
	

	

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)
	@echo "Compiled $<"

norm :
	@echo $(BOLD)$(PINK)" Mandatory part!"$(MINT)
	@norminette $(SRC) $(INC_DIR)
	@echo $(BOLD)$(PINK)" Bonus part!"$(MINT)
	@norminette $(BONUS_SRC)


leaks:
	leaks --atExit -- ./minishell | cat -e



clean :
	@make -C $(LIBFT_DIR) clean
	@printf $(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE)"Cleaned objects and executables!" ... 🧹🗑️$(RESET)

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@printf $(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) ✨minishell✨ $(PINK)All cleaned up! ....🧹🗑️$(RESET)

re: fclean all 

.PHONY: all clean fclean re

# ######################### Color #########################

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

