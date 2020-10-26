# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/25 14:48:59 by ahmansou          #+#    #+#              #
#    Updated: 2020/10/20 12:43:34 by ahmansou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRCS =  src/ass.c\
		src/get_next_line.c\
		src/main.c\
		src/free_misc.c\
		src/champ_misc.c\
		src/ft_split_whitespaces.c\
		src/tokens.c\
		src/ops.c\
		src/ops_misc.c\
		src/misc.c\
		src/misc2.c\
		src/misc3.c\
		src/misc4.c\
		src/print_content.c\
		src/encode_calc.c\
		src/op_live.c\
		src/op_ld.c\
		src/op_st.c\
		src/op_add.c\
		src/op_and.c\
		src/op_sti.c\
		src/op_ldi.c\
		src/op_aff.c\
		src/atoi_base.c

OBJS = $(SRCS:.c=.o) 

FLG = -Wall -Werror -Wextra

$(NAME): $(OBJS)
	make -C libft
	make -C ft_printf
	gcc -g -o $(NAME) $(FLG) $(OBJS) libft/libft.a ft_printf/libftprintf.a

$(OBJS): %.o:%.c
	gcc -c $(FLG) $^ -o $@

clean:
	make clean -C libft
	make clean -C ft_printf
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	make fclean -C ft_printf
	rm -f $(NAME) 

re: fclean all

all : $(NAME)

