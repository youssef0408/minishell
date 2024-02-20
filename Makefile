# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bplante <bplante@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 08:17:58 by ldufour           #+#    #+#              #
#    Updated: 2024/02/20 16:11:59 by bplante          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = minishell
CC              = gcc
CFLAGS          = -g #-Wall -Wextra -Werror
RM              = rm -rf
LIBFT           = $(LIBFT_DIR)/libft.a
SRC_DIR         = src
OBJ_DIR			= obj
INC_DIR         = includes
LIBFT_DIR       = lib/libft
READLINE_DIR    = lib/readline-8.1
READLINE_LIB    = $(READLINE_DIR)/libreadline.a
READLINE_INC    = -I$(READLINE_DIR)/include
READLINE_URL    = ftp://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz

INC             = -I$(INC_DIR) -I$(LIBFT_DIR) $(READLINE_INC)
LIBS            = -lncurses -L$(READLINE_DIR) -lreadline -lhistory -Llib/libft -lft

SRC_FILES = 	main.c  prompt.c builtin/pwd.c\
     			utils.c builtin/cd.c  env_utils.c\
      			builtin/echo.c  builtin/env.c\
	  			tokenizer/redirections.c tokenizer/syntax.c tokenizer/syntax_error.c\
	  			tokenizer/quotes_handler.c child_process.c\
      			builtin/built_exit.c signals.c\
	  			builtin/export.c builtin/unset.c builtin/builtin_execution.c \
				command_execution.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: install $(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ) $(LIBFT) $(READLINE_LIB)
	@$(DISPLAY_LOGOS)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)
	@echo $(CUT) $(CUT) 
	@echo $(BOLD)$(L_PURPLE) Notre minishell est plus mignon qu’un vrai shell  💪💥 $(RESET)	

$(READLINE_LIB): $(READLINE_DIR)
	@if [ ! -f "$@" ]; then \
		echo $(BOLD)$(PINK)"Building Readline 8.1 library..."$(MINT); \
		cd $(READLINE_DIR) && ./configure --prefix=$(CURDIR) && make; \
		echo $(BOLD)$(GREEN)"Readline library built successfully"$(RESET); \
	else \
		echo $(BOLD)$(PINK)"nothing to be done for all."$(RESET); \
	fi

$(READLINE_DIR):
	@mkdir -p $(READLINE_DIR)
	@test -f $(READLINE_DIR)/libreadline.a || { curl -L $(READLINE_URL) | tar xz -C $(READLINE_DIR) --strip-components=1; }
	@echo $(BOLD)$(GREEN) ✨ Readline 8.1 ✨ downloaded and extracted successfully. 💪💥 $(RESET)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)
	@echo "Compiled $<"

$(OBJ_DIR):
	mkdir -p obj/builtin obj/tokenizer
readline-8.1_EXISTS := $(wildcard lib/readline-8.1)

install: $(READLINE_LIB)
	
norm:
	@echo $(BOLD)$(PINK)" Mandatory part!"$(MINT)
	@norminette $(SRC) $(INC_DIR)
	@echo $(BOLD)$(PINK)" Bonus part!"$(MINT)
	@norminette $(BONUS_SRC)

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR)
	@echo $(BOLD)$(GREEN) Cleaned objects and executables! ... 🧹🗑️$(RESET)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME) 
	@echo $(BOLD)$(L_PURPLE) ✨minishell✨ $(PINK)All cleaned up! ....🧹🗑️$(RESET)

re: fclean all

test:
	@echo $(OBJ)

.PHONY: all clean fclean re install
