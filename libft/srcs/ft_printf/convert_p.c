/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 09:47:24 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/01/26 18:03:02 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		apply_width(t_arg *arg)
{
	while (arg->width-- > 0)
	{
		if (arg->flag == '0')
			arg->buffer = ft_strjoinchar(arg->buffer, '0');
		else
			arg->buffer = ft_strjoinchar(arg->buffer, ' ');
	}
	return (0);
}

int		convert_p(t_arg *arg)
{
	char *itoa;
	char *ptr;
	char *nul;

	nul = "0x";
	itoa = ft_itoa((unsigned long)arg->p, 16, 0);
	ptr = itoa;
	if (arg->p)
		arg->width = arg->width - ft_strlen(ptr) - 2;
	else
		arg->width -= 3;
	if (!arg->flag)
		apply_width(arg);
	while (*nul)
		arg->buffer = ft_strjoinchar(arg->buffer, *nul++);
	if (!arg->p)
		arg->buffer = ft_strjoinchar(arg->buffer, '0');
	while (arg->p && *ptr)
		arg->buffer = ft_strjoinchar(arg->buffer, *ptr++);
	apply_width(arg);
	free(itoa);
	return (0);
}
