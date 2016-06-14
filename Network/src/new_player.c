/*
** new_player.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Sun Jun 12 21:31:40 2016 Nyrandone Noboud-Inpeng
*/

#include <netinet/in.h>
#include <sys/types.h>
#include "server.h"

static int		assign_egg_pos(t_server *srv, t_team *t, t_player *pl)
{
  t_egg			*e;
  unsigned int		i;

  i = 0;
  if (list_get_size(srv->data.eggs) > 0)
    return (0);
  else
    {
      while (i < list_get_size(srv->data.eggs))
	{
	  if ((e = list_get_elem_at_position(srv->data.eggs, i)) != NULL &&
	      e->father == t && e->is_born == 1)
	    {
	      pl->x = e->x;
	      pl->y = e->y;
	      list_del_elem_at_position(&srv->data.eggs, i);
	      return (1);
	    }
	  i++;
	}
    }
  return (0);
}

t_egg			*new_egg(t_server *srv, t_player *p)
{
  t_egg			*new;

  if ((new = malloc(sizeof(t_player))) == NULL)
    return (NULL);
  new->timer = 0.0;
  new->x = p->x;
  new->y = p->y;
  new->is_born = 0;
  new->father = get_team_by_player(srv, p);
  return (new);
}

t_player		*new_player(t_server *srv, t_team *t, t_client *cl)
{
  t_player		*new;

  if ((new = malloc(sizeof(t_player))) == NULL)
    return (NULL);
  new->sock = cl->sock;
  if (assign_egg_pos(srv, t, new) == 0)
    {
      new->x = rand() % srv->data.world_x;
      new->y = rand() % srv->data.world_y;
    }
  new->level = 1;
  new->orientation = rand() % 4 * 90;
  new->timer = 0.0;
  new->id = get_max_player_id(srv);
  new->inventory[FOOD] = 0;
  new->inventory[LINEMATE] = 0;
  new->inventory[DERAUMERE] = 0;
  new->inventory[SIBUR] = 0;
  new->inventory[MENDIANE] = 0;
  new->inventory[PHIRAS] = 0;
  new->inventory[THYSTAME] = 0;
  new->inventory[NONE] = -1;
  return (new);
}

t_client        	*new_client(t_server *srv)
{
  t_client		*cl;
  unsigned int		ss;
  struct sockaddr_in	sin;

  if ((cl = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  ss = sizeof(sin);
  cl->timer = 0;
  if ((cl->sock = accept(srv->sock, (struct sockaddr *) &sin, &ss)) == -1)
    {
      error("Error socket can't accept connexion");
      return (NULL);
    }
  if (cl->sock > srv->max)
    srv->max = cl->sock;
  return (cl);
}
