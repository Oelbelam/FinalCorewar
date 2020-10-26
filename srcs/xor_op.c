/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:24:15 by oelbelam          #+#    #+#             */
/*   Updated: 2020/09/22 16:58:41 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		xor_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if (((c >> 6) & 0b11) == REG_CODE)
		args->arg1 = 1 + 0 * args->s_arg1++;
	else if (((c >> 6) & 0b11) == DIR_CODE && (args->s_arg1 += 4))
		args->arg1 = 2;
	else if (((c >> 6) & 0b11) == IND_CODE && (args->s_arg1 += 2))
		args->arg1 = 3;
	else
		error = 0;
	if (((c >> 4) & 0b0011) == REG_CODE)
		args->arg2 = 1 + 0 * args->s_arg2++;
	else if (((c >> 4) & 0b0011) == DIR_CODE && (args->s_arg2 += 4))
		args->arg2 = 2;
	else if (((c >> 4) & 0b0011) == IND_CODE && (args->s_arg2 += 2))
		args->arg2 = 3;
	else
		error = 0;
	if (((c >> 2) & 0b000011) == REG_CODE)
		args->arg3 = 1 + 0 * args->s_arg3++;
	else
		error = 0;
	return (error);
}

int		xor_arg2_execute(t_vm *vm, t_proc **prcs, int32_t value, int pos)
{
	if ((*prcs)->args.arg2 == REG_CODE)
	{
		if (!check_reg(vm, i_mod((*prcs)->cur_pos + pos)))
			return (0);
		value ^= (*prcs)->
		r[vm->arena[((*prcs)->cur_pos + pos++) % MEM_SIZE] - 1];
	}
	else if ((*prcs)->args.arg2 == DIR_CODE)
	{
		value ^= convert_pos(vm, i_mod((*prcs)->cur_pos + pos), 4);
		pos += 4;
	}
	else if ((*prcs)->args.arg2 == IND_CODE)
	{
		value ^= set_ind(vm, (int[]) {i_mod((*prcs)->cur_pos), pos});
		pos += 2;
	}
	if (check_reg(vm, i_mod((*prcs)->cur_pos + pos)))
	{
		(*prcs)->r[vm->arena[i_mod((*prcs)->cur_pos + pos)] - 1] = value;
		(*prcs)->carry = (value == 0) ? 1 : 0;
	}
	return (pos);
}

int		xor_execute(t_vm *vm, t_proc **prcs)
{
	int		crt_p;
	int32_t	tmp_r;
	int16_t	tmp_idx;

	tmp_r = 0;
	crt_p = 0;
	if ((*prcs)->args.arg1 == REG_CODE && (crt_p += 1))
	{
		if (!check_reg(vm, i_mod((*prcs)->cur_pos)))
			return ((*prcs)->args.s_arg1 +
			(*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
			tmp_r = (*prcs)->r[vm->arena[(*prcs)->cur_pos] - 1];
	}
	else if ((*prcs)->args.arg1 == DIR_CODE && (crt_p += 4))
		tmp_r = convert_pos(vm, i_mod((*prcs)->cur_pos), 4);
	else if ((*prcs)->args.arg1 == IND_CODE && (crt_p += 2))
		tmp_r = set_ind(vm, (int[]){(*prcs)->cur_pos, 0});
	if (!(crt_p = xor_arg2_execute(vm, prcs, tmp_r, crt_p)))
		return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 +
		(*prcs)->args.s_arg3);
		return (crt_p + 1);
}

int		xor_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int		arg_ret;

	arg_ret = 0;
	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!xor_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 3) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos +
		xor_execute(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}
