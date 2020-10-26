/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:59:26 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/19 11:17:52 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		check_if_no_op(t_ass_env ass)
{
	t_token	*crt;
	int		opf;
	int		lablef;

	crt = ass.tokens;
	opf = 0;
	lablef = 0;
	while (crt)
	{
		if (crt->type == 4)
			opf = 1;
		if (crt->type == 3)
			lablef = 1;
		crt = crt->next;
	}
	if (!opf && !lablef)
		return (0);
	return (1);
}

void	init_env(t_ass_env *ass)
{
	ass->champ.prog_name = NULL;
	ass->champ.prog_cmnt = NULL;
	ass->tokens = NULL;
	ass->op = NULL;
	ass->sz = 0;
}

int		get_cmnt_start(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ';' || s[i] == '#')
			return (i);
		i++;
	}
	return (i);
}

int		is_cmnt(char *s)
{
	if (s[0] == ';' || s[0] == '#')
		return (1);
	return (0);
}

void	remove_cmnt(char ***sp, int id)
{
	char	*tmp;

	tmp = ft_strsub((*sp)[id], 0, get_cmnt_start((*sp)[id]));
	free((*sp)[id]);
	(*sp)[id] = tmp;
}
