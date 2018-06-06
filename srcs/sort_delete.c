/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:36:52 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/03/04 18:53:13 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_args	*ins_by_name(t_args *head, char *name, char *path)
{
	t_args	*tmp;
	t_args	*new;

	tmp = head;
	if (ft_strcmp(tmp->name, name) > 0)
	{
		new = new_node(name, head, path);
		return (new);
	}
	while (tmp->next)
	{
		if (ft_strcmp(tmp->next->name, name) > 0)
			break ;
		tmp = tmp->next;
	}
	new = new_node(name, tmp->next, path);
	tmp->next = new;
	return (head);
}

t_args	*ins_by_lastmod(t_args *head, char *name, char *path)
{
	t_args		*tmp;
	t_args		*new;
	struct stat	fstat;
	struct stat	nextstat;
	char		*fulln;

	tmp = head;
	fulln = !path[0] ? ft_strdup(name) : ft_strjoin(tmp->path, name);
	lstat(tmp->fulln, &nextstat);
	lstat(fulln, &fstat);
	free(fulln);
	if (nextstat.st_mtimespec.tv_sec < fstat.st_mtimespec.tv_sec)
		return (new = new_node(name, head, path));
	fulln = !path[0] ? ft_strdup(name) : ft_strjoin(tmp->path, name);
	while (tmp->next)
	{
		lstat(tmp->next->fulln, &nextstat);
		if (nextstat.st_mtimespec.tv_sec < fstat.st_mtimespec.tv_sec)
			break ;
		tmp = tmp->next;
	}
	new = new_node(name, tmp->next, path);
	tmp->next = new;
	free(fulln);
	return (head);
}

t_args	*reverse(t_args *head)
{
	t_args	*prev;
	t_args	*current;
	t_args	*next;

	prev = NULL;
	current = head;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return (prev);
}

void	free_list(t_args *head)
{
	t_args	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->name);
		free(tmp->path);
		free(tmp->fulln);
		free(tmp);
	}
}
