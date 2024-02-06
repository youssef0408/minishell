/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:48:25 by yothmani          #+#    #+#             */
/*   Updated: 2023/12/13 17:48:37 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_puterror(int function, char *str)
{
	if (!str)
		str = strerror(errno);
	if (function == -1)
	{
		printf("Error: %s\n", str);
		exit(EXIT_FAILURE);
	}
}
