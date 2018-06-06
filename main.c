/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:09:13 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/07 17:38:56 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		init_opt(t_opt *opt)
{
	opt->uid_min = 0;
	opt->gid_min = 0;
	opt->nlink_min = 0;
	opt->size_min = 0;
	opt->expad = 0;
}

void		print_total_blocks(t_args *head, t_opt *opt)
{
	t_args		*tmp;
	struct stat	fstat;
	int			total;

	tmp = head;
	total = 0;
	while (tmp)
	{
		lstat(tmp->fulln, &fstat);
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && opt->a))
			total = total + fstat.st_blocks;
		tmp = tmp->next;
	}
	if (count_args(head, opt))
		ft_printf("total %d\n", total);
}

void		print_no_args(t_args *head, t_opt *opt)
{
	if (opt->l)
	{
		init_opt(opt);
		print_no_long(head, opt);
	}
	else
		print_no(head, opt);
}

static void	print_wargs(t_args *head, t_opt *opt)
{
	opt->firstr = 0;
	opt->wfile = 0;
	if (opt->l)
	{
		init_opt(opt);
		print_long(head, opt);
	}
	else
		print(head, opt);
}

int			main(int argc, char **argv)
{
	t_opt	opt;
	t_args	*head;
	int		i;

	head = NULL;
	opt.ret = 0;
	parsing_opt(&opt, argv, argc, &i);
	head = parsing_args(head, &opt, argv, &i);
	check_args(head, &opt);
	if (opt.wargs)
		print_wargs(head, &opt);
	else
	{
		print_no_args(head, &opt);
		if (opt.bigr)
			print_recursive(head, &opt);
	}
	free_list(head);
	return (opt.ret);
}
