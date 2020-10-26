/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjouaoud <yjouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 10:41:03 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/19 14:13:08 by yjouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int g_sleep = 1000;

void	print_warzone(t_proc *proc, t_visu vis, t_vm *vm)
{
	while (vis.i <= 4096)
	{
		if (vm->ar_clr[vis.i - 1])
		{
			wattron(vis.win, COLOR_PAIR(vm->ar_clr[vis.i - 1]));
			mvwprintw(vis.win, vis.f, vis.h, " %02x", vm->arena[vis.i - 1]);
			wattroff(vis.win, COLOR_PAIR(vm->ar_clr[vis.i - 1]));
		}
		else
			mvwprintw(vis.win, vis.f, vis.h, " %02x", vm->arena[vis.i - 1]);
		print_proc(proc, vis, vm);
		print_warz1(&vis);
	}
}

void	detectkey(void)
{
	int	key;

	timeout(1);
	key = getch();
	if (key == 32)
		while (1)
		{
			timeout(10);
			key = getch();
			if (key == 32)
				break ;
		}
	else if (key == 'p')
		g_sleep -= (g_sleep >= 25000) ? 25000 : 0;
	else if (key == 'm')
		g_sleep += (g_sleep < 300000) ? 25000 : 0;
	else if (key == 's')
		g_sleep = 1000;
}

void	print_menu(t_visu vis, t_vm *vm, t_player *player)
{
	int i;

	wattron(vis.winmenu, COLOR_PAIR(4));
	mvwprintw(vis.winmenu, 5, 20, "microsecond :                    ");
	mvwprintw(vis.winmenu, 5, 20, "microsecond : %d", g_sleep);
	mvwprintw(vis.winmenu, 6, 20, "cycle : %d  ", vm->cycles);
	mvwprintw(vis.winmenu, 60, 25, "PAUSE : SPACE");
	mvwprintw(vis.winmenu, 61, 20, "VITESSE+ : P | VITESSE- : M");
	i = 0;
	while (i < vm->num_player)
	{
		wattron(vis.winmenu, COLOR_PAIR(i + 1));
		mvwprintw(vis.winmenu, 30 + i, 20, "player %d : %s",
		i + 1, player[i].champion_name);
		i++;
	}
}

void	visu(t_vm *vm, t_proc *proc, t_player *player, t_visu vis)
{
	print_warzone(proc, vis, vm);
	wrefresh(vis.win);
	detectkey();
	print_menu(vis, vm, player);
	wrefresh(vis.winmenu);
	usleep(g_sleep);
}
