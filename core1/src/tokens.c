/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 10:15:09 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/12 15:32:41 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

t_token		*new_token(char *line, int type)
{
	t_token *new;

	if (!line || !(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	if (type == 1 || type == 2 || type == 3)
	{
		new->type = type;
		new->name = line;
		new->next = NULL;
	}
	return (new);
}

int			add_token(t_ass_env *ass, t_token *new)
{
	t_token *ttoken;

	if (!new)
		return (0);
	if (!ass->tokens)
	{
		ass->tokens = new;
		return (1);
	}
	ttoken = ass->tokens;
	while (ttoken->next)
		ttoken = ttoken->next;
	ttoken->next = new;
	return (1);
}
