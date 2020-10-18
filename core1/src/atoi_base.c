/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 10:16:07 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/12 15:00:45 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

static int	ft_power(int nb, int power)
{
	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	return (nb * ft_power(nb, power - 1));
}

static int	cnvert_nbr(char c, int base)
{
	int		result;

	if (c >= '0' && c <= '9')
		result = c - 48;
	else if (c >= 'a' && c <= 'z')
		result = c - 97 + 10;
	else if (c >= 'A' && c <= 'Z')
		result = c - 65 + 10;
	else
		result = -1;
	if (result < base && result != -1)
		return (result);
	else
		return (-1);
}

static int	nbrlen(char *str, int base)
{
	int		length;

	length = 0;
	while (str[length])
	{
		if (cnvert_nbr(str[length], base) == -1)
			break ;
		length++;
	}
	return (length);
}

int			ft_atoi_base(char *nb, int base)
{
	int		result;
	int		length;

	if (base == 10)
		return (ft_atoi(nb));
	while (*nb == ' ' || *nb == '\t' || *nb == '\n'
			|| *nb == '\v' || *nb == '\r' || *nb == '\f')
		nb++;
	result = 0;
	length = nbrlen(nb, base) - 1;
	while (*nb && length >= 0 && cnvert_nbr(*nb, base) != -1)
	{
		result += cnvert_nbr(*nb, base) * ft_power(base, length);
		nb++;
		length--;
	}
	return (result);
}
