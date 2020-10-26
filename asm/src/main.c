/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:03:32 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/20 12:39:44 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

char		*renamefn(char *s)
{
	int		i;
	char	*fn;

	i = 0;
	if (!(fn = ft_strnew(ft_strlen(s) + 2)))
		return (NULL);
	fn = ft_strncpy(fn, s, ft_strlen(s) - 2);
	while (s[i])
	{
		if (s[i] == '.' && s[i + 1] && s[i + 1] == 's')
			break ;
		fn[i] = s[i];
		i++;
	}
	fn[i++] = '.';
	fn[i++] = 'c';
	fn[i++] = 'o';
	fn[i] = 'r';
	return (fn);
}

void		find_prevs(t_token **token)
{
	t_token	*ttoken;
	t_token *current;

	ttoken = *token;
	current = NULL;
	while (ttoken)
	{
		ttoken->prev = current;
		current = ttoken;
		ttoken = ttoken->next;
	}
}

static int	check_name(char *name)
{
	int max;

	max = ft_strlen(name);
	if (!name || !name[max - 1] || !name[max - 2] ||
		(name[max - 2] && name[max - 2] != '.') ||
		(name[max - 1] && name[max - 1] != 's'))
		return (0);
	return (1);
}

void		fix_name_cmnt(t_token **token)
{
	t_token *ttoken;
	char	*tname;
	int		ttype;

	ttoken = *token;
	if (!ttoken)
		return ;
	if (ttoken->type == 2)
	{
		if (ttoken->next && ttoken->next->type == 1)
		{
			tname = ttoken->name;
			ttype = ttoken->type;
			ttoken->name = ttoken->next->name;
			ttoken->type = ttoken->next->type;
			ttoken->next->name = tname;
			ttoken->next->type = ttype;
		}
	}
}

int			main(int ac, char **av)
{
	t_ass_env	ass;
	int			i;

	init_env(&ass);
	if (ac <= 1 || ac > 2 || !check_name(av[1]))
	{
		ft_printf("SRC FILE ERROR\n");
		return (0);
	}
	if ((ac > 1 && !assembler(av[1], &ass)) || check_if_no_op(ass) == 0)
	{
		ft_printf("ERROR\n");
		free_lines(&(ass.lines));
		free_token(&(ass.tokens));
		return (0);
	}
	fix_name_cmnt(&(ass.tokens));
	ass.sz = 0;
	i = 0;
	find_prevs(&(ass.tokens));
	if (get_labels(&(ass.tokens)))
		print_content(ass.tokens, av[1], ass.sz);
	free_lines(&(ass.lines));
	free_token(&(ass.tokens));
	return (0);
}
