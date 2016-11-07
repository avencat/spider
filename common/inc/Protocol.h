/*
** Protocol.h for Spider in /home/touzet_t/epitech/cpp/cpp_spider/common
** 
** Made by Theo TOUZET
** Login   <touzet_t@epitech.net>
** 
** Started on  Mon Nov  7 06:27:00 2016 Theo TOUZET
** Last update Mon Nov  7 06:44:31 2016 Theo TOUZET
*/

#ifndef PROTOCOL_HH_
# define PROTOCOL_HH_

/* SERVER */
// CODES (CMD)
# define SPD_SYN_ACK	100
# define SPD_MSG	101
# define SPD_START	102
# define SPD_STOP	103
# define SPD_CLOSE	104

// CODES (RPL)
# define SPD_RPL_ID		200
# define SPD_RPL_ID_OK		201
# define SPD_RPL_RECEIVED	202
# define SPD_RPL_OK		203
# define SPD_RPL_PONG		204
# define SPD_RPL_QUIT_OK	205

// CODES (ERR)
# define SPD_ERR_BAD_ID		400
# define SPD_ERR_BAD_MSG_FORMAT	401

// CODES (SRV_ERR)
# define SPD_ERR_IO_ERROR	500

// Server protocol structures
typedef struct	s_spider_srv_cmd
{
  int		code;
  char		msg[255];
}		t_spider_srv_cmd;

/* !SERVER */

// Handshake structures
typedef struct	s_spider_hs_client
{
  char		type;
  int		number;
}		t_spider_hs_client;

typedef struct	s_spider_hs_server
{
  int		numberA;
  int		numberB;
}		t_spider_hs_server;

/* CLIENT */

// TYPE
# define SPD_SYN	0
# define SPD_ACK	1
# define SPD_GREET	2
# define SPD_HELLO	3
# define SPD_WORD	4
# define SPD_BREAK	5
# define SPD_MPOS	6
# define SPD_MBTN	7
# define SPD_PING	8
# define SPD_QUIT	9

// Client protocol structures
typedef struct	s_spider_cl
{
  long		timestamp;
  char		type;
  int	        len_title;
  int	        len_content;
  char	        title[255];
  char		content[512];
}		t_spider_cl;

/* !CLIENT */

#endif /* !PROTOCOL_HH_ */
