/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:59:26 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/17 16:18:03 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int	check_if_no_op(t_ass_env ass)
{
	t_token *crt;
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
