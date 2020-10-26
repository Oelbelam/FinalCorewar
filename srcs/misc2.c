/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:09:00 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/18 17:13:29 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_dump(char **av, int *i, int *dump, int *dump_found)
{
	if ((*dump_found) == 1 || !av[(*i) + 1] || !is_num_neg(av[(*i) + 1]))
		return (-3);
	(*dump) = (av[(*i) + 1]) ? ft_atoi(av[(*i) + 1]) : 0;
	(*dump_found) = 1;
	(*i) += 2;
	return ((*dump));
}

int		get_other_args(char **av, char ***args, int *dump, int ac)
{
	int i;
	int j;
	int dump_found;

	i = 0;
	while (av[++i] && i < ac)
	{
		while (i < ac && av[i] && !ft_strcmp(av[i], "-n"))
			i += 3;
		if (i < ac && !(dump_found = 0) && av[i] && !ft_strcmp(av[i], "-dump"))
			if (((*dump) = get_dump(av, &i, dump, &dump_found)) < 0)
				return (-3);
		while (i < ac && av[i] && !ft_strcmp(av[i], "-n"))
			i += 3;
		if (i < ac && av[i] && !is_cor_file(av[i]))
			return (-4);
		if (i < ac && av[i] && (j = -1))
			while (++j < 4)
				if (!(*args)[j])
				{
					(*args)[j] = ft_strdup(av[i]);
					break ;
				}
	}
	return (1);
}

int		check_dups(char **args)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = i;
		if (args[i])
			while (++j < 4)
				if (args[j] && !ft_strcmp(args[i], args[j]))
					return (1);
	}
	return (0);
}

void	free2d(char ***s, int av_num)
{
	int i;

	i = 0;
	while (i < av_num)
	{
		ft_strdel(&(*s)[i]);
		i++;
	}
	free(*s);
}
