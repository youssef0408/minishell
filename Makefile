# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bplante <bplante@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 08:17:58 by ldufour           #+#    #+#              #
#    Updated: 2024/03/25 12:52:23 by bplante          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = minishell
CC              = gcc
CFLAGS          = -g -Wall -Wextra -Werror
RM              = rm -rf
LIBFT           = $(LIBFT_DIR)/libft.a
SRC_DIR         = src
OBJ_DIR			= obj
INC_DIR         = includes
LIBFT_DIR       = lib/libft
READLINE_DIR    = lib/readline
READLINE_LIB    = $(READLINE_DIR)/libreadline.a
READLINE_INC    = -I$(READLINE_DIR)
READLINE_URL    = ftp://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz

INC             = -Ilib $(READLINE_INC) -I.
LIBS            = -L$(READLINE_DIR) -lreadline -lhistory -Llib/libft -lft -lncurses

SRC_FILES = 	main.c  execution/prompt.c builtin/pwd.c\
     			execution/utils.c builtin/cd.c execution/redirections_handler.c\
				execution/redirections_utils.c\
				execution/cmd_path.c execution/handle_fds.c\
				execution/exec_single_builtin.c\
      			builtin/echo.c  builtin/env.c\
      			builtin/built_exit.c execution/signals.c\
	  			builtin/export.c builtin/export_utils.c builtin/unset.c builtin/builtin_execution.c \
				execution/command_execution.c parser/ft_strndup.c parser/parser.c parser/redirections.c parser/tokenizer.c parser/var_loading.c \
				parser/variable_expansion.c parser/syntax_errors.c parser/struct_free.c parser/free_array.c parser/count_cmd.c \
				execution/env_manager.c execution/exec_utils.c execution/env_utils.c parser/parse_utils.c parser/tokenizer_utils.c parser/lst_to_array.c\
				parser/redirections_utils.c main_utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT) $(READLINE_LIB)
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
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)
	@echo "Compiled $<"


$(OBJ_DIR):
	mkdir -p obj/builtin obj/tokenizer obj/parser
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
