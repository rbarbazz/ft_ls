/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:19:32 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/01/28 15:26:21 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	apply_precision(t_arg *arg)
{
	while (arg->prec-- > 0)
		arg->buffer = ft_strjoinchar(arg->buffer, '0');
	return (0);
}

static int	apply_flags(t_arg *arg)
{
	if (arg->flag_sharp && arg->itoaed[0] != '0' && (arg->specifier == 'o' || \
				arg->specifier == 'O'))
		arg->buffer = ft_strjoinchar(arg->buffer, '0');
	else if (arg->flag_sharp && arg->itoaed[0] != '0' && (arg->specifier == 'x'\
				|| arg->specifier == 'X'))
	{
		if (arg->specifier == 'x')
			arg->buffer = ft_strcat(arg->buffer, "0x");
		if (arg->specifier == 'X')
			arg->buffer = ft_strcat(arg->buffer, "0X");
	}
	if (arg->flag_two == '+' && !ft_strchr("uUoOxX", arg->specifier))
		arg->buffer = ft_strjoinchar(arg->buffer, '+');
	else if (arg->flag_two == ' ' && arg->specifier != 'u')
		arg->buffer = ft_strjoinchar(arg->buffer, ' ');
	return (0);
}

static int	calc_width_and_precision(t_arg *arg)
{
	arg->width -= ft_strlen(arg->itoaed);
	if (arg->itoaed[0] == '0' && arg->prec == 0)
		arg->width += ft_strlen(arg->itoaed);
	if ((arg->flag_sharp && arg->itoaed[0] != '0' && (arg->specifier == 'o' ||\
					arg->specifier == 'O' || arg->specifier == 'x' ||\
					arg->specifier == 'X')) || (arg->flag_two && arg->itoaed[0]\
					!= '-'))
	{
		if (arg->specifier == 'x' || arg->specifier == 'X')
			arg->width--;
		arg->width--;
		if ((arg->specifier == 'o' || arg->specifier == 'O') && arg->flag_sharp\
				&& arg->prec)
			arg->prec--;
	}
	if (arg->prec >= 0)
		arg->prec -= ft_strlen(arg->itoaed);
	if (arg->itoaed[0] == '-')
	{
		arg->flag_two = '\0';
		arg->prec++;
	}
	if (arg->prec >= 0)
		arg->width -= arg->prec;
	return (0);
}

int			convert_int_long(t_arg *arg)
{
	int		save;

	save = arg->prec;
	calc_width_and_precision(arg);
	if (!arg->flag)
		apply_width(arg);
	if (arg->itoaed[0] == '-')
	{
		arg->buffer = ft_strjoinchar(arg->buffer, '-');
		ft_memmove(arg->itoaed, arg->itoaed + 1, ft_strlen(arg->itoaed + 1)\
	+ 1);
	}
	apply_flags(arg);
	apply_precision(arg);
	if (arg->width > 0 && arg->flag != '-')
		apply_width(arg);
	if ((arg->itoaed[0] == '0' && !save && !arg->flag_sharp) || (arg->itoaed[0]\
				== '0' && !save && (arg->specifier == 'x' ||\
					arg->specifier == 'X') && arg->flag_sharp))
		return (0);
	while (*arg->itoaed)
		arg->buffer = ft_strjoinchar(arg->buffer, *arg->itoaed++);
	apply_width(arg);
	return (0);
}
