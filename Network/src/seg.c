/*
** seg.c for seg in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 12:12:28 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 12:14:43 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		seg(t_server *server, t_player *player)
{
  char		buffer[20];
  t_team	*player_team;

  if ((player_team = get_team_by_player(server, player)) == NULL)
    {
      fprintf(stderr, ERR_TEAM);
      return (-1);
    }
  if (memset(buffer, 0, 20) == NULL
      || snprintf(buffer, 20, SEG, player_team->name) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (send_all_graphics(server, buffer));
}
