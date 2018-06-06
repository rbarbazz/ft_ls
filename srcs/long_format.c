/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:51:08 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/04 18:50:00 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_permissions_rest(struct stat *fstat)
{
	ft_printf((fstat->st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((fstat->st_mode & S_IWGRP) ? "w" : "-");
	ft_printf((!(fstat->st_mode & S_IXGRP) && fstat->st_mode & S_ISGID) ? "S" :\
			"");
	ft_printf((fstat->st_mode & S_IXGRP && fstat->st_mode & S_ISGID) ? "s" :\
			"");
	ft_printf((fstat->st_mode & S_IXGRP && !(fstat->st_mode & S_ISGID)) ? "x" :\
			"");
	ft_printf((!(fstat->st_mode & S_IXGRP) && !(fstat->st_mode & S_ISGID)) ?\
			"-" : "");
	ft_printf((fstat->st_mode & S_IROTH) ? "r" : "-");
	ft_printf((fstat->st_mode & S_IWOTH) ? "w" : "-");
	ft_printf((!(fstat->st_mode & S_IXOTH) && fstat->st_mode & S_ISVTX) ? "T" :\
			"");
	ft_printf((fstat->st_mode & S_IXOTH && fstat->st_mode & S_ISVTX) ? "t" :\
			"");
	ft_printf((fstat->st_mode & S_IXOTH && !(fstat->st_mode & S_ISVTX)) ? "x" :\
			"");
	ft_printf((!(fstat->st_mode & S_IXOTH) && !(fstat->st_mode & S_ISVTX)) ?\
			"-" : "");
}

static void	print_permissions(struct stat *fstat)
{
	ft_printf((S_ISDIR(fstat->st_mode)) ? "d" : "");
	ft_printf((S_ISLNK(fstat->st_mode)) ? "l" : "");
	ft_printf((S_ISCHR(fstat->st_mode)) ? "c" : "");
	ft_printf((S_ISSOCK(fstat->st_mode)) ? "s" : "");
	ft_printf((S_ISFIFO(fstat->st_mode)) ? "p" : "");
	ft_printf((!S_ISDIR(fstat->st_mode) && !S_ISLNK(fstat->st_mode) &&\
				!S_ISCHR(fstat->st_mode) && !S_ISSOCK(fstat->st_mode)) &&\
			!S_ISFIFO(fstat->st_mode) ? "-" : "");
	ft_printf((fstat->st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((fstat->st_mode & S_IWUSR) ? "w" : "-");
	ft_printf((!(fstat->st_mode & S_IXUSR) && fstat->st_mode & S_ISUID) ? "S" :\
			"");
	ft_printf((fstat->st_mode & S_IXUSR && fstat->st_mode & S_ISUID) ? "s" :\
			"");
	ft_printf((fstat->st_mode & S_IXUSR && !(fstat->st_mode & S_ISUID)) ? "x" :\
			"");
	ft_printf((!(fstat->st_mode & S_IXUSR) && !(fstat->st_mode & S_ISUID)) ?\
			"-" : "");
}

static void	print_uid(struct stat *fstat, t_opt *opt)
{
	if (getpwuid(fstat->st_uid))
		ft_printf(" %-*s", opt->uid_min, getpwuid(fstat->st_uid)->pw_name);
	else
		ft_printf(" %-*d", opt->uid_min, fstat->st_uid);
	if (getgrgid(fstat->st_gid))
		ft_printf("  %-*s", opt->gid_min, getgrgid(fstat->st_gid)->gr_name);
	else
		ft_printf("  %-*d", opt->gid_min, fstat->st_gid);
}

static void	print_time(struct stat *fstat)
{
	char	*str;
	int		i;

	i = 0;
	str = ctime(&fstat->st_mtimespec.tv_sec);
	while (i++ < 4)
		str++;
	if (time(NULL) - fstat->st_mtimespec.tv_sec > 15780000 ||\
			fstat->st_mtimespec.tv_sec - time(NULL) > 15780000)
		ft_printf(" %.6s  %.4s ", str, str + 16);
	else
		ft_printf(" %.12s ", str);
}

void		print_stats(t_args *tmp, t_opt *opt, struct stat fstat, char *buf)
{
	print_permissions(&fstat);
	print_permissions_rest(&fstat);
	ft_printf((listxattr(tmp->fulln, NULL, 0, XATTR_NOFOLLOW) > 0) ? "@" : " ");
	ft_printf(" %*d", opt->nlink_min, fstat.st_nlink);
	print_uid(&fstat, opt);
	if (S_ISCHR(fstat.st_mode))
		ft_printf("  %*u, %*u", opt->size_min, major(fstat.st_rdev),\
				opt->size_min, minor(fstat.st_rdev));
	else if (opt->expad)
		ft_printf("    %*u", (opt->size_min * 2), fstat.st_size);
	else
		ft_printf("  %*d", opt->size_min, fstat.st_size);
	print_time(&fstat);
	if (tmp->wpath)
		ft_printf("%s", tmp->fulln);
	else
		ft_printf("%s", tmp->name);
	if (readlink(tmp->fulln, buf, 2048) >= 0)
		ft_printf(" -> %s", buf);
	ft_printf("\n");
}
