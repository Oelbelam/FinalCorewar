/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 10:41:03 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/15 12:01:43 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <ncurses.h>

int t_sleep = 1000;

void init_visu(t_visu *vis)
{
	initscr();
	cbreak();
	noecho();
	vis->win = newwin(66, 195, 1, 1);
	vis->winmenu = newwin(66, 66, 1, 196);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	refresh();
	box(vis->win, 0, 0);
	box(vis->winmenu, 0, 0);
	vis->i = 1;
	vis->f = 1;
	vis->h = 1;
	keypad(vis->win, true);
}
void print_warzone(t_proc *proc, t_visu vis, t_vm *vm)
{
	t_proc *it_proc;
	while (vis.i <= 4096)
	{
		it_proc = proc;
		if (vm->ar_clr[vis.i - 1])
		{
			wattron(vis.win, COLOR_PAIR(vm->ar_clr[vis.i - 1]));
			mvwprintw(vis.win, vis.f, vis.h, " %02x", vm->arena[vis.i - 1]);
			wattroff(vis.win, COLOR_PAIR(vm->ar_clr[vis.i - 1]));
		}
		else
			mvwprintw(vis.win, vis.f, vis.h, " %02x", vm->arena[vis.i - 1]);
		while (it_proc)
		{
			if (it_proc->cur_pos == vis.i - 1)
			{
				mvwprintw(vis.win, vis.f, vis.h, " ");
				wattron(vis.win, A_REVERSE | COLOR_PAIR(vm->ar_clr[vis.i - 1]));
				mvwprintw(vis.win, vis.f, vis.h + 1, "%02x", vm->arena[vis.i - 1]);
				wattroff(vis.win, A_REVERSE | COLOR_PAIR(vm->ar_clr[vis.i - 1]));
			}
			it_proc = it_proc->next;
		}
		if (vis.i % 64 == 0 && vis.i != 0)
		{
			vis.h = 1;
			vis.f++;
		}
		else
			vis.h = vis.h + 3;
		vis.i++;
	}
}

void visu(t_vm *vm, t_proc *proc, t_player *player, t_visu vis)
{

	print_warzone(proc, vis, vm);
	wrefresh(vis.win);
	int key;
	timeout(10);
	key = getch();
	if (key == 32)
	{
		while (1)
		{
			timeout(10);
			key = getch();
			if (key == 32)
				break;
		}
	}
	else if (key == 'p')
		t_sleep -= (t_sleep >= 25000) ? 25000 : 0;
	else if (key == 'm')
		t_sleep += (t_sleep < 1000000) ? 25000 : 0;
	else if (key == 's')
		t_sleep = 1000;
	else if (key == 'x')
	{
		endwin();
		exit(0);
	}
	wattron(vis.winmenu, COLOR_PAIR(4));
	mvwprintw(vis.winmenu, 2, 2, "microsecond : %d", t_sleep);
	mvwprintw(vis.winmenu, 4, 2, "cycle : %d  ", vm->cycles);
	mvwprintw(vis.winmenu, 40, 2, "PAUSE : SPACE");
	mvwprintw(vis.winmenu, 41, 2, "VITESSE+ : P | VITESSE- : M");
	int i = 0;
	while (i < vm->num_player)
	{
		mvwprintw(vis.winmenu, 6 + i, 2, "player %d : %s", i + 1, player[i].champion_name);
		i++;
	}
	wrefresh(vis.win);
	wrefresh(vis.winmenu);
	usleep(t_sleep);
	// endwin();
}