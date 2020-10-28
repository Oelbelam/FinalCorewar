/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:25:37 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/28 18:35:40 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int			o_live(t_token **op, char ***sp)
{
	if (!(*sp)[0] || !(*sp)[1] ||
		((*sp)[2] && (*sp)[2][0] != ';' &&
		(*sp)[2][0] != '#') ||
		((*sp)[1] && ((*sp)[1][0] == '%' && (*sp)[1][1] != ':') &&
		!is_num_neg((*sp)[1] + 1)) ||
		((*sp)[1] && (*sp)[1][0] != '%'))
		return (0);
	(*op)->is_encode = 0;
	(*op)->argc[0] = T_DIR;
	(*op)->argc[1] = 0;
	(*op)->argc[2] = 0;
	if ((*sp)[1][1] == ':' && ((*op)->args[0] = 2748))
		(*op)->labels[0] = ft_strdup((*sp)[1] + 2);
	else
		(*op)->args[0] = ft_atoi((*sp)[1] + 1);
	(*op)->argc[0] = T_DIR;
	(*op)->sz = 1 + (*op)->tdir_sz;
	return (1);
}

static void	live_misc(char *s, t_token *token, int fd)
{
	int		i;
	int		max;
	char	*a;
	int		maxi;

	maxi = token->tdir_sz * 2;
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
		i += (i == maxi && max % 2 != 0) ? maxi + 1 : 2;
	}
}

void		print_live(t_token *token, int fd)
{
	char	*s;

	s = itoa_base(token->code, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[0], 16);
	live_misc(s, token, fd);
	ft_strdel(&s);
}
