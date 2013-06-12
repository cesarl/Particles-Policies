#include				"IdManager.hh"

IdManager::IdManager() : lastId_(0)
{}

IdManager::~IdManager()
{}

IdManager				*IdManager::getInstance()
{
  static IdManager			that;
  return &that;
}

int					IdManager::inc()
{
  this->lastId_++;
  return this->lastId_;
}

int					IdManager::newId()
{
  return this->inc();
}
