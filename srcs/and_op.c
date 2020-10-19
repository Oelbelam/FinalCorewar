/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 08:56:21 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/18 16:40:23 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		and_check_arg(uint8_t c, t_op_arg *args)
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

int		and_arg2_execute(t_vm *vm, t_proc **prcs, int32_t value, int *index)
{
	if ((*prcs)->args.arg2 == REG_CODE)
		if (check_reg(vm, i_mod((*prcs)->cur_pos + *index)) == 1)
			value &= (*prcs)->r[vm->arena[(*prcs)->cur_pos + (*index)++] - 1];
		else
			return (0);
	else if ((*prcs)->args.arg2 == DIR_CODE)
	{
		value &= convert_pos(vm, (*prcs)->cur_pos + *index, 4);
		*index += 4;
	}
	else if ((*prcs)->args.arg2 == IND_CODE)
	{
		value &= set_ind(vm, (int[]){i_mod((*prcs)->cur_pos), *index});
		*index += 2;
	}
	if (check_reg(vm, i_mod((*prcs)->cur_pos + *index)) == 1)
	{
		(*prcs)->r[vm->arena[((*prcs)->cur_pos +
		*index) % MEM_SIZE] - 1] = value;
		(*prcs)->carry = (value == 0) ? 1 : 0;
	}
	return (1);
}

int		and_execute(t_vm *vm, t_proc **pr)
{
	int		crt_p;
	int32_t	tmp_r;
	short	tmp_idx;

	tmp_r = 0;
	crt_p = 0;
	if ((*pr)->args.arg1 == REG_CODE && (crt_p += 1))
		if (check_reg(vm, i_mod((*pr)->cur_pos)) == 1)
			tmp_r = (*pr)->r[vm->arena[(*pr)->cur_pos % MEM_SIZE] - 1];
		else
			return ((*pr)->args.s_arg1 +
			(*pr)->args.s_arg2 + (*pr)->args.s_arg3);
	else if ((*pr)->args.arg1 == DIR_CODE && (crt_p += 4))
		tmp_r = convert_pos(vm, (*pr)->cur_pos, 4);
	else if ((*pr)->args.arg1 == IND_CODE && (crt_p += 2))
		tmp_r = set_ind(vm, (int[]){(*pr)->cur_pos, 0});
	if (!and_arg2_execute(vm, pr, tmp_r, &crt_p))
		return ((*pr)->args.s_arg1 + (*pr)->args.s_arg2 + (*pr)->args.s_arg3);
	return (crt_p + 1);
}

int		and_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int		arg_ret;

	arg_ret = 0;
	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!and_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 3) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos +
		and_execute(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}
