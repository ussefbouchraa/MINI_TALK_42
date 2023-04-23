/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:58:32 by ybouchra          #+#    #+#             */
/*   Updated: 2023/04/21 05:58:37 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk_bonus.h"

int	g_pid = 0;

void	sig_handler(int signum, siginfo_t *siginfo, void *c)
{
	static int	bit;
	static int	i;

	(void)c;
	if (g_pid != siginfo->si_pid)
	{
		bit = 0;
		i = 0;
		g_pid = siginfo->si_pid;
	}
	if (signum == SIGUSR2)
		i = (1 << bit) | i;
	bit++;
	if (bit == 8)
	{
		if (i != 0)
		{
			write(1, &i, 1);
			bit = 0;
			i = 0;
		}
		else
			kill(siginfo->si_pid, SIGUSR1);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	if (ac != 1)
	{
		write(2, "Error", 5);
		exit(1);
	}
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}
