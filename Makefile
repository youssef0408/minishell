# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yothmani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 15:11:03 by yothmani          #+#    #+#              #
#    Updated: 2023/12/01 15:25:01 by yothmani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= minishell
NAME_BONUS 			= minishell_bonus

CC 					= gcc
CFLAGS 				= -Wall -Wextra -Werror

RM					= rm -rf

LIBFT 				= $(LIBFT_DIR)/libft.a

SRC_DIR 			= src
BONUS_DIR 			= bonus/src_bonus
INC_DIR 			= includes
INCS_DIR_BONUS		= bonus/bonus_includes
LIBFT_DIR 			= lib/libft

INC 				= -I$(INC_DIR) -I$(LIBFT_DIR)
INC_BONUS 			= -I$(INCS_DIR_BONUS) -I$(LIBFT_DIR)



SRC = $(SRC_DIR)/main.c

BONUS_SRC = $(BONUS_DIR)/

OBJ 				= $(SRC:.c=.o)
BONUS_OBJ 			= $(BONUS_SRC:.c=.o)


all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(INC) 
	@printf $(CUT)$(CUT)$(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) "Notre minishell est plus mignon qu’un vrai shell" $(RESET)
	

$(NAME_BONUS): $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(INC_BONUS)
	@printf $(CUT)$(CUT)$(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) "Bonus part!"
	

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC) $(INC_BONUS)
	@echo "Compiled $<"

norm :
	@echo $(BOLD)$(PINK)" Mandatory part!"$(MINT)
	@norminette $(SRC) $(INC_DIR)
	@echo $(BOLD)$(PINK)" Bonus part!"$(MINT)
	@norminette $(BONUS_SRC) $(INCS_DIR_BONUS)


leaks:
	leaks --atExit -- ./minishell

leaks_bonus:
	leaks --atExit -- ./minishell_bonus

clean :
	@make -C $(LIBFT_DIR) clean
	@printf $(CUT)$(CUT)
	@$(RM) $(OBJ) $(BONUS_OBJ) minishell.dSYM
	@echo $(BOLD)$(L_PURPLE)"Cleaned objects and executables!" ... 🧹🗑️$(RESET)

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS) minishell.dSYM
	@printf $(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) ✨minishell✨ $(PINK)All cleaned up! ....🧹🗑️$(RESET)

re: fclean all bonus

.PHONY: all bonus clean fclean re

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

