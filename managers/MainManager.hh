#ifndef					__MAIN_MANAGER_HH__
# define				__MAIN_MANAGER_HH__

#include				"SceneManager.hh"
#include				"ImageManager.hh"
#include				"EventManager.hh"
#include				"FontManager.hh"

class					MainManager
{
public:
  ~MainManager();
  bool					initialize(int width, int height);
  void					deInitialize();
  static MainManager			*getInstance();
private:
  ALLEGRO_DISPLAY			*display_;
  MainManager();
};

#endif					// __MAIN_MANAGER_HH__
