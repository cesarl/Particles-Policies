#include				"AScene.hh"

AScene::AScene(std::string const & name, bool active, bool visible) :
  name_(name), active_(active), visible_(visible), sceneManager_(NULL)
{}

AScene::~AScene()
{}

std::string const &			AScene::getName() const
{
  return this->name_;
}

bool					AScene::getActive() const
{
  return this->active_;
}

bool					AScene::getVisible() const
{
  return this->visible_;
}

int					AScene::getPriority() const
{
  return this->priority_;
}

void					AScene::setName(std::string const name)
{
  this->name_ = name;
}

void					AScene::setActive(bool active)
{
  this->active_ = active;
}

void					AScene::setVisible(bool visible)
{
  this->visible_ = visible;
}

void					AScene::setPriority(int priority)
{
  this->priority_ = priority;
}

void					AScene::setManager(SceneManager *manager)
{
  this->sceneManager_ = manager;
}

void					AScene::sendMessage(e_message type, bool activate, std::string const & sceneName)
{
  if (this->sceneManager_)
    this->sceneManager_->handleMessage(type, activate, sceneName);
}
