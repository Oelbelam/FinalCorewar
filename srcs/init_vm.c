#include "corewar.h"

t_vm *init_vm(int args_num, int dump)
{
    int i;
    t_vm *vm;

    i = 0;
    vm = (t_vm *)ft_memalloc(sizeof(t_vm));
    while (i < 4096)
    {
        vm->arena[i] = 0;
        vm->ar_clr[i++] = 0;
    }
    vm->c_to_die = CYCLE_TO_DIE;
    vm->cycle_to_check = 0;
    vm->cycles = 0;
    vm->win_id = args_num;
    vm->players = NULL;
    vm->num_player = args_num;
    vm->nbr_lives = 0;
    vm->dump = dump;
    vm->nbr_chks = 0;
    vm->index = 0;
    return (vm);
}

void init_args(t_op_arg *args)
{
    args->arg1 = 0;
    args->arg2 = 0;
    args->arg3 = 0;
    args->s_arg1 = 0;
    args->s_arg2 = 0;
    args->s_arg3 = 0;
}