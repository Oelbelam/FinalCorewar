/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:25:46 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/20 12:27:44 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

void	remove_cmnt2(char **line)
{
	char	*tmp;

	if (has_cmnt((*line)))
	{
		tmp = ft_strsub((*line), 0, get_cmnt_start((*line)));
		(*line) = tmp;
	}
}
