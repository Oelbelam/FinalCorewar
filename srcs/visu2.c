/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:26:08 by jbouazao          #+#    #+#             */
/*   Updated: 2020/10/20 12:26:10 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_visu(t_visu *vis)
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

void	print_warz1(t_visu *vis)
{
	if (vis->i % 64 == 0 && vis->i != 0)
	{
		vis->h = 1;
		vis->f++;
	}
	else
		vis->h = vis->h + 3;
	vis->i++;
}

void	print_proc(t_proc *proc, t_visu vis, t_vm *vm)
{
	t_proc *it_proc;

	it_proc = proc;
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
}
