/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:03:13 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/17 15:58:19 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		count_int(int n)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		is_num(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (0);
	return (1);
}

int		is_num_neg(char *s)
{
	int i;

	i = -1;
	if (s[0] == '-')
		i++;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (0);
	return (1);
}

int		calc_sz(char *argc, int dirsz)
{
	int sz;

	sz = 1;
	if (argc[0] == T_REG)
		sz += 1;
	else if (argc[0] == T_DIR)
		sz += dirsz;
	else if (argc[0] == T_IND)
		sz += 2;
	if (argc[1] == T_REG)
		sz += 1;
	else if (argc[1] == T_DIR)
		sz += dirsz;
	else if (argc[1] == T_IND)
		sz += 2;
	if (argc[2] == T_REG)
		sz += 1;
	else if (argc[2] == T_DIR)
		sz += dirsz;
	else if (argc[2] == T_IND)
		sz += 2;
	return (sz);
}

void	get_argc_types(t_token **op, char **sp)
{
	if (sp[1] && sp[1][0] == 'r')
		(*op)->argc[0] = T_REG;
	else if (sp[1] && sp[1][0] == '%')
		(*op)->argc[0] = T_DIR;
	else if (sp[1] && (is_num_neg(sp[1]) || sp[1][0] == ':'))
		(*op)->argc[0] = T_IND;
	else
		(*op)->argc[0] = 0;
	if (sp[2] && sp[2][0] == 'r')
		(*op)->argc[1] = T_REG;
	else if (sp[2] && sp[2][0] == '%')
		(*op)->argc[1] = T_DIR;
	else if (sp[2] && (is_num_neg(sp[2]) || sp[2][0] == ':'))
		(*op)->argc[1] = T_IND;
	else
		(*op)->argc[1] = 0;
	if (sp[3] && sp[3][0] == 'r')
		(*op)->argc[2] = T_REG;
	else if (sp[3] && sp[3][0] == '%')
		(*op)->argc[2] = T_DIR;
	else if (sp[3] && (is_num_neg(sp[3]) || sp[3][0] == ':'))
		(*op)->argc[2] = T_IND;
	else
		(*op)->argc[2] = 0;
}
