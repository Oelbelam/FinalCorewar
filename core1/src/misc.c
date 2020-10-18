/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:14:05 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/18 00:55:58 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

t_op g_op_tab[17] =
	{
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 4},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 4},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 4},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 4},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 4},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 4},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 4},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 2},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1, 2},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1, 2},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 2},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 4},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1, 2},
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 2},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 2},
		{0, 0, {0}, 0, 0, 0, 0, 0, 0}};

const t_op *get_op_tab(void)
{
	return (g_op_tab);
}

const t_op_types g_op_type =
	{
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
		{&o_live, &o_ld, &o_st, &o_add, &o_add, &o_and, &o_and,
		 &o_and, &o_live, &o_ldi, &o_sti, &o_live, &o_ld,
		 &o_ldi, &o_live, &o_aff}};

t_op_types get_o_types(void)
{
	return (g_op_type);
}

int skip_ws(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\v')
		i++;
	return (i);
}

int is_label(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != LABEL_CHAR)
	{
		if (!is_label_char(s[i]))
			return (0);
		i++;
	}
	if (s[i] == LABEL_CHAR)
		return (i);
	return (0);
}

void free2d(char ***s)
{
	int i;

	i = 0;
	while ((*s)[i])
	{
		free((*s)[i]);
		i++;
	}
	free(*s);
}
