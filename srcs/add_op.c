/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:06:04 by oelbelam          #+#    #+#             */
/*   Updated: 2020/09/22 16:59:53 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		add_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if (((c >> 6) & 0b11) == REG_CODE)
		args->arg1 = 1 + 0 * args->s_arg1++;
	else
		error = 0;
	if (((c >> 4) & 0b0011) == REG_CODE)
		args->arg2 = 1 + 0 * args->s_arg2++;
	else
		error = 0;
	if (((c >> 2) & 0b000011) == REG_CODE)
		args->arg3 = 1 + 0 * args->s_arg3++;
	else
		error = 0;
	return (error);
}

int		add_execut(t_vm *vm, t_proc **prcs)
{
	int		tmp_r;
	int		crt_p;

	crt_p = 0;
	tmp_r = 0;
	if (vm->arena[(*prcs)->cur_pos] >= 1 && vm->arena[(*prcs)->cur_pos] <= 16)
		tmp_r = (*prcs)->r[vm->arena[((*prcs)->cur_pos)] - 1];
	else
		return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
	crt_p++;
	if (vm->arena[i_mod(((*prcs)->cur_pos + crt_p))] >= 1
		&& vm->arena[i_mod((*prcs)->cur_pos + crt_p)] <= 16)
		tmp_r = tmp_r + (*prcs)->r[vm->arena[i_mod((*prcs)->cur_pos + crt_p)] - 1];
	else
		return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
	crt_p++;
	if (vm->arena[i_mod((*prcs)->cur_pos + crt_p)] >= 1
	&& vm->arena[i_mod((*prcs)->cur_pos + crt_p)] <= 16)
	{
		(*prcs)->r[vm->arena[i_mod((*prcs)->cur_pos + crt_p)] - 1] = tmp_r;
		(*prcs)->carry = (tmp_r == 0) ? 1 : 0;
	}
	return ((*prcs)->args.s_arg1 + (*prcs)->args.s_arg2 + (*prcs)->args.s_arg3);
}

int		add_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int		arg_ret;

	(void)head;
	arg_ret = 0;
	(*prcs)->cur_pos = i_mod((*prcs)->cur_pos + 1);
	init_args(&(*prcs)->args);
	if (!add_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 3) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = i_mod((*prcs)->cur_pos + 1);
		(*prcs)->cur_pos = ((*prcs)->cur_pos + add_execut(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}