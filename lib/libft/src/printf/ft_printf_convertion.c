/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convertion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante/Walord <benplante99@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:36:18 by bplante           #+#    #+#             */
/*   Updated: 2023/12/12 19:39:53 by bplante/Wal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*arg_to_str(char *str)
{
	char	*output;

	if (!str)
		output = ft_strdup("(null)");
	else
		output = ft_strdup(str);
	return (output);
}

char	*arg_to_uint_hex(unsigned long num, int is_caps)
{
	unsigned long	n_cpy;
	unsigned long	i;
	char			*str;

	n_cpy = num;
	i = 0;
	while (++i && n_cpy)
		n_cpy /= 16;
	if (num == 0)
		i++;
	str = ft_calloc(1, i);
	if (!str)
		return (NULL);
	else if (num == 0)
		str[0] = '0';
	while (num != 0)
	{
		str[i - 2] = num_to_hex(num % 16, is_caps);
		num /= 16;
		i--;
	}
	return (str);
}

char	num_to_hex(int num, int is_caps)
{
	char	maj;

	maj = 'a';
	if (is_caps)
		maj = 'A';
	if (num > 9)
		return (num - 10 + maj);
	return (num + '0');
}

char	*arg_to_uint(unsigned int num)
{
	unsigned int	n_cpy;
	unsigned int	i;
	char			*str;

	n_cpy = num;
	i = 0;
	while (++i && n_cpy)
		n_cpy /= 10;
	if (num == 0)
		i++;
	str = ft_calloc(1, i);
	if (!str)
		return (0);
	else if (num == 0)
		str[0] = '0';
	while (num != 0)
	{
		str[i - 2] = num % 10 + '0';
		num /= 10;
		i--;
	}
	return (str);
}

char	*arg_to_ptr(void *ptr)
{
	char	*output;
	char	*str;

	str = arg_to_uint_hex((unsigned long)ptr, 0);
	if (!str)
		return (NULL);
	output = ft_strjoin("0x", str);
	free(str);
	return (output);
}
