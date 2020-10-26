/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:34:47 by jbouazao          #+#    #+#             */
/*   Updated: 2020/10/20 12:34:48 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_player(t_player *player)
{
	player->file_name = NULL;
	player->exec_code = NULL;
	player->live = 0;
}

void	re_init_live(t_proc **proc)
{
	t_proc *it_proc;

	it_proc = *proc;
	while (it_proc)
	{
		it_proc->live = 0;
		it_proc = it_proc->next;
	}
}

void	ft_annonce_players(t_player *players, int args_num)
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < args_num)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		players[i].pid, players[i].exec_code_size, players[i].champion_name,
		players[i].champion_comment);
		i++;
	}
}

void	set_proc(t_proc **prcs, t_vm *vm, t_player *player)
{
	t_ops	ops;
	t_proc	*it;

	it = *prcs;
	ops = get_ops();
	while (it)
	{
		if (it->flag == 0)
		{
			if (!get_op(vm, &it))
			{
				it->cur_pos = (it->cur_pos + 1) % MEM_SIZE;
				it = it->next;
				continue;
			}
			else
				it->flag = 1;
		}
		if ((it->cycle_to_wait -= 1) && (it->cycle_to_wait) == 1)
		{
			ops.ops[it->current_op](vm, &it, prcs, &player);
			it->flag = 0;
		}
		it = it->next;
	}
}

void	check(t_vm *vm, t_proc **prcs)
{
	if ((vm->c_to_die >= 0) && vm->cycle_to_check >= vm->c_to_die)
	{
		check_ft(vm, prcs);
		vm->cycle_to_check = 0;
	}
	else if (vm->c_to_die < 0)
		check_ft(vm, prcs);
}
