/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:27:34 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/18 17:41:40 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			lld_check_arg(uint8_t c, t_op_arg *args)
{
	int		error;

	error = 1;
	if (((c >> 6) & 0b11) == DIR_CODE && (args->s_arg1 += 4))
		args->arg1 = 2;
	else if ((((c >> 6) & 0b11) == IND_CODE) && (args->s_arg1 += 2))
		args->arg1 = 3;
	else
		error = 0;
	if ((((c >> 4) & 0b0011) == REG_CODE))
	{
		args->arg2 = 1 + 0 * args->s_arg2++;
	}
	else
		error = 0;
	return (error);
}

int			lld_execute(t_vm *vm, t_proc **prcs)
{
	short	tmp_idx;
	int		crt_p;
	int32_t	tmp_r2;

	tmp_idx = 0;
	crt_p = 0;
	if ((*prcs)->args.arg1 == DIR_CODE && (crt_p = 4))
		tmp_r2 = convert_pos(vm, (*prcs)->cur_pos, 4);
	else if ((*prcs)->args.arg1 == IND_CODE && (crt_p = 2))
		tmp_r2 = set_ind(vm, (int[]){(*prcs)->cur_pos, 0});
	if (check_reg(vm, i_mod((*prcs)->cur_pos + crt_p)) == 1)
	{
		(*prcs)->r[vm->arena[((*prcs)->cur_pos + crt_p) %
		MEM_SIZE] - 1] = tmp_r2;
		(*prcs)->carry = (tmp_r2 == 0) ? 1 : 0;
	}
	return (crt_p + 1);
}

int			lld_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int		arg_ret;

	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!lld_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 2) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos +
						lld_execute(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}
