#include				"EventManager.hh"

EventManager::EventManager() :
  event_queue_(NULL),
  timer_(NULL),
  sceneManager_(NULL)
{
  OptionManager::getInstance()->setOption<bool>("run", true);
  this->run_ = OptionManager::getInstance()->getOption<bool>("run");
}

EventManager::~EventManager()
{
}

bool					EventManager::initialize()
{
  if (!al_install_keyboard())
    return false;
  if (!al_install_mouse())
    return false;
  this->event_queue_ = al_create_event_queue();
  if (!this->event_queue_)
    return false;
  this->timer_ = al_create_timer(1.0 / 60);
  if (!this->timer_)
    return false;

  al_register_event_source(this->event_queue_, al_get_keyboard_event_source());
  al_register_event_source(this->event_queue_, al_get_mouse_event_source());
  al_register_event_source(this->event_queue_, al_get_display_event_source(al_get_current_display()));
  al_register_event_source(this->event_queue_, al_get_timer_event_source(this->timer_));
  al_start_timer(this->timer_);

  this->sceneManager_ = SceneManager::getInstance();
  return true;
}

void					EventManager::uninitialize()
{
  if (this->event_queue_)
    al_destroy_event_queue(this->event_queue_);
  if (this->timer_)
    al_destroy_timer(this->timer_);
  al_uninstall_keyboard();
  al_uninstall_mouse();
}


void					EventManager::play()
{
  bool					draw;
  double				fps = 0;
  int					frames_done = 0;
  double				old_time = al_get_time();

  if (!this->sceneManager_)
    {
      std::cerr << "Error : Event Manager - SceneManager has not been linked" << std::endl;
      return;
    }
  this->run_->setValue(true);
  while (this->run_->getValue())
    {
      ALLEGRO_EVENT			ev;

      draw = false;
      al_wait_for_event(this->event_queue_, &ev);

      if (ev.type == ALLEGRO_EVENT_TIMER)
	{
	  draw = true;
	  this->sceneManager_->updateEvent(&ev);
	}
      else
	this->sceneManager_->inputEvent(&ev);
      if (draw && al_is_event_queue_empty(this->event_queue_))
	{
	  al_clear_to_color(al_map_rgb(0,0,0));
	  this->sceneManager_->drawEvent(&ev);
	  al_flip_display();


	  double game_time = al_get_time();
	  if(game_time - old_time >= 1.0)
	    {
	      fps = frames_done / (game_time - old_time);
	      frames_done = 0;
	      old_time = game_time;
	      std::cout << fps << std::endl;
	    }
	  frames_done++;
	}
      if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
	  this->stop();
	}
    }
}

void					EventManager::stop()
{
  this->run_->setValue(false);
}

EventManager				*EventManager::getInstance()
{
  static EventManager			that;
  return &that;
}
