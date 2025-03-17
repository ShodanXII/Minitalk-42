/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:21:12 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/11 11:27:29 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack_received = 0;

static void	signal_acknowledged(int signum)
{
	if (signum == SIGUSR1)
	{
		write(1, "Message received by server!\n", 28);
		g_ack_received = 1;
	}
}

void	ft_send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_putstr_fd("can not send signal\n", 1);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_putstr_fd("can not send signal\n", 1);
				exit(EXIT_FAILURE);
			}
		}
		i--;
		usleep(300);
	}
}

void	ft_send_int(int pid, int num)
{
	char	*ptr;
	int		i;

	ptr = (char *)&num;
	i = 0;
	while (i < 4)
	{
		ft_send_char(pid, ptr[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;

	i = 0;
	if (argc != 3)
		exit(EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	if (pid <= 1 || !*argv[2])
		exit(EXIT_FAILURE);
	signal(SIGUSR1, signal_acknowledged);
	ft_send_int(pid, ft_strlen(argv[2]));
	while (argv[2][i])
		ft_send_char(pid, argv[2][i++]);
	while (!g_ack_received)
		pause();
	return (0);
}
