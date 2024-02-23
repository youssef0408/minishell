/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:37:40 by bplante				#+#    #+#             */
/*   Updated: 2024/02/22 12:38:20 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

enum			e_infile_type
{
	FILE_NAME,
	HEREDOC
};

enum			e_outfile_type
{
	TRUNC,
	APPEND
};

typedef struct s_infile
{
	enum		e_infile_type;
	char		*del_file;
}				t_infile;

typedef struct s_outfile
{
	enum		e_outfile_type;
	char		*file;
}				t_outfile;

typedef struct s_input_parse
{
	char		***cmds;
	t_infile	*infiles;
	t_outfile	*outfiles;
}				t_input_parse;

int	parse_input(char *input, t_input_parse *input_parse)
{
	// char	*trimed_input;
	// int		cmd_count;
	// cpy_redirections(input, input_parse);
	// trimed_input = trim_redirections(input, input_parse);
	// // free original input here if the add_history copies by value
	// cmd_count = count_cmd_blocks(trimed_input);
}

struct			s_litteral_tracker
{
	int			is_lit;
	char		quote;
};

//<<>>echo test
//bash: syntax error near unexpected token `>>'
//to get value, read until next token, if value size is zero prompt error


bool	is_litteral(char c, struct s_litteral_tracker *lt)
{
	if (c == '\\' && ((lt->quote == 0 && lt->is_lit == 0) || (lt->quote != 0
				&& lt->is_lit == 1)))
		lt->is_lit++;
	else if (lt->is_lit == 0 && (c == '\'' || c == '\"')
			&& lt->quote == 0)
	{
		lt->quote = c;
		lt->is_lit++;
	}
	else if (lt->is_lit == 1 && c == lt->quote)
	{
		lt->is_lit--;
		lt->quote = 0;
	}
	else if (lt->is_lit == 2 || (lt->is_lit == 1 && lt->quote == 0))
		lt->is_lit--;
	else if (lt->is_lit == 0)
		return false;
	return true;
}

void	cpy_redirections(char *input, t_input_parse *input_parse)
{
	int	i;
	struct s_litteral_tracker lt;
	bool is_redirect;

	is_redirect = false;
	lt.is_lit = 0;
	lt.quote = 0;
	i = 0;
	while (input[i])
	{
		if (!is_litteral(input[i], &lt))
		{
			//either count redirection or only get last one 
		}
		i++;
	}
}

int	get_trimed_input_len(char *input, t_input_parse *input_parse)
{
}

char	*trim_redirections(char *input, t_input_parse *input_parse)
{
}

int	count_cmd_blocks(char *input)
{
}