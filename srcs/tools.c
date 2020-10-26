/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 11:14:02 by jbouazao          #+#    #+#             */
/*   Updated: 2020/10/19 11:14:04 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short	convert_int_pos(t_vm *vm, int pos, int size)
{
	short	result;
	int		i;

	i = 0;
	result = 0;
	while (i < size)
	{
		pos = i_mod(pos);
		result |= vm->arena[pos] << (((size - 1) * 8) - i * 8);
		i++;
		pos++;
	}
	return (result);
}

int32_t	convert_pos(t_vm *vm, int pos, int size)
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

int32_t	set_ind(t_vm *vm, int *pos)
{
	short	index;
	int32_t	result;

	result = 0;
	index = convert_int_pos(vm, pos[0] + pos[1], 2);
	index = pos[0] - 2 + ((index % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
	result = convert_short_pos(vm, index, 4);
	return (result);
}

void	wr_arena(t_vm *vm, int32_t value, int *pos)
{
	short	index;

	index = convert_int_pos(vm, (pos[0] + pos[1]), 2);
	index = s_mod(((index % IDX_MOD) + MEM_SIZE));
	vm->arena[i_mod(pos[0] - 2 + (index))] = (value & 4278190080U) >> 24;
	vm->arena[i_mod(pos[0] - 2 + (index) + 1)] = (value & 16711680) >> 16;
	vm->arena[i_mod(pos[0] - 2 + (index) + 2)] = (value & 65280) >> 8;
	vm->arena[i_mod(pos[0] - 2 + (index) + 3)] = value & 255;
	vm->ar_clr[i_mod(pos[0] - 2 + (index))] = pos[2];
	vm->ar_clr[i_mod(pos[0] - 2 + (index) + 1)] = pos[2];
	vm->ar_clr[i_mod(pos[0] - 2 + (index) + 2)] = pos[2];
	vm->ar_clr[i_mod(pos[0] - 2 + (index) + 3)] = pos[2];
}

void	wri_arena(t_vm *vm, t_proc *prcs, int32_t index, int32_t pos)
{
	int32_t value;

	value = prcs->r[vm->arena[pos] - 1];
	vm->arena[index] = (value & 4278190080U) >> 24;
	vm->arena[i_mod(index + 1)] = (value & 16711680) >> 16;
	vm->arena[i_mod(index + 2)] = (value & 65280) >> 8;
	vm->arena[i_mod(index + 3)] = (value & 255);
	vm->ar_clr[index] = prcs->proc_clr;
	vm->ar_clr[i_mod(index + 1)] = prcs->proc_clr;
	vm->ar_clr[i_mod(index + 2)] = prcs->proc_clr;
	vm->ar_clr[i_mod(index + 3)] = prcs->proc_clr;
}
