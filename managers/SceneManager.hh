#ifndef					__SCENE_MANAGER_HH__
# define				__SCENE_MANAGER_HH__

#include                                <allegro5/allegro.h>
#include				<string>
#include				<list>
#include				<algorithm>
#include				"AScene.hh"
#include				"EventManager.hh"
#include				"EMessages.hh"

class					AScene;
class					EventManager;

enum					E_PRIORITY
  {
    HIGH,
    MEDIUM,
    LOW
  };

class					SceneManager
{
public:
  static SceneManager			*getInstance();
  bool					initialize();
  void					uninitialize();
  ~SceneManager();
  void					add(AScene *scene, int priority = MEDIUM);
  AScene				*remove(AScene *scene);
  AScene				*get(std::string const & name);
  void					setVisibleAll(bool val);
  void					setActiveAll(bool val);
  void					setPriority(AScene *scene, int priority);
  void					updateEvent(ALLEGRO_EVENT *event);
  void					drawEvent(ALLEGRO_EVENT *event);
  void					inputEvent(ALLEGRO_EVENT *event);
  void					handleMessage(e_message type, bool activate, std::string const & sceneName);
private:
  SceneManager();
  std::list<AScene*>			collection_;
  typedef std::list<AScene*>::iterator	t_iter;
};

#endif					// __SCENE_MANAGER_HH__
