/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:48:32 by bplante           #+#    #+#             */
/*   Updated: 2024/03/25 00:49:24 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	handle_variable_end(bool *is_in_var, t_list **expansions,
		t_expansions **exp)
{
	*is_in_var = false;
	*expansions = (*expansions)->next;
	if (*expansions)
	{
		*exp = (t_expansions *)(*expansions)->content;
		return (false);
	}
	else
		return (true);
}

void	init_sv_info(t_sv_info *sv_info, t_list *expansions)
{
	sv_info->i = 0;
	sv_info->count = 0;
	sv_info->exp = expansions->content;
	sv_info->is_in_var = false;
	sv_info->has_char = false;
}

void	check_if_data_after_exp(t_sv_info *svi, char *data)
{
	if (svi->has_char)
		svi->count++;
	else if (!svi->has_char && ((data[svi->i] && data[svi->i + 1])
			|| svi->exp->is_quoted))
		svi->count++;
}
