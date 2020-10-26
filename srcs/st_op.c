/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:45:31 by oelbelam          #+#    #+#             */
/*   Updated: 2020/09/22 16:47:52 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		st_check_arg(uint8_t c, t_op_arg *args)
{
	int error;

	error = 1;
	if (((c >> 6) & 0b11) == REG_CODE && (args->s_arg1 += 1))
		args->arg1 = 1;
	else
		error = 0;
	if ((((c >> 4) & 0b0011) == REG_CODE))
		args->arg2 = 1 + 0 * args->s_arg2++;
	else if (((c >> 4) & 0b0011) == IND_CODE && (args->s_arg2 += 2))
		args->arg2 = 3;
	else
		error = 0;
	return (error);
}

int		st_execute(t_vm *vm, t_proc **pr)
{
	int32_t		tmp_r;
	short		ind_v;
	int			crt_p;

	crt_p = 0;
	tmp_r = 0;
	ind_v = 0;
	if ((*pr)->args.arg1 == REG_CODE)
	{
		if (check_reg(vm, (*pr)->cur_pos))
			tmp_r = (*pr)->r[vm->arena[((*pr)->cur_pos) % MEM_SIZE] - 1];
		else
			return ((*pr)->args.s_arg1 + (*pr)->args.s_arg2);
	}
	crt_p++;
	if ((*pr)->args.arg2 == REG_CODE)
	{
		if (check_reg(vm, i_mod((*pr)->cur_pos + crt_p)))
			(*pr)->r[vm->arena[i_mod((*pr)->cur_pos + crt_p)] - 1] = tmp_r;
		else
			return ((*pr)->args.s_arg1 + (*pr)->args.s_arg2);
	}
	else if ((*pr)->args.arg2 == IND_CODE)
		wr_arena(vm, tmp_r, (int[]){(*pr)->cur_pos, crt_p, (*pr)->proc_clr});
	return ((*pr)->args.s_arg1 + (*pr)->args.s_arg2);
}

int		st_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int		arg_ret;

	(void)head;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!st_check_arg(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 2) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		(*prcs)->cur_pos = ((*prcs)->cur_pos + st_execute(vm, prcs)) % MEM_SIZE;
	}
	return (1);
}
