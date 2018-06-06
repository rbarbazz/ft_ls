/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 10:02:45 by rbarbazz          #+#    #+#             */
/*   Updated: 2017/12/14 11:35:01 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*to_backslash(char *str)
{
	int		index;
	char	*dst;

	index = 0;
	while (str[index] != '\n' && str[index] != '\0')
		index++;
	if (!(dst = (char*)malloc(sizeof(char) * (index + 1))))
		return (NULL);
	dst = ft_memcpy(dst, str, index);
	dst[index] = '\0';
	return (dst);
}

int		check_last(char *tmp, char **line, char **save)
{
	if (*tmp && ft_strchr(tmp, '\0'))
	{
		if (*save)
		{
			*line = ft_strjoin(*save, tmp);
			free(tmp);
			free(*save);
		}
		else
			*line = tmp;
		*save = NULL;
		return (1);
	}
	else if (*save && *save[0] != '\0' && ft_strchr(*save, '\0'))
	{
		*line = *save;
		*save = NULL;
		return (1);
	}
	return (0);
}

int		norm(char *tmp, char **line, char **save)
{
	char	*swag;

	swag = to_backslash(tmp);
	if (!*save)
		*line = swag;
	else
	{
		*line = ft_strjoin(*save, swag);
		free(swag);
		free(*save);
	}
	*save = ft_strdup(ft_strchr(tmp, '\n') + 1);
	free(tmp);
	return (1);
}

int		read_buffer(const int fd, char **line, char **save)
{
	char	*swag;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	tmp = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		swag = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = swag;
		if (ft_strchr(buf, '\n'))
			return (norm(tmp, line, save));
	}
	if (ret < 0)
		return (-1);
	return (check_last(tmp, line, save));
}

int		get_next_line(const int fd, char **line)
{
	static char	*save = NULL;
	char		*swag;

	if (fd < 0)
		return (-1);
	if (save)
	{
		if (ft_strchr(save, '\n'))
		{
			swag = save;
			*line = to_backslash(save);
			save = ft_strdup(ft_strchr(save, '\n') + 1);
			free(swag);
			return (1);
		}
	}
	return (read_buffer(fd, line, &save));
}
