/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstauto_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:45:53 by bplante           #+#    #+#             */
/*   Updated: 2024/03/13 11:46:39 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	lst_auto_add_back(t_list **lst, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		exit_prg_at_error("malloc failure");
	ft_lstadd_back(lst, new);
	return (0);
}
