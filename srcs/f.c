/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:36:29 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/18 17:18:32 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			return_err(char ***args, int av_num)
{
	free2d(args, av_num);
	return (0);
}

int			has_vis(char **av, int ac)
{
	if (ft_strcmp(av[ac - 1], "-v"))
		return (1);
	return (0);
}

int			get_args(int ac, char **av, char ***args, int *dump)
{
	int err;
	int av_num;

	av_num = 0;
	if (ac > 1 && (av_num = check_files(av)) <= 4 && check_files(av) > 0)
	{
		if (!((*args) = ft_memalloc(sizeof(char *) * av_num)))
			return (0);
		if ((err = get_n_args(av, args)) < 0)
		{
			ft_printf("ERROR 1 %d\n", err);
			return (return_err(args, av_num));
		}
		if ((err = get_other_args(av, args, dump, ac)) < 0)
		{
			ft_printf("ERROR 2 %d\n", err);
			return (return_err(args, av_num));
		}
	}
	else
		return (0);
	return (av_num);
}

int			check_vis(int *ac, char **av)
{
	if (!ft_strcmp(av[(*ac) - 1], "-v"))
	{
		(*ac) -= 1;
		return (1);
	}
	return (0);
}

t_player	*ft_main(int ac, char **av, int *has_vis, int *args_num)
{
	char		**args;
	int			av_num;
	int			i;
	int			dump;
	t_player	*players;

	*has_vis = check_vis(&ac, av);
	if ((av_num = get_args(ac, av, &args, &dump)) != 0)
	{
		i = -1;
		while (++i < av_num)
			if (args[i] && (*args_num += 1))
				continue;
		players = (t_player *)ft_memalloc(sizeof(t_player) * i);
		while (--i > -1)
		{
			players[i].file_name = ft_strdup(args[i]);
			players[i].pid = i + 1;
			players[i].dump = dump;
		}
		free2d(&args, av_num);
	}
	else
		exit(0);
	return (players);
}
