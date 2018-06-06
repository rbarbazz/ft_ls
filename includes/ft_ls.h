/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:56:56 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/07 14:39:20 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdio.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

typedef struct	s_opt
{
	int				bigr;
	int				r;
	int				l;
	int				t;
	int				a;
	int				wargs;
	int				firstr;
	int				wfile;
	int				ret;
	int				othx;
	unsigned int	uid_min;
	unsigned int	gid_min;
	unsigned int	nlink_min;
	unsigned int	size_min;
	unsigned int	expad;
}				t_opt;

typedef struct	s_args
{
	char			*name;
	char			*path;
	char			*fulln;
	int				wpath;
	int				valid;
	int				file;
	int				dev;
	int				dir;
	struct s_args	*next;
}				t_args;

void			parsing_opt(t_opt *opt, char **argv, int argc, int *i);
t_args			*parsing_args(t_args *head, t_opt *opt, char **argv, int *i);
t_args			*get_curr_dir(t_args *head, t_opt *opt, char *toopen);
void			check_args(t_args *head, t_opt *opt);
void			print_no_args(t_args *head, t_opt *opt);
void			print(t_args *head, t_opt *opt);
void			print_long(t_args *head, t_opt *opt);

void			print_no(t_args *head, t_opt *opt);

void			print_no_long(t_args *head, t_opt *opt);
void			check_min_width(t_args *head, t_opt *opt);
void			print_stats(t_args *tmp, t_opt *opt, struct stat fstat,\
		char *buf);
void			init_opt(t_opt *opt);
void			print_total_blocks(t_args *head, t_opt *opt);
int				count_args(t_args *head, t_opt *opt);

void			print_recursive(t_args *head, t_opt *opt);

t_args			*first_list(char *name, char *path);
t_args			*new_node(char *name, t_args *next, char *path);
t_args			*new_list(char *name, char *path, char *currdir);
void			free_list(t_args *head);
t_args			*ins_by_name(t_args *head, char *name, char *path);
t_args			*ins_by_lastmod(t_args *head, char *name, char *currdir);
t_args			*reverse(t_args *head);

#endif
