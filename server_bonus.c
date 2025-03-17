/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:45:24 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/11 11:05:35 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server_state	g_server = {0, 0, 0, 0, 0, NULL, 0};

void	handle_new_client(siginfo_t *info)
{
	if (g_server.pid != 0 && g_server.pid != info->si_pid)
	{
		reset_server_state();
		g_server.pid = info->si_pid;
	}
	if (g_server.pid == 0)
		g_server.pid = info->si_pid;
}

void	process_received_bit(int signum)
{
	if (signum == SIGUSR1)
		g_server.c = (g_server.c << 1);
	else if (signum == SIGUSR2)
		g_server.c = (g_server.c << 1) | 1;
	g_server.bit++;
}

void	process_message_byte(siginfo_t *info)
{
	g_server.bit = 0;
	if (g_server.byte_count < 4)
		handle_message_length();
	else if (g_server.buffer)
		handle_message_content(info);
	g_server.c = 0;
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	handle_new_client(info);
	process_received_bit(signum);
	if (g_server.bit == 8)
		process_message_byte(info);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
