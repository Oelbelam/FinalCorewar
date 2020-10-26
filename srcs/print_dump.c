/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:35:03 by jbouazao          #+#    #+#             */
/*   Updated: 2020/10/20 12:35:06 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_dump(t_vm vm)
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
