/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:09:25 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/27 18:42:32 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		o_aff(t_token **op, char ***sp)
{
	if ((*sp)[0] && (*sp)[1])
		remove_cmnt(sp, 1);
	if (!(*sp)[0] || !(*sp)[1] ||
		((*sp)[2] && (*sp)[2][0] != ';' &&
		(*sp)[2][0] != '#') ||
		((*sp)[1][0] != 'r' && (*sp)[1][0] != 'R') ||
		((*sp)[1] && ((*sp)[1][0] == 'r' || (*sp)[1][0] == 'R') &&
		!is_num((*sp)[1] + 1)))
		return (0);
	(*op)->encode = calc_encode((*sp)[1], NULL, NULL);
	(*op)->args[0] = ft_atoi((*sp)[1] + 1);
	if ((*op)->args[0] > REG_NUMBER || (*op)->args[0] <= 0)
		return (0);
	(*op)->argc[0] = T_REG;
	(*op)->sz = 3;
	return (1);
}

void	print_aff(t_token *token, int fd)
{
	char	*s;

	s = itoa_base(token->code, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->encode, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[0], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
}
