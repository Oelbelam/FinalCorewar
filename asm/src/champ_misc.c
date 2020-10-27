/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:51:41 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/27 19:48:58 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		chk_nm(char *line)
{
	unsigned long i;

	i = 0;
	while (line[i] && i < ft_strlen(line) - 1)
	{
		if (line[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

int		get_champ_name(char *line, t_ass_env *ass)
{
	char	*tmp;

	remove_cmnt2(&line);
	line = ft_strtrim(line);
	tmp = line;
	if (!line || line[0] != '"' || line[ft_strlen(line) - 1] != '"' ||
		!chk_nm(line + 1))
	{
		ft_strdel(&tmp);
		return (0);
	}
	line++;
	if (ft_strlen(line) - 1 > PROG_NAME_LENGTH)
	{
		ft_strdel(&tmp);
		return (0);
	}
	ass->champ.prog_name = ft_strsub(line, 0, ft_strlen(line) - 1);
	if (!add_token(ass, new_token(ass->champ.prog_name, 1)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int		get_champ_cmnt(char *line, t_ass_env *ass)
{
	char	*tmp;

	remove_cmnt2(&line);
	line = ft_strtrim(line);
	tmp = line;
	if (!line || line[0] != '"' || line[ft_strlen(line) - 1] != '"' ||
		!chk_nm(line + 1))
	{
		ft_strdel(&tmp);
		return (0);
	}
	line++;
	if (ft_strlen(line) - 1 > COMMENT_LENGTH)
	{
		ft_strdel(&tmp);
		return (0);
	}
	ass->champ.prog_cmnt = ft_strsub(line, 0, ft_strlen(line) - 1);
	if (!add_token(ass, new_token(ass->champ.prog_cmnt, 2)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int		is_label_char(char c)
{
	int i;

	i = -1;
	while (LABEL_CHARS[++i])
		if (LABEL_CHARS[i] == c)
			return (1);
	return (0);
}

int		get_label(char *line, t_ass_env *ass, int l)
{
	if (!add_token(ass, new_token(ft_strsub(line, 0, l), 3)))
		return (0);
	return (1);
}
