SERVER = server
CLIENT = client

SERVER_BNS = server_bonus
CLIENT_BNS = client_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_SERVER = ft_atoi.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strlen.c server.c utils.c
SRCS_CLIENT = ft_atoi.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strlen.c client.c

SRCS_SERVER_BNS = ft_atoi.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strlen.c server_bonus.c utils_bonus.c
SRCS_CLIENT_BNS = ft_atoi.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strlen.c client_bonus.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

OBJS_SERVER_BNS = $(SRCS_SERVER_BNS:.c=.o)
OBJS_CLIENT_BNS = $(SRCS_CLIENT_BNS:.c=.o)

all: server client

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS_SERVER_BNS) $(OBJS_CLIENT_BNS)
	$(CC) $(OBJS_SERVER_BNS) -o ${SERVER_BNS}
	$(CC) $(OBJS_CLIENT_BNS) -o ${CLIENT_BNS}
	@touch bonus

server client: $(OBJS_SERVER) $(OBJS_CLIENT)
	$(CC) $(OBJS_SERVER) -o ${SERVER}
	$(CC) $(OBJS_CLIENT) -o ${CLIENT}

clean:
	rm -f $(OBJS_SERVER) $(OBJS_SERVER_BNS) $(OBJS_CLIENT) $(OBJS_CLIENT_BNS) bonus

fclean: clean
	rm -f server client server_bonus client_bonus

re: fclean all

.PHONY: clean
