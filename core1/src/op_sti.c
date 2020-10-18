/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:43:15 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/18 00:25:57 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int has_cmnt(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ';' || s[i] == '#')
			return (1);
		i++;
	}
	return (0);
}

static int check_sti_err(char ***sp)
{
	remove_cmnt(sp, 3);
	if (!(*sp)[0] || !(*sp)[1] || !(*sp)[2] || !(*sp)[3] ||
		(has_cmnt((*sp)[3]) && (*sp)[4] && (*sp)[4][0] != ';' &&
		 (*sp)[4][0] != '#') ||
		((*sp)[1] && (*sp)[1][0] != 'R' &&
		 (*sp)[1][0] != 'r') ||
		((*sp)[1] && ((*sp)[1][0] == 'r' || (*sp)[1][0] == 'R') && !is_num((*sp)[1] + 1)) ||
		((*sp)[2] && (*sp)[2][0] != 'R' && (*sp)[2][0] != 'r' &&
		 (*sp)[2][0] != '%' && (*sp)[2][0] != ':' && !is_num_neg((*sp)[2])) ||
		((*sp)[2] && ((*sp)[2][0] == 'r' || (*sp)[2][0] == 'R') &&
		 !is_num((*sp)[2] + 1)) ||
		((*sp)[2] && ((*sp)[2][0] == '%' && (*sp)[2][1] != ':') && !is_num_neg((*sp)[2] + 1)) ||
		((*sp)[3] && (*sp)[3][0] != 'R' && (*sp)[3][0] != 'r' &&
		 (*sp)[3][0] != '%') ||
		((*sp)[3] && ((*sp)[3][0] == 'r' || (*sp)[3][0] == 'R') && !is_num((*sp)[3] + 1)) ||
		((*sp)[3] && ((*sp)[3][0] == '%' && (*sp)[3][1] != ':') &&
		 !is_num_neg((*sp)[3] + 1)))
		return (0);
	return (1);
}

int o_sti(t_token **op, char ***sp)
{
	if (!check_sti_err(sp))
		return (0);
	(*op)->encode = calc_encode((*sp)[1], (*sp)[2], (*sp)[3]);
	get_argc_types(op, (*sp));
	fill_args(op, (*sp), 0);
	fill_args(op, (*sp), 1);
	fill_args(op, (*sp), 2);
	get_argc_types(op, (*sp));
	if (((*op)->argc[0] == T_REG &&
		 ((*op)->args[0] > REG_NUMBER || (*op)->args[0] <= 0)) ||
		((*op)->argc[1] == T_REG &&
		 ((*op)->args[1] > REG_NUMBER || (*op)->args[1] <= 0)) ||
		((*op)->argc[2] == T_REG &&
		 ((*op)->args[2] > REG_NUMBER || (*op)->args[2] <= 0)))
		return (0);
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
	return (1);
}

static void sti_misc(char *s, t_token *token, int fd, int t)
{
	int i;
	int max;
	char *a;
	int maxi;

	maxi = 2;
	maxi = (token->argc[t] == T_DIR || token->argc[t] == T_IND) ? 4 : maxi;
	maxi = (token->argc[t] == T_DIR && token->tdir_sz == 4) ? 8 : maxi;
	max = ft_strlen(s);
	i = (max % 2 != 0) ? 1 : 0;
	while (i < maxi - max)
	{
		ft_putchar_fd(00, fd);
		i += 2;
	}
	maxi = (max > maxi) ? max - maxi : 0;
	i = maxi;
	while (i < (int)ft_strlen(s))
	{
		a = (i == maxi && max % 2 != 0) ? ft_strsub(s, i, 1) : ft_strsub(s, i, 2);
		ft_putchar_fd(ft_atoi_base(a, 16), fd);
		ft_strdel(&a);
		i += (i == maxi && max % 2 != 0) ? 1 : 2;
	}
}

void print_sti(t_token *token, int fd)
{
	char *s;

	s = itoa_base(token->code, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->encode, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[0], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[1], 16);
	sti_misc(s, token, fd, 1);
	ft_strdel(&s);
	s = itoa_base(token->args[2], 16);
	sti_misc(s, token, fd, 2);
	ft_strdel(&s);
}
