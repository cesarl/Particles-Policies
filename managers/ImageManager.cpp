#include				"ImageManager.hh"

//ctor

ImageManager::ImageManager()
{
}

//dtor

ImageManager::~ImageManager()
{
}

bool					ImageManager::initialize()
{
  if (!al_init_image_addon())
    return false;
  return true;
}

void					ImageManager::uninitialize()
{
  t_iter				it;

  for (it = this->collection_.begin(); it != this->collection_.end(); ++it)
    {
      al_destroy_bitmap(it->second);
      this->collection_.erase(it);
    }
  al_shutdown_image_addon();
}

ImageManager				*ImageManager::getInstance()
{
  static ImageManager			that;
  return &that;
}

// load an image

ALLEGRO_BITMAP				*ImageManager::load(std::string const & path)
{
  ALLEGRO_BITMAP			*tmp;

  if ((tmp = this->get(path)))
    return tmp;
  tmp = al_load_bitmap(path.c_str());
  if (!tmp)
    {
      std::cerr << "Error - ImageManager : loading " << path << " failed" << std::endl;
      return NULL;
    }
  this->collection_.insert(t_pair(path, tmp));
  return tmp;
}

//free an image and delete it of the collection

void					ImageManager::erase(std::string const & path)
{
  t_iter				it;

  it = this->collection_.find(path);
  if (it != this->collection_.end())
    {
      al_destroy_bitmap(it->second);
      this->collection_.erase(it);
    }
}

//return an image

ALLEGRO_BITMAP				*ImageManager::get(std::string const & path)
{
  t_iter				it;

  it = this->collection_.find(path);
  if (it != this->collection_.end())
    return it->second;
  return NULL;
}

//load a list of image

bool					ImageManager::loadList(std::list<std::string> const & list)
{
  std::list<std::string>::const_iterator it = list.begin();
  bool					ret = true;

  for (; it != list.end(); ++it)
    {
      if(!this->load(*it))
	ret = false;
    }
  return ret;
}

//load all images in a directory

bool					ImageManager::loadDirectory(std::string const & path)
{
  ALLEGRO_FS_ENTRY			*cur;
  ALLEGRO_FS_ENTRY			*l;
  bool					ret = true;

  cur = al_create_fs_entry(path.c_str());
  if (!cur || !al_open_directory(cur))
    {
      std::cerr << "Error - ImageManager : load directory " << path << " error" << std::endl;
      return false;
    }
  while ((l = al_read_directory(cur)) != NULL)
    {
      if (!this->load(al_get_fs_entry_name(l)))
	ret = false;
    }
  return ret;
}

//relaod all images

void					ImageManager::refresh()
{
  t_iter				it;
  ALLEGRO_BITMAP			*tmp;

  for (it = this->collection_.begin(); it != this->collection_.end(); ++it)
    {
      tmp = al_load_bitmap(it->first.c_str());
      if (!tmp)
	{
	  std::cerr << "Error - ImageManager : loading " << it->first << " failed" << std::endl;
	  this->collection_.erase(it);
	}
      al_destroy_bitmap(it->second);
      it->second = tmp;
    }
}
