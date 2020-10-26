/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 11:19:56 by jbouazao          #+#    #+#             */
/*   Updated: 2020/10/19 11:19:57 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		i_mod(int num)
{
	return (num % MEM_SIZE);
}

short	s_mod(short num)
{
	return (num % MEM_SIZE);
}

int		check_reg(t_vm *vm, int pos)
{
	if (vm->arena[pos] >= 1 && vm->arena[pos] <= 16)
		return (1);
	else
		return (0);
}

int32_t	convert_short_pos(t_vm *vm, short pos, int size)
{
	int32_t result;
	int		i;

	i = 0;
	result = 0;
	while (i < size)
	{
		pos = s_mod(pos);
		result |= vm->arena[pos] << (((size - 1) * 8) - i * 8);
		i++;
		pos++;
	}
	return (result);
}
