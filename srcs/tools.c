#include "corewar.h"

int				i_mod(int num)
{
	return (num % MEM_SIZE);
}

short			s_mod(short num)
{
	return (num % MEM_SIZE);
}

int		check_reg(t_vm *vm, int pos)
{
	if (vm->arena[pos] >= 1 && vm->arena[pos] <= 16)
		return (1);
	else
		return (0);
}

int32_t convert_short_pos(t_vm *vm, short pos, int size)
{
	int32_t result;
	int		i;


	i = 0;
	result = 0;
	while (i < size)
	{
		pos = s_mod(pos);
		result |= vm->arena[pos] << (((size - 1) * 8) - i * 8);
		i++;
		pos++;
	}
	return (result);
}

short	convert_int_pos(t_vm *vm, int pos, int size)
{
	short	result;
	int		i;

	i = 0;
	result = 0;
	while (i < size)
	{
		pos = i_mod(pos);
		result |= vm->arena[pos] << (((size - 1) * 8) - i * 8);
		i++;
		pos++;
	}
	return (result);
}

int32_t convert_pos(t_vm *vm, int pos, int size)
{
	int32_t result;
	int		i;


	i = 0;
	result = 0;
	while (i < size)
	{
		pos = s_mod(pos);
		result |= vm->arena[pos] << (((size - 1) * 8) - i * 8);
		i++;
		pos++;
	}
	return (result);
}

int32_t		set_ind(t_vm *vm, int *pos)
{
	short	index;
	int32_t	result;

	result = 0;
	index =  convert_int_pos(vm, pos[0] + pos[1], 2);
	index = pos[0] - 2 + ((index % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
	result = convert_short_pos(vm, index, 4);
	return (result);
}

void	set_st_arena(t_vm *vm, int32_t value, int *pos)
{
	short	index;

	index = convert_int_pos(vm, (pos[0] + pos[1]), 2);
	index = s_mod(((index % IDX_MOD) + MEM_SIZE));
	vm->arena[i_mod(pos[0] - 2 + (index))] = (value & 4278190080U) >> 24;
	vm->arena[i_mod(pos[0] - 2 + (index) + 1)] = (value & 16711680) >> 16;
	vm->arena[i_mod(pos[0] - 2 + (index) + 2)] = (value & 65280) >> 8;
	vm->arena[i_mod(pos[0] - 2 + (index) + 3)] = value & 255;
	vm->ar_clr[i_mod(pos[0] - 2 + (index))] = pos[2];
	vm->ar_clr[i_mod(pos[0] - 2 + (index) + 1)] = pos[2];
	vm->ar_clr[i_mod(pos[0] - 2 + (index) + 2)] = pos[2];
	vm->ar_clr[i_mod(pos[0] - 2 + (index) + 3)] = pos[2];
}

void	set_sti_arena(t_vm *vm, t_proc *prcs, int32_t index, int32_t pos)
{
	int32_t value;

	value = prcs->r[vm->arena[pos] - 1];
	vm->arena[index] = (value & 4278190080U) >> 24;
	vm->arena[i_mod(index + 1)] = (value & 16711680) >> 16;
	vm->arena[i_mod(index + 2)] = (value & 65280) >> 8;
	vm->arena[i_mod(index + 3)] = (value & 255);
	vm->ar_clr[index] = prcs->proc_clr;
	vm->ar_clr[i_mod(index + 1)] = prcs->proc_clr;
	vm->ar_clr[i_mod(index + 2)] = prcs->proc_clr;
	vm->ar_clr[i_mod(index + 3)] = prcs->proc_clr;
}