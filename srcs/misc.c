/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:07:08 by oelbelam          #+#    #+#             */
/*   Updated: 2020/10/18 17:19:25 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_files(char **av)
{
	int	count;
	int	i;
	int	len;
	int	j;

	count = 0;
	i = 1;
	while (av[i])
	{
		len = ft_strlen(av[i]) - 1;
		if (av[i][len] && av[i][len] == 'r' &&
			av[i][len - 1] && av[i][len - 1] == 'o' &&
			av[i][len - 2] && av[i][len - 2] == 'c' &&
			av[i][len - 3] && av[i][len - 3] == '.')
			count++;
		i++;
	}
	return (count);
}

int		is_cor_file(char *av)
{
	int	len;

	len = ft_strlen(av) - 1;
	if (av[len] && av[len] == 'r' &&
		av[len - 1] && av[len - 1] == 'o' &&
		av[len - 2] && av[len - 2] == 'c' &&
		av[len - 3] && av[len - 3] == '.')
		return (1);
	return (0);
}

int		is_num_neg(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '-')
		i++;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (0);
	return (1);
}

int		is_num(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (0);
	return (1);
}

int		get_n_args(char **av, char ***args)
{
	int	n;
	int	i;

	i = 0;
	while (av[++i])
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			i++;
			if (is_num(av[i]) && (n = ft_atoi(av[i])) &&
				n > 0 && n <= check_files(av))
			{
				if ((*args)[n - 1] || !is_cor_file(av[++i]))
					return (-1);
				(*args)[n - 1] = ft_strdup(av[i]);
			}
			else
				return (-2);
		}
	}
	return (1);
}
