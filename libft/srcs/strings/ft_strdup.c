/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:10:40 by rbarbazz          #+#    #+#             */
/*   Updated: 2017/11/10 15:31:48 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	dst = (char*)malloc(sizeof(char) * (len + 1));
	if (dst == 0)
		return (NULL);
	else
	{
		while (len--)
		{
			dst[i] = s1[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (dst);
}
