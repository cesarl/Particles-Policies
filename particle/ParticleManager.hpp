#ifndef					__PARTICLE_MANAGER_HPP__
# define				__PARTICLE_MANAGER_HPP__

#include				<cmath>
#include				"Particle.hh"

template				<size_t size, // number of particle in collection
					 class InitPolicy, // particle initialisation
					 class UpdatePolicy, // particle update
					 class ParticleType> // particle type
class					ParticleGroup
{
public:
  InitPolicy			initPlc;
  UpdatePolicy			updatePlc;

  explicit				ParticleGroup() throw()
    : length_(size),
      cnt_(0)
  {}
  inline void				clear() throw() {
    this->cnt_ = 0;
  }
  inline const ParticleType		*getParticles() const throw()
  {
    if (this->getCounter() == 0)
      {
	return NULL;
      }
    return this->list_;
  }
  inline size_t				getLength() const throw()
  {
    return this->length_;
  }
  inline size_t				getCounter() const throw()
  {
    return this->cnt_;
  }
  void					emit(const size_t &nb, const Vector3d &position)
  {
    size_t				amount;

    amount = nb;
    if ((this->cnt_ + amount) > this->length_)
      {
	amount = this->length_ - this->cnt_;
      }
    if (amount > 0)
      {
	size_t				i;

	i = this->cnt_;
	this->cnt_ += amount;
	for (; i < this->cnt_; ++i)
	  {
	    this->list_[i].position = position;
	    this->initPlc(this->list_[i]);
	  }
      }
  }
  void					update() throw()
  {
    this->updatePlc.prepareAction();
    for (size_t i = 0; i < this->cnt_; i++)
      {
	this->updatePlc(this->list_[i]);
	if (this->list_[i].lifetime <= 0)
	  {
	    this->list_[i] = this->list_[this->cnt_ - 1];
	    --this->cnt_;
	  }
	++i;
      }
  }

  void					draw() throw()
  {
    static ALLEGRO_BITMAP *bmp;

    bmp = ImageManager::getInstance()->load("assets/imgs/point.png");
    for (size_t i = 0; i < this->cnt_; i++)
      {
	al_draw_tinted_scaled_rotated_bitmap(bmp,
					     this->list_[i].color,
					     this->list_[i].center.getX(),
					     this->list_[i].center.getY(),
					     this->list_[i].position.getX(),
					     this->list_[i].position.getY(),
					     this->list_[i].scale.getX(),
					     this->list_[i].scale.getY(),
					     this->list_[i].angle, 0);
      }
  }

private:
  ParticleType				list_[size];
  size_t				length_;
  size_t				cnt_;
};

template				<class ParticleType, class ColorPolicy, class CenterPolicy, class ScalePolicy, class VelocityPolicy, class LifePolicy, class PositionPolicy, class RotationPolicy>
class					CompletePolicy
{
public:
  PositionPolicy			positionPlc;
  ColorPolicy				colorPlc;
  CenterPolicy				centerPlc;
  ScalePolicy				scalePlc;
  VelocityPolicy			velocityPlc;
  LifePolicy				lifePlc;
  RotationPolicy			rotationPlc;

  inline void				prepareAction() throw() {
    this->positionPlc.prepareAction();
    this->velocityPlc.prepareAction();
    this->scalePlc.prepareAction();
    this->centerPlc.prepareAction();
    this->colorPlc.prepareAction();
    this->lifePlc.prepareAction();
    this->rotationPlc.prepareAction();
  }
  inline void				operator() (ParticleType &particle) const throw()
  {
    this->positionPlc(particle);
    this->velocityPlc(particle);
    this->scalePlc(particle);
    this->centerPlc(particle);
    this->colorPlc(particle);
    this->lifePlc(particle);
    this->rotationPlc(particle);
  }
};

template				<class ParticleType>
class					LifeInitializer
{
public:
  int					minimumLife;
private:
  int					lifeRange_;
public:
  inline void				setLifeRange(const int & minLife, const int & maximumLife) throw()
  {
    this->minimumLife = minLife;
    this->lifeRange_ = maximumLife + 1 - this->minimumLife;
  }
  explicit				LifeInitializer() throw() :
    minimumLife(0),
    lifeRange_(0)
  {}
  inline void				operator()(ParticleType & particle) const throw()
  {
    particle.lifetime = this->minimumLife + rand() % this->lifeRange_;
  }
};

template				<class ParticleType>
class					ColorInitializer
{
public:
  explicit				ColorInitializer() throw()
  {}
  inline void				operator()(ParticleType & particle) const throw()
  {
    particle.color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);
  }
};

template				<class ParticleType>
class					CenterInitializer
{
public:
  Vector3d				center;
public:
  inline void				setCenter(const Vector3d & s) throw()
  {
    this->center = s;
  }
  explicit				CenterInitializer() throw() :
    center(Vector3d(20, 20, 0))
  {}
  inline void				operator()(ParticleType & particle) const throw()
  {
    particle.center = this->center;
  }
};

template				<class ParticleType>
class					ScaleInitializer
{
public:
  Vector3d				scale;
public:
  inline void				setScale(const Vector3d & s) throw()
  {
    this->scale = s;
  }
  explicit				ScaleInitializer() throw() :
    scale(Vector3d(1.0f, 1.0f, 0.0f))
  {}
  inline void				operator()(ParticleType & particle) const throw()
  {
    particle.scale = this->scale;
  }
};


template				<class ParticleType>
class					VelocityInitializer
{
public:
  explicit				VelocityInitializer() throw()
  {}
  inline void				operator()(ParticleType & particle) const throw()
  {
    particle.velocity = Vector3d((-20 + (rand() % 40)) / 10.0f, (-20 + (rand() % 40)) / 10.0f, 0.0f);
  }
};

template				<class ParticleType>
class					RotationInitializer
{
public:
  explicit				RotationInitializer() throw()
  {}
  inline void				operator()(ParticleType & particle) const throw()
  {
    particle.angle = (rand() % 20) / 10.0f;
    particle.rotationForce = (rand() % 3) / 10.0f;
  }
};


template				<class ParticleType>
class					GravityAction
{
public:
  Vector3d				gravity;
public:
  explicit				GravityAction() throw() :
    gravity(Vector3d(0.0f, 0.0f, 0.0f))
  {}
  inline void				prepareAction() throw()
  {}
  inline void				operator()(ParticleType &particle) const throw()
  {
    particle.velocity += this->gravity;
  }
};

template				<class ParticleType>
class					MoveAction
{
public:
  inline void				prepareAction() throw() {}
  inline void				operator()(ParticleType &particle) const throw()
  {
    particle.position += particle.velocity;
  }
};


template				<class ParticleType>
class					CenterAction
{
public:
  inline void				prepareAction() throw() {}
  inline void				operator()(ParticleType &particle) const throw()
  {
    (void)particle;
  }
};

template				<class ParticleType>
class					ScaleAction
{
public:
  inline void				prepareAction() throw() {}
  inline void				operator()(ParticleType &particle) const throw()
  {
    particle.scale -= Vector3d(0.01f, 0.01f, 0.0f);
  }
};

template				<class ParticleType>
class					ColorAction
{
public:
  inline void				prepareAction() throw() {}
  inline void				operator()(ParticleType &particle) const throw()
  {
    float r, g, b, a;
    al_unmap_rgba_f(particle.color, &r, &g, &b, &a);
    a -= 0.005;
    particle.color = al_map_rgba_f(r, g, b, a);
    if (a <= 0.0f)
      particle.lifetime = -1;
    (void)particle;
  }
};

template				<class ParticleType>
class					LifeAction
{
public:
  int					lifeless;
  inline void				prepareAction() throw() {}
  inline void				operator()(ParticleType &particle) const throw()
  {
    particle.lifetime -= this->lifeless;
  }
};

template				<class ParticleType>
class					RotationAction
{
public:
  inline void				prepareAction() throw() {}
  inline void				operator()(ParticleType &particle) const throw()
  {
    particle.rotationForce -= 0.0005f;
    if (particle.rotationForce <= 0.0f)
      return;
    particle.angle += particle.rotationForce;
    if (particle.angle > 6.2f)
      particle.angle = 0.0f;
    if (particle.angle < 0.0f)
      particle.angle = 6.2f;
  }
};

////////////////
// NULLPOLICY //
////////////////

template				<class ParticleType>
class					NullPolicy
{
public:
  inline void				prepareAction() throw() {}
  inline void				operator()(ParticleType &particle) const throw()
  {
    (void)particle;
  }
};


#endif					// __PARTICLE_MANAGER_HPP__
