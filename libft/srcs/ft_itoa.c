/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:36:23 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/01/12 17:31:12 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nbr_len_u(uintmax_t n, int base)
{
	int		i;

	i = 1;
	while (n >= (size_t)base)
	{
		++i;
		n /= base;
	}
	return (i);
}

char	digit(int nb, int maj)
{
	if (nb < 10)
		return ('0' + nb);
	if (maj)
		return ('A' + nb % 10);
	return ('a' + nb % 10);
}

char	*ft_itoa_u(uintmax_t n, int base, int maj)
{
	char	*res;
	int		size;

	size = nbr_len_u(n, base);
	if (!(res = malloc(sizeof(*res) * (size + 1))))
		return (NULL);
	res[size] = 0;
	while (size-- >= 1)
	{
		res[size] = digit(n % base, maj);
		n /= base;
	}
	return (res);
}

char	*ft_itoa(intmax_t n, int base, int maj)
{
	char	*res;
	char	*tmp;

	if (n < 0)
	{
		tmp = ft_itoa_u(-n, base, maj);
		res = ft_strjoin("-", tmp);
		free(tmp);
	}
	else
		res = ft_itoa_u(n, base, maj);
	return (res);
}
