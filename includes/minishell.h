/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:18:40 by yothmani          #+#    #+#             */
/*   Updated: 2024/03/22 22:54:41 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/includes/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include "parser.h"
# include "builtin.h"
# include "execution.h"

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
#define FD_IN 0
#define FD_OUT 1
#define NO_RED -2
#define EOINTA -3
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
void		print_in_color(const char *color, const char *msg);
bool		is_white_space(char c);
int			ft_strcmp(const char *s1, const char *s2);
void		close_pipes(int lst_size, int **pipes);
/*#############################|| debug.c ||##############################*/
void		log_printf(const char *format, ...);
void		print_cmd(void *content);
void		print_token(void *content);

/*#############################|| Prompt.c ||############################*/
char		*display_prompt(void);
char		*print_colored_message(const char *user, const char *path);
/*#############################|| free_and_exit.c ||#####################*/

void		exit_prg_at_error(char *str);
void		free_token(void *token_ptr);
void		free_cmd(void *info);
void		clean_table(char **table);
void		free_array(void **content, void (del)(void *));

int			**pipes_creation(int lst_size);
void		main_exec(t_list *cmd_list, char **envp);
void		clean_process(t_list *token_list, t_list *cmd_list, char *cmd_str);

/*#############################|| signals.c ||#####################*/

void		init_signal_handlers(void);

/*#############################|| env ||###############################*/
char		*join_key_value(t_list *node);
/**
 * @brief Get the value in the list that matches the key,
	returns null if no key found
 *
 * @return returns a const char *,
	do not free it is a pointer to the original value
 */
const char	*get_value_with_key(t_list *env, const char *key);
/**
 * @brief converts the list to char ** array to be passed to execve
 */
char		**env_list_to_envp(t_list *env);
/**
 * @brief adds a key value pair to env if pair is not found,
	if key already exists updates the key
 *
 * @param env
 * @param key if key is null it segfaults, key cannot be null
 * @param value if value is NULL, stores a zero len string instead
 */
void		add_to_env(t_list **env, const char *key, char *value);
/**
 * @brief removes a key value pair from the list,
	if key isnt found it does nothing
 */
void		remove_from_env(t_list **env, const char *key);
/**
 * @brief converts an envp array to a dict list for internal use
 */
t_list		*convert_envp(char **envp);
/**
 * @brief function to free_the_struct inside the list to free the list
 * to be used with ft_lstclear()
 */
void		free_key_value(void *key_value);
void		free_t_command(t_command *info);

int			lst_auto_add_back(t_list **lst, void *content);
int			here_doc(char *del);
void		close_irrelevant_fds(int *fds, int pos);
void		close_non_std_fds(int *fds);
int			get_cmd_path(t_command *info, char **args);

#endif
