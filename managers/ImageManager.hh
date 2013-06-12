#ifndef					__IMAGE_MANAGER_H__
# define				__IMAGE_MANAGER_H__

#include				<list>
#include				<map>
#include				<string>
#include				<iostream>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_image.h>

class					ImageManager
{
public:
  ~ImageManager();
  bool					initialize();
  void					uninitialize();
  static ImageManager			*getInstance();
  ALLEGRO_BITMAP			*load(std::string const & path);
  void					erase(std::string const & path);
  ALLEGRO_BITMAP			*get(std::string const & path);
  bool					loadList(std::list<std::string> const & list);
  bool					loadDirectory(std::string const & path);
  void					refresh();
private:
  ImageManager();			// private ctor because of singleton pattern
  std::map<std::string, ALLEGRO_BITMAP*> collection_;
  typedef std::map<std::string, ALLEGRO_BITMAP*>::iterator t_iter;
  typedef std::pair<std::string, ALLEGRO_BITMAP*> t_pair;
};

#endif					// __IMAGE_MANAGER_H__
