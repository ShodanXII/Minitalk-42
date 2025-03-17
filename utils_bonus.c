/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:31:50 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/11 13:03:49 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	reset_server_state(void)
{
	g_server.bit = 0;
	g_server.c = 0;
	g_server.len = 0;
	g_server.byte_count = 0;
	g_server.index = 0;
	if (g_server.buffer)
	{
		free(g_server.buffer);
		g_server.buffer = NULL;
	}
}

void	handle_message_length(void)
{
	((char *)&g_server.len)[g_server.byte_count] = g_server.c;
	g_server.byte_count++;
	if (g_server.byte_count == 4)
	{
		if (g_server.len <= 0 || g_server.len > 100000)
		{
			g_server.pid = 0;
			return ;
		}
		g_server.buffer = malloc(g_server.len + 1);
		if (!g_server.buffer)
			exit(EXIT_FAILURE);
		g_server.buffer[g_server.len] = '\0';
	}
}

void	handle_message_content(siginfo_t *info)
{
	(void)info;
	g_server.buffer[g_server.index++] = g_server.c;
	if (g_server.index == g_server.len)
	{
		ft_putstr_fd(g_server.buffer, 1);
		write(1, "\n", 1);
		free(g_server.buffer);
		g_server.buffer = NULL;
		kill(info->si_pid, SIGUSR1);
		reset_server_state();
	}
}
