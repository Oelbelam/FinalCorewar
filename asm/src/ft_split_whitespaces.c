/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 16:45:49 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/28 19:29:42 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

static int	word_count(char *str)
{
	int i;
	int wc;
	int is_word;

	i = 0;
	wc = 0;
	if (!(is_word = 0) && !str)
		return (0);
	while (str[i])
	{
		while (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' &&
			str[i] != SEPARATOR_CHAR && str[i] && (is_word = 1))
			i++;
		if (str[i] == '\t' || str[i] == ' ' || str[i] == '\n' ||
			str[i] == '\0' || str[i] == SEPARATOR_CHAR)
		{
			if (is_word == 1)
				wc++;
			is_word = 0;
			i++;
		}
	}
	return (wc);
}

static int	wlen(char *str, int i)
{
	int lc;

	lc = 0;
	while (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' &&
		str[i] != SEPARATOR_CHAR && str[i])
	{
		lc++;
		i++;
	}
	return (lc);
}

static int	skipws(char *str, int i)
{
	while ((str[i] == '\t' || str[i] == ' ' || str[i] == '\n' ||
		str[i] == SEPARATOR_CHAR) && str[i])
		i++;
	return (i);
}

char		**ft_split_whitespaces(char *str)
{
	char	**arr;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if ((arr = malloc(sizeof(char*) * (word_count(str) + 1))) == NULL)
		return (NULL);
	while (str[i])
	{
		i = skipws(str, i);
		if (str[i])
		{
			k = 0;
			if ((arr[j] = malloc(sizeof(char) * wlen(str, i) + 1)) == NULL)
				return (NULL);
			while (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' &&
			str[i] != SEPARATOR_CHAR && str[i])
				arr[j][k++] = str[i++];
			arr[j++][k] = '\0';
		}
	}
	arr[j] = NULL;
	return (arr);
}
