/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:18:40 by yothmani          #+#    #+#             */
/*   Updated: 2024/02/21 14:11:15 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin.h"
# include "execution.h"
# include "libft/includes/libft.h"
# include "parse.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <lib/readline-8.1/history.h>
# include <lib/readline-8.1/readline.h>
# include <limits.h>
# include <math.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/*#############################|| Characters ||#####################*/
// # define PIPE 124        // |
// # define REDIR_I 60      // <
// # define REDIR_O 62      // >
// # define SINGLE_QUOTE 39 // '
// # define DOUBLE_QUOTE 34 // "

/*#############################|| Colors ||#####################*/
# define RED "1;31"
# define GREEN "1;32"
# define YELLOW "1;33"
# define BLUE "1;34"
# define MAGENTA "1;35"
# define CYAN "1;36"
# define WHITE "1;37"
# define BOLD_RED "1;91"
# define BOLD_GREEN "1;92"
# define BOLD_YELLOW "1;93"
# define BOLD_BLUE "1;94"
# define BOLD_MAGENTA "1;95"
# define BOLD_CYAN "1;96"
# define BOLD_WHITE "1;97"

/*#############|| Structures and tokens ||################*/
// typedef enum e_tokentype
// {
// 	ALPHA_T = 97,
// 	REDIR_IN_T = 60,
// 	REDIR_OUT_T = 62,
// 	REDIR_AP_T = 43,
// 	PIPE_T = 124,
// 	HERE_DOC_T = 45,
// }				t_tokentype;

// typedef struct s_token
// {
// 	t_tokentype	type;
// 	char		*value;
// 	char		*to_print;
// 	char		*to_exec;
// 	char		*end_;
// 	char		*new_;
// 	int			i;
// 	int			init;
// 	int			len;
// 	int			pos;
// 	bool		append;
// }				t_token;

/*#############################|| lexer.c ||##############################*/
// t_list			*tokenizer(const char *str, t_list *token_list);
// void			temp_error(int i, t_list *token_list, t_token *token);
/*#############################|| quote_handler.c ||######################*/
// int				quotes_parser(const char *str, int i, t_token *token,
// int delimiter);

/*#############################|| utils.c ||##############################*/
char		*trim_str(char *str);
void		*safe_calloc(size_t nmemb, size_t size);
void		print_in_color(char *color, char *msg);
bool		is_white_space(char c);
int			ft_strcmp(char *s1, char *s2);
void		close_pipes(int lst_size, int **pipes);
/*#############################|| debug.c ||##############################*/
void		log_printf(const char *format, ...);
void		print_cmd(void *content);
void		print_token(void *content);

/*#############################|| Prompt.c ||############################*/
char		*display_prompt(void);
static char	*print_colored_message(const char *user, const char *path);

/*#############################|| free_and_exit.c ||#####################*/

void		exit_prg_at_error(char *str);
void		free_token(void *token_ptr);
void		free_cmd(void *cmd);
void		clean_table(char **table);
void		free_array(void **content);

int			**pipes_creation(int lst_size);
void		main_exec(t_list *cmd_list, char **envp);
void		clean_process(t_list *token_list, t_list *cmd_list, char *cmd_str);

/*#############################|| signals.c ||#####################*/

void		init_signal_handlers(void);

#endif
