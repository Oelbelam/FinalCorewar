/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:33:46 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/12 15:36:36 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		calc_exec_code_sz(t_token *token)
{
	t_token	*ttoken;
	int		i;

	i = 0;
	ttoken = token;
	while (ttoken)
	{
		if (ttoken->type == 4)
			i += ttoken->sz;
		ttoken = ttoken->next;
	}
	return (i);
}

int		print_exec_code_size(int fd, int sz)
{
	int		i;
	int		max;
	char	*a;
	char	*s;
	int		maxi;

	maxi = 8;
	s = itoa_base(sz, 16);
	max = ft_strlen(s);
	i = (max % 2 != 0) ? 1 : 0;
	while (i < maxi - max)
	{
		ft_putchar_fd(00, fd);
		i += 2;
	}
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		a = (i == 0 && max % 2 != 0) ? ft_strsub(s, i, 1) : ft_strsub(s, i, 2);
		ft_putchar_fd(ft_atoi_base(a, 16), fd);
		ft_strdel(&a);
		i += (i == 0 && max % 2 != 0) ? 1 : 2;
	}
	ft_strdel(&s);
	return (1);
}

int		look_forewards(t_token *token, char *label, int i)
{
	t_token *ttoken;
	int		byte;

	byte = 0;
	ttoken = token;
	while (ttoken)
	{
		if (ttoken && ttoken->type == 4)
		{
			byte += ttoken->sz;
		}
		if (ttoken && ttoken->type == 3 && !ft_strcmp(ttoken->name, label))
		{
			token->args[i] = byte;
			return (1);
		}
		ttoken = ttoken->next;
	}
	return (0);
}

int		look_backwards(t_token *token, char *label, int i)
{
	t_token *ttoken;
	int		byte;

	byte = 0;
	ttoken = token->prev;
	while (ttoken)
	{
		if (ttoken && ttoken->type == 4)
		{
			byte += ttoken->sz;
		}
		if (ttoken && ttoken->type == 3 && !ft_strcmp(ttoken->name, label))
		{
			token->args[i] = -1 * byte;
			return (1);
		}
		ttoken = ttoken->prev;
	}
	return (0);
}

int		get_labels(t_token **token)
{
	t_token	*ttoken;
	int		i;

	ttoken = *token;
	while (ttoken)
	{
		if (ttoken->type == 4)
		{
			i = -1;
			while (++i < 3)
				if (ttoken->labels[i])
				{
					if (!look_backwards(ttoken, ttoken->labels[i], i) &&
						!look_forewards(ttoken, ttoken->labels[i], i))
					{
						ft_printf("ERROR : Label [%s] Not Found",
							ttoken->labels[i]);
						return (0);
					}
				}
		}
		ttoken = ttoken->next;
	}
	return (1);
}
