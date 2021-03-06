/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 21:04:10 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/18 16:44:34 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		delet_no_prev(t_proc **prcs, t_proc **tmp, t_proc *it_prcs)
{
	t_proc *to_del;

	to_del = it_prcs;
	it_prcs = it_prcs->next;
	(*prcs) = (*prcs)->next;
	(*prcs)->prev = NULL;
	free(to_del);
	it_prcs->prev = NULL;
	*tmp = it_prcs;
	return (2);
}

int		delete_prev_next(t_proc **prcs, t_proc **tmp, t_proc *it_prcs)
{
	t_proc *to_del;

	to_del = it_prcs;
	it_prcs->prev->next = it_prcs->next;
	it_prcs->next->prev = it_prcs->prev;
	it_prcs = it_prcs->prev->next;
	free(to_del);
	*tmp = it_prcs;
	return (2);
}

int		delet_rest(t_proc *it_prcs, t_proc **tmp, t_proc **prcs)
{
	t_proc *to_del;

	if (it_prcs->prev)
	{
		to_del = it_prcs;
		it_prcs->prev->next = NULL;
		free(to_del);
		*tmp = it_prcs;
	}
	else
	{
		free(it_prcs);
		it_prcs = NULL;
		*prcs = NULL;
		*tmp = it_prcs;
	}
	return (1);
}

int		ft_delete_node(t_proc **prcs, int index, t_proc **tmp)
{
	t_proc	*it_prcs;
	t_proc	*to_del;
	int		i;

	i = -1;
	it_prcs = *prcs;
	while (++i < index)
		it_prcs = it_prcs->next;
	if (it_prcs->prev && it_prcs->next)
		return (delete_prev_next(prcs, tmp, it_prcs));
	else if (!it_prcs->prev && it_prcs->next)
		return (delet_no_prev(prcs, tmp, it_prcs));
	else
		return (delet_rest(it_prcs, tmp, prcs));
}

int		check_ft(t_vm *vm, t_proc **prcs)
{
	t_proc	*it_prcs;
	int		index;

	it_prcs = *prcs;
	index = 0;
	while (it_prcs)
	{
		if (it_prcs->live == 0)
		{
			if (ft_delete_node(prcs, index, &it_prcs) == 2)
				continue ;
			else
				break ;
		}
		index += 1;
		it_prcs = it_prcs->next;
	}
	check_lives(vm);
	re_init_live(prcs);
	return (1);
}
