/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:09:16 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/07 17:10:06 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_perm_curr(t_args *tmp, t_opt *opt)
{
	struct stat	fstat;

	opt->othx = 0;
	if (!lstat(tmp->fulln, &fstat) && !(fstat.st_mode & S_IROTH))
	{
		tmp->valid = 1;
		opt->ret = 1;
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && opt->a))
			ft_printf("ft_ls: %s: Permission denied\n", tmp->name);
		return (1);
	}
	if (!lstat(tmp->fulln, &fstat) && !(fstat.st_mode & S_IXOTH))
	{
		opt->othx = 1;
		opt->ret = 1;
		return (1);
	}
	return (0);
}

int			count_args(t_args *head, t_opt *opt)
{
	t_args	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && opt->a))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	pre_checks(t_opt *opt, t_args *head, t_args *tmp)
{
	if ((opt->firstr && opt->wargs) || opt->wfile)
		ft_printf("\n");
	if (count_args(head, opt) != 1 || opt->firstr)
		ft_printf("%s:\n", tmp->fulln);
	if (!opt->firstr)
		opt->firstr = 1;
}

void		print_recursive(t_args *head, t_opt *opt)
{
	t_args	*tmp;
	t_args	*rec;

	tmp = head;
	while (tmp)
	{
		if (tmp->dir && ft_strcmp(".", tmp->name) && ft_strcmp("..", tmp->name))
		{
			pre_checks(opt, head, tmp);
			if (!check_perm_curr(tmp, opt))
			{
				rec = new_list(".", tmp->path, tmp->name);
				rec = get_curr_dir(rec, opt, tmp->fulln);
				check_args(rec, opt);
				if (opt->r)
					rec = reverse(rec);
				print_no_args(rec, opt);
				if (opt->bigr)
					print_recursive(rec, opt);
				free_list(rec);
			}
		}
		tmp = tmp->next;
	}
}
