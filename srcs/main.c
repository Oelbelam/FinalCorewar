/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:59:08 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/18 17:59:08 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void init_player(t_player *player)
{
	player->file_name = NULL;
	player->exec_code = NULL;
	player->live = 0;
}

void re_init_live(t_proc **proc)
{
	t_proc *it_proc;

	it_proc = *proc;
	while (it_proc)
	{
		it_proc->live = 0;
		it_proc = it_proc->next;
	}
}

void ft_annonce_players(t_player *players, int args_num)
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

void set_proc(t_proc **prcs, t_vm *vm, t_player *player)
{
	t_ops ops;
	t_proc *it;

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
void check(t_vm *vm, t_proc **prcs)
{
	if ((vm->c_to_die >= 0) && vm->cycle_to_check >= vm->c_to_die)
	{
		check_ft(vm, prcs);
		vm->cycle_to_check = 0;
	}
	else if (vm->c_to_die < 0)
		check_ft(vm, prcs);
}

int			ft_main_loopv2(t_vm *vm, t_proc *prcs, t_player *player, int has_visu)
{
	t_visu	vis;
	int		key;
	
	if (has_visu)
		init_visu(&vis);
	while (1)
	{
		vm->cycles++;
		vm->cycle_to_check++;
		if (!prcs)
			break;
		set_proc(&prcs, vm, player);
		check(vm, &prcs);
		if (has_visu)
			visu(vm, prcs, player, vis);
		if (!has_visu && vm->dump && print_dump(*vm))
				return (1);
	}
	if (has_visu)
	{
		mvwprintw(vis.winmenu, 30, 2, "winner is : %s  ", player[vm->win_id - 1].champion_name);
		wrefresh(vis.winmenu);
		while (1)
		{
			timeout(10);
			key = getch();
			if (key == 'x')
				break;
		}
	}
	return (0);
}

int			ft_main_loop(t_player *player, int args_num, int has_visu)
{
	t_vm	*vm;
	t_proc	*prcs;
	int		temp;

	prcs = NULL;
	vm = init_vm(args_num, player[0].dump);
	set_exec_code(vm, player);
	init_procs(vm, player, &prcs);
	temp = ft_main_loopv2(vm, prcs, player, has_visu);
	if (!has_visu && !temp)
		ft_printf("Contestant %d, \"%s\", has won !\n", vm->win_id, player[vm->win_id - 1].champion_name);
	ft_memdel((void **)&vm);
	return (0);
}

void	free_env(t_player **player, int args_num)
{
	int	i;

	i = 0;
	while (i < args_num)
	{
		ft_memdel((void **)&((*player)[i]).file_name);
		ft_memdel((void **)&((*player)[i]).exec_code);
		i++;
	}
	ft_memdel((void **)player);
}

int main(int ac, char **av)
{
	t_player *player;
	int has_vis;
	int args_num;
	int i;
	int error;

	args_num = 0;
	has_vis = 0;
	player = ft_main(ac, av, &has_vis, &args_num);
	i = 0;
	while (i < args_num)
	{
		if ((error = parse_file(player, i)) < 0)
		{
			print_errors(error, player[i]);
			free_env(&player, i + 1);
			return (0);
		}
		i++;
	}
	if (!has_vis)
		ft_annonce_players(player, args_num);
	ft_main_loop(player, args_num, has_vis);
	free_env(&player, args_num);
}