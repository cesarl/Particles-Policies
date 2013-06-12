#include				"FontManager.hh"

//ctor

FontManager::FontManager()
{
}

//dtor

FontManager::~FontManager()
{}


bool					FontManager::initialize()
{
  al_init_font_addon();
  if (!al_init_ttf_addon())
    return false;
  return true;
}

void					FontManager::uninitialize()
{
  t_iter				it;

  for (it = this->collection_.begin(); it != this->collection_.end(); ++it)
    {
      al_destroy_font(it->second);
      this->collection_.erase(it);
    }
  // cause segfault
  // al_shutdown_ttf_addon();
  al_shutdown_font_addon();
}


FontManager				*FontManager::getInstance()
{
  static FontManager			that;
  return &that;
}

// load a font

ALLEGRO_FONT				*FontManager::load(std::string const & path, int size)
{
  ALLEGRO_FONT				*tmp;
  std::stringstream			key;

  key << path << "-" << size;
  if ((tmp = this->get(path, size)))
    return tmp;
  tmp = al_load_font(path.c_str(), size, 0);
  if (!tmp)
    {
      std::cerr << "Error - FontManager : loading " << key.str() << " failed" << std::endl;
      return NULL;
    }
  this->collection_.insert(t_pair(key.str(), tmp));
  return tmp;
}

//free a font and delete it of the collection

void					FontManager::erase(std::string const & path, int size)
{
  t_iter				it;
  std::string				key;

  key = path;
  key += "-";
  key += size;
  it = this->collection_.find(key);
  if (it != this->collection_.end())
    {
      al_destroy_font(it->second);
      this->collection_.erase(it);
    }
}

//return a font

ALLEGRO_FONT				*FontManager::get(std::string const & path, int size)
{
  t_iter				it;
  std::string				key;

  key = path;
  key += "-";
  key += size;
  it = this->collection_.find(path);
  if (it != this->collection_.end())
    return it->second;
  return NULL;
}
