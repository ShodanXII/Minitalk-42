/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:44:31 by achat             #+#    #+#             */
/*   Updated: 2025/03/21 14:30:51 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_state	g_state = {0, 0, 0, 0, 0, NULL, 0};

void	handle_client(siginfo_t *info)
{
	if (g_state.client_pid != 0 && g_state.client_pid != info->si_pid)
	{
		clear_server_state();
		g_state.client_pid = info->si_pid;
	}
	if (g_state.client_pid == 0)
		g_state.client_pid = info->si_pid;
}

void	handle_bit(int signum)
{
	if (signum == SIGUSR1)
		g_state.current_char = (g_state.current_char << 1);
	else if (signum == SIGUSR2)
		g_state.current_char = (g_state.current_char << 1) | 1;
	g_state.current_bit++;
}

void	handle_byte(siginfo_t *info)
{
	g_state.current_bit = 0;
	if (g_state.size_bytes < 4)
		handle_message_size();
	else if (g_state.message)
		handle_message_data(info);
	g_state.current_char = 0;
}

void	process_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	handle_client(info);
	handle_bit(signum);
	if (g_state.current_bit == 8)
		handle_byte(info);
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = process_signal;
	server_pid = getpid();
	ft_putnbr_fd(server_pid, 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
