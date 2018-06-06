/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:24:49 by rbarbazz          #+#    #+#             */
/*   Updated: 2017/11/15 10:59:38 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_char(char const *s, char c, int index)
{
	if (s[index] == c)
		return (1);
	if (s[index] == '\0')
		return (2);
	return (0);
}

static int			count_words(char const *s, char c)
{
	int count;
	int index;

	index = 0;
	count = 0;
	while (s[index])
	{
		while (is_char(s, c, index) == 1)
			index++;
		if (is_char(s, c, index) == 0)
		{
			while (is_char(s, c, index) == 0)
				index++;
			count++;
		}
	}
	return (count);
}

static char			**copy(char **tab, char const *s, char c)
{
	int index;
	int wn;
	int cn;

	wn = 0;
	index = 0;
	while (wn < count_words(s, c))
	{
		cn = 0;
		tab[wn] = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
		while (is_char(s, c, index) == 1)
			index++;
		while (is_char(s, c, index) == 0)
		{
			tab[wn][cn] = s[index];
			index++;
			cn++;
		}
		tab[wn][cn] = '\0';
		wn++;
	}
	tab[wn] = NULL;
	return (tab);
}

char				**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * (count_words(s, c) + 1))))
		return (NULL);
	copy(tab, s, c);
	return (tab);
}
