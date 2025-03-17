/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:39:32 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/11 11:20:10 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_server_state
{
	pid_t	pid;
	int		bit;
	char	c;
	int		len;
	int		byte_count;
	char	*buffer;
	int		index;
}	t_server_state;

extern t_server_state	g_server;

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char	*str);
int		ft_atoi(const char *str);

void	reset_server_state(void);
void	handle_message_length(void);
void	handle_message_content(siginfo_t *info);

#endif