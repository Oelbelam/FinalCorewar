/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:52:15 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/12 15:01:32 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

static void	first_arg(char **bytes, char *arg, int i)
{
	if (!arg)
	{
		(*bytes)[i] = '0';
		(*bytes)[i + 1] = '0';
		return ;
	}
	if (arg[0] == 'r')
	{
		(*bytes)[i] = '0';
		(*bytes)[i + 1] = '1';
	}
	else if (arg[0] == '%')
	{
		(*bytes)[i] = '1';
		(*bytes)[i + 1] = '0';
	}
	else if (is_num_neg(arg) || arg[0] == ':')
	{
		(*bytes)[i] = '1';
		(*bytes)[i + 1] = '1';
	}
}

int			calc_encode(char *arg1, char *arg2, char *arg3)
{
	char	encode;
	char	*bytes;

	encode = 0;
	if (!(bytes = ft_strnew(8)))
		return (0);
	first_arg(&bytes, arg1, 0);
	first_arg(&bytes, arg2, 2);
	first_arg(&bytes, arg3, 4);
	first_arg(&bytes, NULL, 6);
	encode = ft_atoi_base(bytes, 2);
	ft_strdel(&bytes);
	return (encode);
}
