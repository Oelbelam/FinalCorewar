/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:28:45 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/27 18:19:55 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		aff_check_args(uint8_t c, t_op_arg *args)
{
	int	error;

	error = 1;
	if (((c >> 6) & 0b11) == REG_CODE)
		args->arg1 = 1 + 0 * args->s_arg1++;
	else
		error = 0;
	return (error);
}

int		aff_op(t_vm *vm, t_proc **prcs, t_proc **head, t_player **player)
{
	int val;

	val = 0;
	(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	init_args(&(*prcs)->args);
	if (!aff_check_args(vm->arena[(*prcs)->cur_pos], &(*prcs)->args))
	{
		(*prcs)->cur_pos = ((skip_bytes(vm->arena[(*prcs)->cur_pos], 4, 1) +
		(*prcs)->cur_pos)) % MEM_SIZE;
	}
	else
	{
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
		if (vm->arena[(*prcs)->cur_pos] >= 1 &&
		vm->arena[(*prcs)->cur_pos] <= 16)
			printf("AFF : %c\n",
			(char)(((*prcs)->r[vm->arena[(*prcs)->cur_pos] - 1] % 256)));
		(*prcs)->cur_pos = ((*prcs)->cur_pos + 1) % MEM_SIZE;
	}
	return (1);
}
