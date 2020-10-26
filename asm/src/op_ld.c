/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:38:37 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/20 12:12:04 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

static int	valid_ld(char ***sp)
{
	if ((*sp)[0] && (*sp)[1] && (*sp)[2])
		remove_cmnt(sp, 2);
	if (!(*sp)[0] || !(*sp)[1] || !(*sp)[2] ||
		(has_cmnt((*sp)[2]) && (*sp)[3] && (*sp)[3][0] != ';' &&
		(*sp)[3][0] != '#') ||
		((*sp)[1] && (*sp)[1][0] != '%' && (*sp)[1][0] != ':' &&
		!is_num_neg((*sp)[1])) ||
		((*sp)[1] && (*sp)[1][0] == '%' && (*sp)[1][1] != ':' &&
		!is_num_neg((*sp)[1] + 1)) ||
		((*sp)[2] && (*sp)[2][0] != 'r' && (*sp)[2][0] != 'R') ||
		((*sp)[2] && ((*sp)[2][0] == 'r' || (*sp)[2][0] == 'R') &&
		!is_num((*sp)[2] + 1)))
		return (0);
	return (1);
}

int			o_ld(t_token **op, char ***sp)
{
	if (!valid_ld(sp))
		return (0);
	(*op)->encode = calc_encode((*sp)[1], (*sp)[2], NULL);
	if ((*sp)[1][0] == '%')
	{
		if ((*sp)[1][1] == ':' && ((*op)->args[0] = 2748))
			(*op)->labels[0] = ft_strdup((*sp)[1] + 2);
		else
			(*op)->args[0] = ft_atoi((*sp)[1] + 1);
	}
	else
	{
		if ((*sp)[1][0] == ':' && ((*op)->args[0] = 2748))
			(*op)->labels[0] = ft_strdup((*sp)[1] + 1);
		else
			(*op)->args[0] = ft_atoi((*sp)[1]);
	}
	(*op)->argc[0] = ((*sp)[1][0] == '%') ? T_DIR : T_IND;
	(*op)->argc[1] = T_REG;
	(*op)->argc[2] = 0;
	(*op)->args[1] = ft_atoi((*sp)[2] + 1);
	if ((*op)->args[1] > REG_NUMBER || (*op)->args[1] <= 0)
		return (0);
	(*op)->sz = ((*sp)[1][0] == '%') ? 7 : 5;
	return (1);
}

static void	ld_misc(char *s, t_token *token, int fd, int t)
{
	int		i;
	int		max;
	int		maxi;
	char	*a;

	maxi = (token->argc[t] == T_DIR) ? 8 : 4;
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
		a = (i == maxi && max % 2 != 0) ?
			ft_strsub(s, i, 1) : ft_strsub(s, i, 2);
		ft_putchar_fd(ft_atoi_base(a, 16), fd);
		ft_strdel(&a);
		i += (i == maxi && max % 2 != 0) ? 1 : 2;
	}
}

void		print_ld(t_token *token, int fd)
{
	char	*s;

	s = itoa_base(token->code, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->encode, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[0], 16);
	ld_misc(s, token, fd, 0);
	ft_strdel(&s);
	s = itoa_base(token->args[1], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
}
