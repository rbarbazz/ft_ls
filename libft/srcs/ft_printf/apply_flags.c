/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:51:51 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/02/22 13:41:50 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		check_flags(const char *format, t_arg *arg, int *i)
{
	if (format[*i] == '#')
		arg->flag_sharp = '#';
	else if (format[*i] == '-')
		arg->flag = '-';
	else if (format[*i] == '+')
		arg->flag_two = '+';
	else if (format[*i] == ' ' && arg->flag_two != '+')
		arg->flag_two = ' ';
	else if (format[*i] == '0' && arg->flag != '-')
		arg->flag = '0';
	else if (format[*i] == ' ' && arg->flag_two == '+')
		arg->flag_two = '+';
	else
		return (1);
	(*i)++;
	return (0);
}

int		check_width(const char *format, t_arg *arg, int *i, va_list ap)
{
	char	*tmp;
	int		itmp;

	itmp = 0;
	if (format[*i] == '*')
	{
		arg->width = va_arg(ap, int);
		(*i)++;
		return (0);
	}
	tmp = ft_memalloc(ft_strlen(format));
	while ((ft_isdigit(format[*i])) == 1)
	{
		tmp[itmp] = format[*i++];
		itmp++;
	}
	tmp[itmp] = '\0';
	if (!*tmp)
	{
		free(tmp);
		return (1);
	}
	arg->width = ft_atoi(tmp);
	free(tmp);
	return (0);
}

int		check_precision(const char *format, t_arg *arg, int *i)
{
	char	*tmp;
	int		itmp;

	itmp = 0;
	tmp = ft_memalloc(ft_strlen(format));
	if (format[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(format[*i]) == 1)
		{
			tmp[itmp] = format[*i];
			(*i)++;
			itmp++;
		}
		tmp[itmp] = '\0';
		if (!*tmp)
			arg->prec = 0;
		arg->prec = ft_atoi(tmp);
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

int		check_length(const char *format, t_arg *arg, int *i)
{
	if (format[*i] == 'h' && format[*i + 1] == 'h')
	{
		arg->length = "hh\0";
		(*i) = (*i) + 2;
	}
	else if (format[*i] == 'l' && format[*i + 1] == 'l')
	{
		arg->length = "ll\0";
		(*i) = (*i) + 2;
	}
	else if (format[(*i)] == 'h')
		arg->length = "h\0";
	else if (format[(*i)] == 'l')
		arg->length = "l\0";
	else if (format[(*i)] == 'j')
		arg->length = "j\0";
	else if (format[(*i)] == 'z')
		arg->length = "z\0";
	else
		return (1);
	if (ft_strlen(arg->length) == 1)
		(*i)++;
	return (0);
}

int		check_specifier(const char *format, t_arg *arg, int *i)
{
	if (format[*i] == 's' || format[*i] == 'S' || format[*i] == 'p'
			|| format[*i] == 'd' || format[*i] == 'D' || format[*i] == 'i'
			|| format[*i] == 'o' || format[*i] == 'O' || format[*i] == 'u'
			|| format[*i] == 'U' || format[*i] == 'x' || format[*i] == 'X'
			|| format[*i] == 'c' || format[*i] == 'C' || format[*i] == '%')
		arg->specifier = format[*i];
	else
		return (1);
	return (0);
}
