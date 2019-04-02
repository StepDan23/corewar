/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:02:36 by artemiy           #+#    #+#             */
/*   Updated: 2019/04/02 19:50:12 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "vm.h"
#include "libft.h"

int		count_champs(t_champion *head)
{
	int			champs_num;
	t_champion	*ch;

	champs_num = 0;
	ch = head;
	while (ch)
	{
		champs_num++;
		ch = ch->next;
	}
	return (champs_num);
}

void	vm_load_champ(unsigned char *mem, t_champion *champ, int index)
{
	unsigned int	i;

	i = 0;
	while (i < champ->size)
	{
		mem[index + i] = champ->code[i];
		i++;
	}
}

int		vm_index_to_load(int total, int curr)
{
	int	pos;

	pos = curr * (MEM_SIZE / total);
	pos -= pos % 32;
	return (pos);
}

void	vm_spread_champs(t_vm *vm, t_champion *champs)
{
	int			champs_num;
	int			i;
	t_proccess	*proccess;

	champs_num = count_champs(champs);
	i = 0;
	while (i < champs_num)
	{
		ft_printf("%d\n", vm_index_to_load(champs_num, i));
		vm_load_champ(vm->memory, champs, vm_index_to_load(champs_num, i));
		proccess = proccess_new(champs->id, vm_index_to_load(champs_num, i));
		if (!proccess)
		{
			ft_printf("Error: %s\n", strerror(errno));
			exit(0);
		}
		proccess_add(&vm->process, proccess);
		i++;
		champs = champs->next;
	}
}
