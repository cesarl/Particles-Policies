#ifndef				__PARTICLE_HH__
# define			__PARTICLE_HH__

#include			<allegro5/allegro.h>
#include			"Vector3d.hh"
#include			"ImageManager.hh"

struct				Particle
{
  Vector3d			position;
  Vector3d			velocity;
  ALLEGRO_COLOR			color;
  Vector3d			center;
  Vector3d			scale;
  int				lifetime;
  float				angle;
  float				rotationForce;
};

#endif				// __PARTICLE_HH__
