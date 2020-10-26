/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vm_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:43:15 by jbouazao          #+#    #+#             */
/*   Updated: 2020/10/19 13:43:16 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	set_exec_code(t_vm *vm, t_player *player)
{
	int position;
	int i;
	int k;

	i = 0;
	position = 0;
	while (i < vm->num_player)
	{
		position = (MEM_SIZE / vm->num_player) * i;
		k = 0;
		while (k < player[i].exec_code_size)
		{
			vm->arena[position + k] = player[i].exec_code[k];
			vm->ar_clr[position + k] = player[i].pid;
			k++;
		}
		i++;
	}
}
