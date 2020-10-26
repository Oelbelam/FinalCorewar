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

void	print_win(unsigned char *name, t_visu vis)
{
	int key;

	key = 0;
	mvwprintw(vis.winmenu, 36, 20, "winner is : %s  ", name);
	wrefresh(vis.winmenu);
	while (1)
	{
		timeout(10);
		key = getch();
		if (key == 'x')
			break ;
	}
}

int		ft_main_loopv2(t_vm *vm, t_proc *prcs, t_player *player, int has_visu)
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
			break ;
		set_proc(&prcs, vm, player);
		check(vm, &prcs);
		if (has_visu)
			visu(vm, prcs, player, vis);
		if (!has_visu && vm->dump && print_dump(*vm))
			return (1);
	}
	if (has_visu)
		print_win(player[vm->win_id - 1].champion_name, vis);
	return (0);
}

int		ft_main_loop(t_player *player, int args_num, int has_visu)
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
		ft_printf("Contestant %d, \"%s\", has won !\n",
		vm->win_id, player[vm->win_id - 1].champion_name);
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

int		main(int ac, char **av)
{
	t_player	*player;
	int			has_vis;
	int			args_num;
	int			i;
	int			error;

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
