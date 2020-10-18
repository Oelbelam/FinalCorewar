/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:36:34 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/18 00:24:38 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int r_err(char r)
{
	return (((r != 'r') && (r != 'R')) ? 1 : 0);
}

int o_add(t_token **op, char ***sp)
{
	remove_cmnt(sp, 3);
	if (!(*sp)[0] || !(*sp)[1] || !(*sp)[2] || !(*sp)[3] ||
		(has_cmnt((*sp)[3]) && (*sp)[4] && (*sp)[4][0] != ';' && (*sp)[4][0] != '#') ||
		r_err((*sp)[1][0]) || r_err((*sp)[2][0]) || r_err((*sp)[3][0]) ||
		((*sp)[1] && (((*sp)[1][0] == 'r') || ((*sp)[1][0] == 'R')) &&
		 !is_num((*sp)[1] + 1)) ||
		((*sp)[2] && (((*sp)[2][0] == 'r') || ((*sp)[2][0] == 'R')) &&
		 !is_num((*sp)[2] + 1)) ||
		((*sp)[3] && (((*sp)[3][0] == 'r') || ((*sp)[3][0] == 'R')) &&
		 !is_num((*sp)[3] + 1)))
		return (0);
	(*op)->encode = calc_encode((*sp)[1], (*sp)[2], (*sp)[3]);
	(*op)->args[0] = ft_atoi((*sp)[1] + 1);
	(*op)->args[1] = ft_atoi((*sp)[2] + 1);
	(*op)->args[2] = ft_atoi((*sp)[3] + 1);
	if ((*op)->args[0] > REG_NUMBER || (*op)->args[0] <= 0 ||
		(*op)->args[1] > REG_NUMBER || (*op)->args[1] <= 0 ||
		(*op)->args[2] > REG_NUMBER || (*op)->args[2] <= 0)
		return (0);
	get_argc_types(op, (*sp));
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
	return (1);
}

void print_add_sub(t_token *token, int fd)
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
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[2], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
}
