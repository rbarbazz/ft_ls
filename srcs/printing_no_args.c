/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_no_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:23:59 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/07 16:15:58 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_no(t_args *head, t_opt *opt)
{
	t_args		*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && opt->a))
		{
			ft_printf("%s\n", tmp->name);
			opt->wfile = 1;
		}
		tmp = tmp->next;
	}
}

void		print_no_long(t_args *head, t_opt *opt)
{
	t_args		*tmp;
	char		buf[2048];
	struct stat	fstat;

	tmp = head;
	check_min_width(head, opt);
	print_total_blocks(head, opt);
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && opt->a))
		{
			lstat(tmp->fulln, &fstat);
			print_stats(tmp, opt, fstat, buf);
			opt->wfile = 1;
		}
		tmp = tmp->next;
	}
}
