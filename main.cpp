#include                                <allegro5/allegro.h>
#include				"MainScene.hh"
#include				"MainManager.hh"

int					main()
{
  if (!MainManager::getInstance()->initialize(50 * 20, 50 * 20))
    return -1;

  MainScene				mainScene;
  SceneManager				*sceneManager;
  EventManager				*eventManager;

  ImageManager::getInstance()->load("assets/imgs/stars.png");

  eventManager = EventManager::getInstance();
  sceneManager = SceneManager::getInstance();

  sceneManager->add(&mainScene);
  mainScene.setActive(true);
  mainScene.setVisible(true);
  mainScene.setName("mainScene");

  sceneManager->initialize();

  eventManager->play();
  MainManager::getInstance()->deInitialize();
  return (1);
}
