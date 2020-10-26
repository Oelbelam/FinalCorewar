NAME = corewar

SRCS =	srcs/main.c\
		srcs/parse_file.c\
		srcs/print_errors.c\
		srcs/read_bits.c\
		srcs/init_vm.c\
		srcs/set_vm_code.c\
		srcs/proces.c\
		srcs/exec_code.c\
		srcs/visu.c\
		srcs/live_op.c\
		srcs/ld_op.c\
		srcs/st_op.c\
		srcs/add_op.c\
		srcs/sub_op.c\
		srcs/and_op.c\
		srcs/or_op.c\
		srcs/xor_op.c\
		srcs/zjmp_op.c\
		srcs/ldi_op.c\
		srcs/sti_op.c\
		srcs/fork_op.c\
		srcs/lld_op.c\
		srcs/lldi_op.c\
		srcs/lfork_op.c\
		srcs/aff_op.c \
		srcs/check_ft.c\
		srcs/tools.c\
		srcs/tools1.c\
		srcs/f.c\
		srcs/misc.c\
		srcs/misc2.c\
		srcs/visu2.c\
		srcs/misc3.c\
		srcs/print_dump.c

OBJS = $(SRCS:.c=.o)

ASM_DIR = ./asm

LIBFT = ./libft

FT_PRINTF = ./ft_printf

FT_PRINTF_LIB = ./ft_printf/libftprintf.a

FLGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT) all
	make -C $(FT_PRINTF) all
	make -C $(ASM_DIR) all
	gcc -o $(NAME) $(FLGS) $(OBJS) $(FT_PRINTF_LIB) -lncurses

$(OBJ): %.o:%.c corewar.h
	gcc -c $(FLGS) $< -o $@

clean: 
	rm -rf $(OBJS)
	make -C $(LIBFT) clean
	make -C $(FT_PRINTF) clean
	make -C $(ASM_DIR) clean

fclean : clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean
	make -C $(FT_PRINTF) fclean
	make -C $(ASM_DIR) fclean

re : fclean all
