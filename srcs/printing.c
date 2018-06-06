/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:40:56 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/07 14:30:53 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print(t_args *head, t_opt *opt)
{
	t_args		*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->file && tmp->wpath)
		{
			ft_printf("%s\n", tmp->fulln);
			opt->wfile = 1;
		}
		else if (tmp->file)
		{
			ft_printf("%s\n", tmp->name);
			opt->wfile = 1;
		}
		tmp = tmp->next;
	}
	print_recursive(head, opt);
}

void		print_long(t_args *head, t_opt *opt)
{
	t_args		*tmp;
	char		buf[2048];
	struct stat	fstat;

	tmp = head;
	check_min_width(head, opt);
	while (tmp)
	{
		if (tmp->file)
		{
			lstat(tmp->fulln, &fstat);
			print_stats(tmp, opt, fstat, buf);
			opt->wfile = 1;
		}
		tmp = tmp->next;
	}
	print_recursive(head, opt);
}
