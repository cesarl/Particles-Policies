#ifndef					__EVENT_MANAGER_HH__
# define				__EVENT_MANAGER_HH__

#include                                <allegro5/allegro.h>
#include				<iostream>
#include				<list>
#include				<algorithm>
#include				"SceneManager.hh"
#include				"OptionManager.hpp"
#include				"FontManager.hh"

class					SceneManager;
class					Input;

class					EventManager
{
public:
  ~EventManager();
  static EventManager			*getInstance();
  bool					initialize();
  void					uninitialize();
  void					play();
  void					stop();
  void					setSceneManager(SceneManager * sceneManager);
private:
  ALLEGRO_EVENT_QUEUE			*event_queue_;
  ALLEGRO_TIMER				*timer_;
  SceneManager				*sceneManager_;
  OptionValue<bool>			*run_;
  EventManager();
};

#endif					// __EVENT_MANAGER_HH__

