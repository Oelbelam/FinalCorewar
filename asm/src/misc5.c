/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:30:24 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/28 19:19:25 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		has_comment(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';' || line[i] == '#')
			return (i);
		i++;
	}
	return (0);
}

// int has_comma(char *line)
// {
// 	int i;

// 	i = 0;
// 	while(line[i])
// 		i++;
// 	if (line[i - 1] == ',')
// 	{

// 	}
// }