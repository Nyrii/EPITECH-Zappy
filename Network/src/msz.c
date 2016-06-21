/*
** msz.c for msz in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:00:27 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 13:46:30 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "errors.h"
#include "server.h"
#include "replies.h"

int		msz(t_server *srv, t_client *cl)
{
  char		buffer[40];

  if (!srv || !cl)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (memset(buffer, 0, 40) == NULL
      || snprintf(buffer, 40, MSZ,
		  srv->data.world_x, srv->data.world_y) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  if (dprintf(cl->sock, "%s", buffer) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
