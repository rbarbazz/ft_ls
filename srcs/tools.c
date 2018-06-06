/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 18:36:57 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/07 17:41:08 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	devfd(t_args *head, t_opt *opt)
{
	if (opt->t)
		head = ins_by_lastmod(head, "..", head->path);
	else
		head = ins_by_name(head, "..", head->path);
	if (opt->t)
		head = ins_by_lastmod(head, "0", head->path);
	else
		head = ins_by_name(head, "0", head->path);
}

t_args		*get_curr_dir(t_args *head, t_opt *opt, char *toopen)
{
	DIR					*currdir;
	struct dirent		*currfile;
	unsigned long long	currino;
	unsigned long long	fdino;

	currdir = opendir("/dev/fd");
	currfile = readdir(currdir);
	fdino = currfile->d_ino;
	closedir(currdir);
	currdir = opendir(toopen);
	currfile = readdir(currdir);
	currino = currfile->d_ino;
	while (currfile)
	{
		if (opt->t && currfile->d_ino != currino)
			head = ins_by_lastmod(head, currfile->d_name, head->path);
		else if (currfile->d_ino != currino)
			head = ins_by_name(head, currfile->d_name, head->path);
		currfile = readdir(currdir);
	}
	if (currino == fdino)
		devfd(head, opt);
	closedir(currdir);
	return (head);
}

static void	check_rdev(t_opt *opt, struct stat fstat, char *itoaed)
{
	itoaed = ft_itoa(major(fstat.st_rdev), 10, 0);
	if (ft_strlen(itoaed) > opt->size_min)
		opt->size_min = ft_strlen(itoaed);
	free(itoaed);
	itoaed = ft_itoa(minor(fstat.st_rdev), 10, 0);
	if (ft_strlen(itoaed) > opt->size_min)
		opt->size_min = ft_strlen(itoaed);
	free(itoaed);
}

static void	check_id(t_opt *opt, struct stat fstat, char *itoaed)
{
	itoaed = getpwuid(fstat.st_uid) ?\
			ft_strdup(getpwuid(fstat.st_uid)->pw_name) :\
			ft_itoa(fstat.st_uid, 10, 0);
	if (ft_strlen(itoaed) > opt->uid_min)
		opt->uid_min = ft_strlen(itoaed);
	free(itoaed);
	itoaed = getgrgid(fstat.st_gid) ?\
			ft_strdup(getgrgid(fstat.st_gid)->gr_name) :\
			ft_itoa(fstat.st_gid, 10, 0);
	if (ft_strlen(itoaed) > opt->gid_min)
		opt->gid_min = ft_strlen(itoaed);
	free(itoaed);
}

void		check_min_width(t_args *head, t_opt *opt)
{
	struct stat	fstat;
	t_args		*tmp;
	char		*itoaed;

	tmp = head;
	while (tmp)
	{
		if (tmp->name[0] != '.' || (opt->a && tmp->name[0] == '.'))
		{
			lstat(tmp->fulln, &fstat);
			check_id(opt, fstat, itoaed);
			check_rdev(opt, fstat, itoaed);
			itoaed = ft_itoa(fstat.st_nlink, 10, 0);
			if (ft_strlen(itoaed) > opt->nlink_min)
				opt->nlink_min = ft_strlen(itoaed);
			free(itoaed);
			itoaed = ft_itoa(fstat.st_size, 10, 0);
			if (ft_strlen(itoaed) > opt->size_min)
				opt->size_min = ft_strlen(itoaed);
			free(itoaed);
			if (tmp->dev)
				opt->expad = 1;
		}
		tmp = tmp->next;
	}
}
