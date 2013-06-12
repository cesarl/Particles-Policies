#include				"MainManager.hh"

MainManager::MainManager() :
  display_(NULL)
{}

MainManager::~MainManager()
{}

MainManager				*MainManager::getInstance()
{
  static MainManager			that;
  return &that;
}

bool					MainManager::initialize(int width, int height)
{
  if (!al_init())
    return false;
  this->display_ = al_create_display(width, height);
  if (!this->display_)
    return false;
  if (!EventManager::getInstance()->initialize())
    return false;
  if (!FontManager::getInstance()->initialize())
    return false;
  if (!ImageManager::getInstance()->initialize())
    return false;
  return true;
}

void					MainManager::deInitialize()
{
  ImageManager::getInstance()->uninitialize();
  FontManager::getInstance()->uninitialize();
  EventManager::getInstance()->uninitialize();
  SceneManager::getInstance()->uninitialize();
  if (this->display_)
    al_destroy_display(this->display_);
  al_uninstall_system();
}
