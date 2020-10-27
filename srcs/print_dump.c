/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:35:03 by jbouazao          #+#    #+#             */
/*   Updated: 2020/10/27 14:34:29 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int print_dump(t_vm vm)
{
	short it;

	if (vm.dump == vm.cycles)
	{
		it = 0;
		ft_printf("0x0000 : ");
		while (it < 4096)
		{
			if (it != 0 && it % 64 == 0)
				ft_printf("\n%#.4x : ", it);
			ft_printf("%02x ", vm.arena[it]);
			it++;
		}
		ft_printf("\n");
		return (1);
	}
	return (0);
}

void free_procs(t_proc **prcs)
{
	t_proc *to_del;

	while ((*prcs)->next)
	{
		to_del = (*prcs);
		(*prcs) = (*prcs)->next;
		ft_memdel((void **)&to_del);
	}
	ft_memdel((void **)prcs);
}