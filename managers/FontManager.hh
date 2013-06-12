#ifndef					__FONT_MANAGER_H__
# define				__FONT_MANAGER_H__

#include				<list>
#include				<map>
#include				<string>
#include				<iostream>
#include				<sstream>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_font.h>
#include				<allegro5/allegro_ttf.h>

class					FontManager
{
public:
  ~FontManager();
  bool					initialize();
  void					uninitialize();
  static FontManager			*getInstance();
  ALLEGRO_FONT				*load(std::string const & path, int size);
  void					erase(std::string const & path, int size);
  ALLEGRO_FONT				*get(std::string const & path, int size);
private:
  FontManager();
  std::map<std::string, ALLEGRO_FONT*> collection_;
  typedef std::map<std::string, ALLEGRO_FONT*>::iterator t_iter;
  typedef std::pair<std::string, ALLEGRO_FONT*> t_pair;
};

#endif					// __FONT_MANAGER_H__
