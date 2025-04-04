/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:47:07 by achat             #+#    #+#             */
/*   Updated: 2025/03/21 14:25:01 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	clear_server_state(void)
{
	g_state.current_bit = 0;
	g_state.current_char = 0;
	g_state.message_size = 0;
	g_state.size_bytes = 0;
	g_state.message_index = 0;
	if (g_state.message)
	{
		free(g_state.message);
		g_state.message = NULL;
	}
}

void	handle_message_size(void)
{
	((char *)&g_state.message_size)[g_state.size_bytes] = g_state.current_char;
	g_state.size_bytes++;
	if (g_state.size_bytes == 4)
	{
		if (g_state.message_size <= 0 || g_state.message_size > 100000)
		{
			g_state.client_pid = 0;
			return ;
		}
		g_state.message = malloc (g_state.message_size + 1);
		if (!g_state.message)
			exit(EXIT_FAILURE);
		g_state.message[g_state.message_size] = '\0';
	}
}

void	handle_message_data(siginfo_t *info)
{
	(void)info;
	g_state.message[g_state.message_index++] = g_state.current_char;
	if (g_state.message_index == g_state.message_size)
	{
		ft_putstr_fd(g_state.message, 1);
		write(1, "\n", 1);
		free(g_state.message);
		g_state.message = NULL;
		kill(info->si_pid, SIGUSR1);
		clear_server_state();
	}
}
