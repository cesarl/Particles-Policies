#ifndef					__SCENE_PAUSE_HH__
# define				__SCENE_PAUSE_HH__

#include				<iostream> // for debug - to clear
#include				"AScene.hh"
#include				"ParticleManager.hpp"

class					MainScene : public AScene
{
public:
  MainScene();
  ~MainScene();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
  virtual bool				initialize();
  virtual void				uninitialize();
private: //variables
  ParticleGroup<5000,
		CompletePolicy< Particle,
				ColorInitializer<Particle>,
				SizeInitializer<Particle>,
				VelocityInitializer<Particle>,
				LifeInitializer<Particle>,
				NullPolicy<Particle> >,
		CompletePolicy< Particle,
				ColorAction<Particle>,
				SizeAction<Particle>,
				NullPolicy<Particle>, //GravityAction<Particle>,
				LifeAction<Particle>,
				GravityAction<Particle> >,
		Particle>
  particles_;
};

#endif					// __SCENE_PAUSE_HH__
