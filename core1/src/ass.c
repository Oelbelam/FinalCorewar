/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ass.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:34:28 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/18 00:56:20 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int parser(t_lines **line, t_ass_env *ass)
{
	int l;
	char *tmp;

	if (!ft_strncmp((*line)->line, NAME_CMD_STRING, 5))
		return (get_champ_name((*line)->line + 5, ass));
	else if (!ft_strncmp((*line)->line, COMMENT_CMD_STRING, 8))
		return (get_champ_cmnt((*line)->line + 8, ass));
	else if (is_op((*line)->line))
	{
		if ((l = is_label((*line)->line)) > 0)
			if (!get_label((*line)->line, ass, l))
				return (0);
		return (get_op((*line)->line, ass));
	}
	else if ((l = is_label((*line)->line)) > 0)
	{
		tmp = (*line)->line + l + 1 + skip_ws((*line)->line + l + 1);
		if (tmp && ft_strcmp(tmp, "") && !is_op(tmp))
			return (0);
		return (get_label((*line)->line, ass, l));
	}
	return (0);
}

int check_name_cmnt(t_ass_env *ass)
{
	t_lines *tline;
	int found;

	tline = ass->lines;
	found = 0;
	while (tline)
	{
		if (tline->line[0] == '#' || tline->line[0] == ';' || !tline->line[0])
		{
			tline = tline->next;
			continue;
		}
		if (!ft_strncmp(tline->line, NAME_CMD_STRING, 5))
			found++;
		else if (!ft_strncmp(tline->line, COMMENT_CMD_STRING, 8))
			found++;
		if (is_label(tline->line) || is_op(tline->line))
			break;
		tline = tline->next;
	}
	return (found);
}

int assembler(char *fn, t_ass_env *ass)
{
	t_lines *tline;
	char *tchar;

	if (!get_lines(fn, ass))
		return (0);
	if (check_name_cmnt(ass) != 2)
		return (0);
	tline = ass->lines;
	while (tline && (tchar = tline->line))
	{
		tchar += skip_ws(tchar);
		if (tchar[0] == '#' || tchar[0] == ';' || !tchar[0])
		{
			tline = tline->next;
			continue;
		}
		if (!parser(&tline, ass))
			return (0);
		tline = tline->next;
	}
	return (1);
}
