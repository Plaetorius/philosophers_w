# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 12:46:27 by tgernez           #+#    #+#              #
#    Updated: 2023/05/02 18:44:03 by tgernez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
FTSRCS			= .c
DIRSRCS 		= srcs/
SRCS 			=	$(addsuffix ${FTSRCS},	\
					$(addprefix ${DIRSRCS},	\
					philo		\
					atoi_def	\
					time		\
					parsing		\
					cleaning	\
					init		\
					mutexes		\
					actions		\
					threads		\
					synchro		\
					))
INCLUDES		= -Iincludes
CC				= cc
FLAGS			= -Wall -Wextra -Werror -fsanitize=thread
FLAG_THREADS	= -pthread
OBJS			= ${SRCS:.c=.o}
RM				= rm -rf
RED				= \033[1;31m
NC				= \033[0m
LGREEN			= \033[1;32m
CYAN			= \033[1;36m

%.o: %.c
	@echo "\033[1A                                                          "
	@echo -n "\033[1A"
	@echo "${CYAN}Compiling $< ${NC}"
	@${CC} ${FLAGS} ${FLAG_THREADS} -o $@ -c $^ ${INCLUDES}

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${FLAG_THREADS} ${OBJS} ${INCLUDES} -o $@ -g3
	@echo "${LGREEN}Successfully created${NC}${CYAN} ${NAME}${NC}${LGREEN}!${NC}"

sanitize: ${OBJS}
	@${CC} ${FLAGS} ${FLAG_THREADS} ${OBJS} ${INCLUDES} -o philo -g3 -fsanitize=thread

#----------------------------------PHILOSOPHERS

clean:
	@echo "${CYAN}Cleaned ${NAME}${NC}"
	@${RM} ${OBJS}
fclean:		clean
	@echo "${CYAN}FCleaned ${NAME}${NC}"
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
