/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:28:00 by oelbelam          #+#    #+#             */
/*   Updated: 2020/09/22 01:29:13 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lldi_check_arg(uint8_t c, t_op_arg *args)
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

int		lldi_arg2_execute(t_vm *vm, t_proc **prcs, int *index, short value)
{
	int temp;

	temp = (*prcs)->cur_pos + index[0];
	if ((*prcs)->args.arg2 == REG_CODE)
	{
		if (!check_reg(vm, i_mod(temp)))
			return (0);
		index[1] = value + index[1] + (*prcs)->r[vm->arena[i_mod(temp)] - 1];
		index[0]++;
		temp = (*prcs)->cur_pos + index[0];
	}
	else if ((*prcs)->args.arg2 == DIR_CODE)
	{
		value += (vm->arena[i_mod(temp)] << 8 | vm->arena[i_mod(temp + 1)]);
		index[1] = (value + index[1]) % MEM_SIZE;
		index[0] += 2;
		temp = (*prcs)->cur_pos + index[0];
	}
	if (check_reg(vm, i_mod(temp)))
	{
		(*prcs)->r[vm->arena[(temp) % MEM_SIZE] - 1] = convert_pos(vm,
			i_mod((*prcs)->cur_pos - 2 + index[1] + MEM_SIZE), 4);
		(*prcs)->carry = ((*prcs)->r[vm->arena[i_mod(temp)] - 1] == 0) ? 1 : 0;
	}
	return (index[0]);
}

int		lldi_execute(t_vm *vm, t_proc **prcs)
{
	int		crt_p;
	short	tmp_idx;
	int32_t	tmp_idx2;

	crt_p = 0;
	tmp_idx = 0;
	tmp_idx2 = 0;
	if ((*prcs)->args.arg1 == REG_CODE && (crt_p += 1))
	{
		if (!check_reg(vm, i_mod((*prcs)->cur_pos)))
			return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
		tmp_idx2 = (*prcs)->r[vm->arena[(*prcs)->cur_pos] - 1];
	}
	else if ((*prcs)->args.arg1 == DIR_CODE && (crt_p += 2))
		tmp_idx = convert_int_pos(vm, (*prcs)->cur_pos, 2);
	else if ((*prcs)->args.arg1 == IND_CODE && (crt_p += 2))
		tmp_idx2 = set_ind(vm, (int[]){(*prcs)->cur_pos, 0});
	if (!(crt_p = lldi_arg2_execute(vm, prcs, (int[]){crt_p, tmp_idx2}, tmp_idx)))
		return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
	return (crt_p + 1);
}

int 	lldi_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!lldi_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = i_mod((skip_bytes(vm->arena[(*prcs)->cur_pos], 2, 3) +
		(*prcs)->cur_pos));
	}
	else
	{
		(*prcs)->cur_pos = i_mod((*prcs)->cur_pos + 1);
		(*prcs)->cur_pos = i_mod((*prcs)->cur_pos + lldi_execute(vm, prcs));
	}
	return (1);
}