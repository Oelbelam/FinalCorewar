/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ass.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbelam <oelbelam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:03:28 by ahmansou          #+#    #+#             */
/*   Updated: 2020/10/27 18:11:28 by oelbelam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASS_H
# define ASS_H

# define BUFF_SIZE 1
# define FD_LIMIT 4864

# include "../libft/libft.h"
# include "../ft_printf/src/ft_printf.h"
# include "op.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

typedef	struct		s_lines
{
	char			*line;
	struct s_lines	*next;
}					t_lines;

typedef struct		s_op
{
	char			*name;
	char			binary;
	char			arg[3];
	int				code;
	int				cycle;
	char			*desc;
	char			carry;
	char			octcode;
	int				tdir_sz;
}					t_op;

typedef struct		s_token
{
	int				type;
	char			*name;
	int				args[3];
	char			argc[3];
	int				code;
	int				tdir_sz;
	int				is_encode;
	int				encode;
	int				sz;
	char			*labels[3];
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct		s_ch
{
	char			*prog_name;
	char			*prog_cmnt;
}					t_ch;

typedef struct		s_ass_env
{
	struct s_op		*op;
	t_lines			*lines;
	t_token			*tokens;
	int				sz;
	int				exec_code_sz;
	struct s_ch		champ;
}					t_ass_env;

typedef struct		s_op_types
{
	int				opss[16];
	int				(*t[16])(t_token **op, char ***sp);
}					t_op_types;

t_op_types			get_o_types(void);
int					o_live(t_token **op, char ***sp);
int					o_ld(t_token **op, char ***sp);
int					o_st(t_token **op, char ***sp);
int					o_add(t_token **op, char ***sp);
int					o_and(t_token **op, char ***sp);
int					o_zjmp(t_token **op, char ***sp);
int					o_ldi(t_token **op, char ***sp);
int					o_sti(t_token **op, char ***sp);
int					o_fork(t_token **op, char ***sp);
int					o_lld(t_token **op, char ***sp);
int					o_lldi(t_token **op, char ***sp);
int					o_lfork(t_token **op, char ***sp);
int					o_aff(t_token **op, char ***sp);

void				fill_args(t_token **op, char **sp, int arg);
int					assembler(char *fn, t_ass_env *ass);
int					get_lines(char *filename, t_ass_env *env);
char				**ft_split_whitespaces(char *str);
int					skip_ws(char *line);
int					is_label(char *s);
int					get_champ_name(char *line, t_ass_env *ass);
int					get_champ_cmnt(char *line, t_ass_env *ass);
int					is_label_char(char c);
int					get_label(char *line, t_ass_env *ass, int l);
int					add_token(t_ass_env *ass, t_token *new);
t_token				*new_token(char *line, int type);
int					is_op(char *line);
const t_op			*get_op_tab(void);
int					get_op(char *line, t_ass_env *ass);
void				free2d(char ***s);
int					ft_atoi_base(char *nb, int base);

void				print_magic_header(int fd);
void				print_name_comnt(int fd, char *name, int max);
void				print_null(int fd);
int					print_exec_code_size(int fd, int sz);
void				print_content(t_token *ttoken, char *fn, int sz);
void				print_exec_code(int fd, t_token *tk);

int					count_int(int n);
char				*renamefn(char *s);

void				print_live(t_token *token, int fd);
void				print_ld(t_token *token, int fd);
void				print_st(t_token *token, int fd);
void				print_add_sub(t_token *token, int fd);
void				print_and_xor(t_token *token, int fd);
void				print_sti(t_token *token, int fd);
void				print_ldi(t_token *token, int fd);
void				print_aff(t_token *token, int fd);

int					is_num(char *s);
int					is_num_neg(char *s);

int					calc_encode(char *arg1, char *arg2, char *arg3);
int					calc_sz(char *argc, int dirsz);
int					calc_exec_code_sz(t_token *token);

void				get_argc_types(t_token **op, char **sp);

int					get_labels(t_token **token);

void				free_lines(t_lines **lines);
void				free_token(t_token **token);
void				free_name_cmnt(t_ch *ch);

int					check_if_no_op(t_ass_env ass);
void				init_env(t_ass_env *ass);
void				remove_cmnt(char ***sp, int id);
int					get_cmnt_start(char *s);
int					has_cmnt(char *s);
int					is_cmnt(char *s);

int					r_err(char r);
int					has_cmnt(char *s);

void				remove_cmnt2(char **line);

#endif
