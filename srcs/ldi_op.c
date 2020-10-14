/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:25:52 by oelbelam          #+#    #+#             */
/*   Updated: 2020/09/20 15:25:43 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ldi_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if (((c >> 6) & 0b11) == DIR_CODE && (args->s_arg1 += 2))
		args->arg1 = 2;
	else if ((((c >> 6) & 0b11) == IND_CODE) && (args->s_arg1 += 2))
		args->arg1 = 3;
	else if ((((c >> 6) & 0b11) == REG_CODE) && (args->s_arg1 += 1))
		args->arg1 = 1;
	else
		error = 0;
	if ((((c >> 4) & 0b0011) == REG_CODE))
		args->arg2 = 1 + 0 * args->s_arg2++;
	else if ((((c >> 4) & 0b0011) == DIR_CODE) && (args->s_arg2 += 2))
		args->arg2 = 2;
	else
		error = 0;
	if ((((c >> 2) & 0b000011) == REG_CODE))
		args->arg3 = 1 + 0 * args->s_arg3++;
	else
		error = 0;
	return (error);
}

int idx_mod(int num)
{
	return ((num % IDX_MOD) + MEM_SIZE);
}

int		ldi_arg2_execut(t_vm *vm, t_proc **prcs, int *index, short value)
{
	if ((*prcs)->args.arg2 == REG_CODE)
	{
		if (check_reg(vm, (*prcs)->cur_pos + index[0]))
		{
			index[1] = value + index[1] 
			+ (*prcs)->r[vm->arena[i_mod((*prcs)->cur_pos + index[0])] - 1];
		}
		else
			return (0);
		index[0] += 1;
	}
	else if ((*prcs)->args.arg2 == DIR_CODE)
	{
		value += convert_int_pos(vm, (*prcs)->cur_pos + index[0], 2);
		index[1] = value + index[1];
		index[0] += 2;
	}
	if (check_reg(vm, (*prcs)->cur_pos + index[0]))
	{
		(*prcs)->r[vm->arena[i_mod((*prcs)->cur_pos + index[0])] - 1] = convert_pos(vm, 
		i_mod((*prcs)->cur_pos - 2 + idx_mod(index[1])), 4);
	}
	return (index[0]);
}


int		ldi_execute(t_vm *vm, t_proc **prcs)
{
	int		crt_p;
	short	tmp_idx;
	int32_t	tmp_idx2;

	crt_p = 0;
	tmp_idx = 0;
	tmp_idx2 = 0;
	if ((*prcs)->args.arg1 == REG_CODE && (crt_p += 1))
	{
		if (check_reg(vm, (*prcs)->cur_pos) == 1)
			tmp_idx2 = (*prcs)->r[vm->arena[(*prcs)->cur_pos] - 1];
		else
			return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
	}
	else if ((*prcs)->args.arg1 == DIR_CODE && (crt_p += 2))
		tmp_idx = convert_int_pos(vm, (*prcs)->cur_pos, 2);
	else if ((*prcs)->args.arg1 == IND_CODE && (crt_p += 2))
		tmp_idx2 = set_ind(vm, (int[]){(*prcs)->cur_pos, 0});
	if ((crt_p = ldi_arg2_execut(vm, prcs, (int[]){crt_p, tmp_idx2}, tmp_idx)) == 0)
		return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
	return (crt_p + 1);
}

int 	ldi_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!ldi_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 2, 3) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos + ldi_execute(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}
