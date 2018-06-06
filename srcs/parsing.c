/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:13:02 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/07 17:59:45 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_opt(t_opt *opt, char **argv, int *i, int j)
{
	if (!argv[*i][j])
		return (1);
	while (argv[*i][j])
	{
		if (argv[*i][j] == 'l')
			opt->l = 1;
		else if (argv[*i][j] == 'r')
			opt->r = 1;
		else if (argv[*i][j] == 'R')
			opt->bigr = 1;
		else if (argv[*i][j] == 'a')
			opt->a = 1;
		else if (argv[*i][j] == 't')
			opt->t = 1;
		else
		{
			ft_printf("ft_ls illegal option -- %c\nusage: ./ft_ls [-lRart] \
[file ...]", argv[*i][j]);
			exit(1);
		}
		j++;
	}
	return (0);
}

void		parsing_opt(t_opt *opt, char **argv, int argc, int *i)
{
	int j;

	*i = 1;
	opt->l = 0;
	opt->r = 0;
	opt->bigr = 0;
	opt->a = 0;
	opt->t = 0;
	while (argc > *i && argv[*i][0] == '-')
	{
		j = 1;
		if (!check_opt(opt, argv, i, j))
			(*i)++;
		else
			break ;
	}
}

static void	check_invalid(t_args *tmp, t_opt *opt, struct stat *fstat)
{
	if (!lstat(tmp->path, fstat) && !(fstat->st_mode & S_IROTH))
	{
		tmp->valid = 1;
		opt->ret = 1;
		if (tmp->name[0] != '.' || (tmp->name[0] == '.' && opt->a))
			ft_printf("ft_ls: %s: Permission denied\n", tmp->name);
	}
	else if (lstat(tmp->fulln, fstat) == -1)
	{
		tmp->valid = 1;
		opt->ret = 1;
		ft_printf("ft_ls: %s: No such file or directory\n", tmp->fulln);
	}
}

void		check_args(t_args *head, t_opt *opt)
{
	t_args		*tmp;
	struct stat	fstat;

	tmp = head;
	while (tmp)
	{
		if (!lstat(tmp->fulln, &fstat))
		{
			if (S_ISDIR(fstat.st_mode))
				tmp->dir = 1;
			else if (S_ISCHR(fstat.st_mode))
				tmp->dev = 1;
			else
				tmp->file = 1;
		}
		check_invalid(tmp, opt, &fstat);
		tmp = tmp->next;
	}
}

t_args		*parsing_args(t_args *head, t_opt *opt, char **argv, int *i)
{
	if (argv[*i])
	{
		opt->wargs = 1;
		head = first_list(argv[(*i)++], "\0");
		while (argv[*i])
		{
			if (opt->t)
				head = ins_by_lastmod(head, argv[*i], "\0");
			else
				head = ins_by_name(head, argv[*i], "\0");
			(*i)++;
		}
	}
	else
	{
		opt->wargs = 0;
		head = first_list(".", "./");
		head = get_curr_dir(head, opt, ".");
	}
	if (opt->r)
		head = reverse(head);
	return (head);
}
