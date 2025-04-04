/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:42:14 by achat             #+#    #+#             */
/*   Updated: 2025/03/21 14:08:30 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_state {
	pid_t	client_pid;
	int		current_bit;
	char	current_char;
	int		message_size;
	int		size_bytes;
	char	*message;
	int		message_index;
}		t_state;

extern t_state	g_state;

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
void	clear_server_state(void);
void	handle_message_size(void);
void	handle_message_data(siginfo_t *info);

#endif