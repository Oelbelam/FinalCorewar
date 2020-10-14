/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:26:20 by oelbelam          #+#    #+#             */
/*   Updated: 2020/09/22 19:26:21 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		sti_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if ((((c >> 6) & 0b11) == REG_CODE) && (args->s_arg1 += 1))
		args->arg1 = 1;
	else
		error = 0;
	if ((((c >> 4) & 0b0011) == REG_CODE))
		args->arg2 = 1 + 0 * args->s_arg2++;
	else if ((((c >> 4) & 0b0011) == DIR_CODE) && (args->s_arg2 += 2))
		args->arg2 = 2;
	else if ((((c >> 4) & 0b0011) == IND_CODE) && (args->s_arg2 += 2))
		args->arg2 = 3;
	else
		error = 0;
	if ((((c >> 2) & 0b000011) == REG_CODE))
		args->arg3 = 1 + 0 * args->s_arg3++;
	else if ((((c >> 2) & 0b000011) == DIR_CODE) && (args->s_arg3 += 2))
		args->arg3 = 2;
	else
		error = 0;
	return (error);
}

int		sti_arg3_execute(t_vm *vm, t_proc **prcs, short value, int *index)
{
	if ((*prcs)->args.arg3 == REG_CODE)
	{
		if (!check_reg(vm, i_mod((*prcs)->cur_pos + 1 + index[0])))
			return (0);
		index[1] = i_mod(value + index[1]
			+ (*prcs)->r[vm->arena[i_mod((*prcs)->cur_pos + 1 + index[0])] - 1]);
		index[1] = i_mod(((*prcs)->cur_pos - 2) + ((index[1] % IDX_MOD)) + MEM_SIZE);
		index[0] += 1;
	}
	else if ((*prcs)->args.arg3 == DIR_CODE)
	{
		value = value + convert_int_pos(vm, (*prcs)->cur_pos + 1 + index[0], 2);
		index[1] = value + index[1];
		index[1] = i_mod(((*prcs)->cur_pos - 2) + ((index[1] % IDX_MOD)) + MEM_SIZE);
		index[0] += 2;
	}
	if (check_reg(vm, i_mod((*prcs)->cur_pos)))
		set_sti_arena(vm, *prcs, index[1], (*prcs)->cur_pos);
	return (index[0]);
}

int		sti_execute(t_vm *vm, t_proc **prcs)
{
	int		crt_p;
	int16_t tmp_idx;
	int32_t	tmp_idx2;

	crt_p = 0;
	tmp_idx = 0;
	tmp_idx2 = 0;
	if ((*prcs)->args.arg2 == REG_CODE && (crt_p += 1))
	{
		if (!check_reg(vm, i_mod((*prcs)->cur_pos + 1)))
			return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
		tmp_idx2 = (*prcs)->r[vm->arena[i_mod((*prcs)->cur_pos + 1)] - 1];
	}
	else if ((*prcs)->args.arg2 == DIR_CODE && (crt_p += 2))
		tmp_idx = vm->arena[((*prcs)->cur_pos + 1) % MEM_SIZE] << 8 | vm->arena[((*prcs)->cur_pos + 2) % MEM_SIZE] % MEM_SIZE;
	else if ((*prcs)->args.arg2 == IND_CODE && (crt_p += 2))
		tmp_idx2 = set_ind(vm, (int[]){i_mod((*prcs)->cur_pos), 1});
	if (!(crt_p = sti_arg3_execute(vm, prcs, tmp_idx, (int []){crt_p, tmp_idx2})))
		return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
	return (crt_p + 1);
}

int 	sti_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!sti_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 2, 3) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos + sti_execute(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}
