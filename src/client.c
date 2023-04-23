/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 06:22:36 by ybouchra          #+#    #+#             */
/*   Updated: 2023/04/21 06:01:27 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	printmsg(int signum)
{
	(void)signum;
	write(1, "msg successfully transmitted !!\n", 33);
}

void	send_bit(int pid, int bit)
{
	if (kill(pid, 0) != 0)
	{
		write(2, "pid Error", 9);
		exit(1);
	}
	if (bit == 0)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(900);
}	

void	send_msg(int pid, char *msg)
{
	int	i;

	while (*msg)
	{
		i = -1;
		while (++i < 8)
			send_bit(pid, (*msg >> i) & 1);
		msg++;
	}
	i = -1;
	while (++i < 8)
		send_bit(pid, 0);
}

int	main(int ac, char **av)
{
	signal(SIGUSR1, printmsg);
	if (ac != 3)
	{
		write(2, "Error", 5);
		exit(1);
	}
	if (ft_isdigit(av[1]) || ft_atoi(av[1]) < 1)
		write(2, "pid Error1\n", 12);
	else
		send_msg(ft_atoi(av[1]), av[2]);
	exit(0);
}
