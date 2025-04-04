/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:40:20 by achat             #+#    #+#             */
/*   Updated: 2025/03/21 14:34:34 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	transmit_byte(int server_pid, char byte)
{
	int	bit_position;

	bit_position = 7;
	while (bit_position >= 0)
	{
		if ((byte >> bit_position) & 1)
		{
			if (kill(server_pid, SIGUSR2) == -1)
			{
				ft_putstr_fd("ERROR: Failed to send signal to server\n", 1);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (kill(server_pid, SIGUSR1) == -1)
			{
				ft_putstr_fd("ERROR: Failed to send signal to server\n", 1);
				exit(EXIT_FAILURE);
			}
		}
		bit_position--;
		usleep(300);
	}
}

void	transmit_integer(int server_pid, int value)
{
	char	*byte_ptr;
	int		byte_index;

	byte_ptr = (char *)&value;
	byte_index = 0;
	while (byte_index < 4)
	{
		transmit_byte(server_pid, byte_ptr[byte_index]);
		byte_index++;
	}
}

int	main(int argc, char **argv)
{
	int		char_index;
	pid_t	server_pid;

	char_index = 0;
	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client [server_pid] [message]\n", 1);
		exit(EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 1 || !*argv[2])
	{
		ft_putstr_fd("ERROR: Invalid PID or empty message\n", 1);
		exit(EXIT_FAILURE);
	}
	transmit_integer(server_pid, ft_strlen(argv[2]));
	while (argv[2][char_index])
	{
		transmit_byte(server_pid, argv[2][char_index]);
		char_index++;
	}
	return (0);
}
