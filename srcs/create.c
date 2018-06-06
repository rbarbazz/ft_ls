/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:36:44 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/07 18:02:17 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_args	*split_path(t_args *new, char *name)
{
	int	i;
	int len;

	len = ft_strlen(name);
	i = len - 1;
	while (name[i] == '/')
		i--;
	while (name[i] != '/')
		i--;
	if (!(new->path = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	ft_strncpy(new->path, name, i);
	new->path[i + 1] = '\0';
	if (!(new->name = (char*)malloc(sizeof(char) * (len - i + 1))))
		return (NULL);
	ft_strncpy(new->name, name + i, len - i);
	new->name[len - i] = '\0';
	new->wpath = 1;
	return (new);
}

t_args			*first_list(char *name, char *path)
{
	t_args *new;

	if (!(new = (t_args*)malloc(sizeof(t_args))))
		return (NULL);
	if (ft_strchr(name, '/') && ft_strcmp("/", name) != 0 &&\
			name[ft_strlen(name) - 1] != '/')
		split_path(new, name);
	else
	{
		new->name = ft_strdup(name);
		new->path = ft_strdup(path);
		new->wpath = 0;
	}
	new->fulln = ft_strjoin(new->path, new->name);
	new->next = NULL;
	new->valid = 0;
	new->file = 0;
	new->dir = 0;
	new->dev = 0;
	return (new);
}

t_args			*new_list(char *name, char *path, char *currdir)
{
	t_args *new;

	if (!(new = (t_args*)malloc(sizeof(t_args))))
		return (NULL);
	new->name = ft_strdup(name);
	new->path = ft_strjoin(path, currdir);
	if (ft_strcmp("/", new->path))
		new->path = ft_strjoinchar(new->path, '/');
	new->fulln = ft_strjoin(new->path, new->name);
	new->next = NULL;
	new->wpath = 0;
	new->valid = 0;
	new->file = 0;
	new->dir = 0;
	new->dev = 0;
	return (new);
}

t_args			*new_node(char *name, t_args *next, char *path)
{
	t_args *new;

	if (!(new = (t_args*)malloc(sizeof(t_args))))
		return (NULL);
	if (ft_strchr(name, '/') && ft_strcmp("/", name) != 0 &&\
			name[ft_strlen(name) - 1] != '/')
		split_path(new, name);
	else
	{
		new->name = ft_strdup(name);
		new->path = ft_strdup(path);
		new->wpath = 0;
	}
	new->fulln = ft_strjoin(new->path, new->name);
	new->next = next;
	new->valid = 0;
	new->file = 0;
	new->dir = 0;
	new->dev = 0;
	return (new);
}
