NAME = server

CNAME = client

NAME_B = server_bonus

CNAME_B = client_bonus

CC = cc -Wall -Wextra -Werror

RM = rm -rf

S_FILES = src/server.c utils/ft_atoi.c utils/ft_putnbr.c utils/ft_isdigit.c
C_FILES = src/client.c utils/ft_atoi.c utils/ft_putnbr.c utils/ft_isdigit.c

S_FILES_B = src/server_bonus.c utils/ft_atoi.c utils/ft_putnbr.c utils/ft_isdigit.c
C_FILES_B = src/client_bonus.c utils/ft_atoi.c utils/ft_putnbr.c utils/ft_isdigit.c

S_OBJS = $(S_FILES:.c=.o)
C_OBJS = $(C_FILES:.c=.o)

S_OBJS_B= $(S_FILES_B:.c=.o)
C_OBJS_B= $(C_FILES_B:.c=.o)

all: $(NAME) $(CNAME)

$(NAME) : $(S_OBJS)
	$(CC) $^ -o $@

$(CNAME): $(C_OBJS)
	$(CC) $^ -o $@

%.o : %.c minitalk.h minitalk_bonus.h
	$(CC) -c $< -o $@

bonus: $(NAME_B) $(CNAME_B)

$(NAME_B): $(S_OBJS_B)
	$(CC) $^ -o $@

$(CNAME_B): $(C_OBJS_B)
	$(CC) $^ -o $@

clean:
	$(RM) $(S_OBJS) $(C_OBJS) $(S_OBJS_B) $(C_OBJS_B)

fclean : clean
	$(RM) $(NAME) $(CNAME) $(NAME_B) $(CNAME_B)

re : fclean all