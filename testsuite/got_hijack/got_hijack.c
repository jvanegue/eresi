/*
** unlink.c for unlinked
** 
** Started on  Sun Mar 10 01:18:51 2002 mayhem
** Last update Sun Mar 10 02:46:18 2002 mayhem
*/
#include	"libelfsh.h"

#define		TROJANED_FILE	"./a.out"
#define		OUTPUT_FILE	"./fake_aout"

int		main(int argc, char **argv)
{
  elfshobj_t	*file;
  Elf32_Sym	*new_sleep;
  int		ret;

  file = elfsh_map_obj(TROJANED_FILE);
  new_sleep = elfsh_get_symbol_by_name(file, "new_sleep");
  if (!file || !new_sleep)
    {
      elfsh_error();
      exit(-1);
    }

  /* Try this to hijack got by index or the second one to hijack by name */
  //ret = elfsh_set_got_entry_by_index(file, 5, new_sleep->st_value);
  ret = elfsh_set_got_entry_by_name(file, "sleep", new_sleep->st_value);
  if (ret < 0)
    {
      elfsh_error();
      exit(-1);
    }

  /* RELINKING THE FILE */
  ret = elfsh_save_obj(file, OUTPUT_FILE);
  if (ret < 0)
    elfsh_error();

  printf("Relinking *%s* \n", ret ? "Error" : "OK");
  return (0);
}
