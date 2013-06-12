#ifndef					__PARTICLE_MANAGER_HPP__
# define				__PARTICLE_MANAGER_HPP__

#include				<cmath>
#include				"Particle.hh"

template				<size_t size, class InitializePolicy, class ActionPolicy, class ParticleType>
class					ParticleGroup
{
public:
  InitializePolicy			initializePolicy;
  ActionPolicy				actionPolicy;

  explicit				ParticleGroup() throw(): currentCount(0) {}
  inline void				clear() throw() {
    currentCount = 0;
  }
  inline const ParticleType		*getParticles() const throw()
  {
    if (particleCount() == 0)
      {
	return NULL;
      }
    return this->particlearray;
  }
  inline size_t				maxParticles() const throw()
  {
    return size;
  }
  inline size_t				particleCount() const throw()
  {
    return this->currentCount;
  }
  void					emit(const size_t &nb, const Vector3d &position)
  {
    size_t				amount;

    amount = nb;
    if ((this->particleCount() + amount) > this->maxParticles())
      {
	amount = this->maxParticles() - this->particleCount();
      }
    if (amount > 0)
      {
	size_t				cnt;

	cnt = this->currentCount;
	this->currentCount += amount;
	for (; cnt < this->currentCount; ++cnt)
	  {
	    this->particlearray[cnt].position = position;
	    this->initializePolicy(this->particlearray[cnt]);
	  }
      }
  }
  void					update() throw()
  {
    this->actionPolicy.prepareAction();
    for (size_t cnt = 0; cnt < this->currentCount; cnt++)
      {
	this->actionPolicy(this->particlearray[cnt]);
	if (this->particlearray[cnt].lifetime <= 0)
	  {
	    this->particlearray[cnt] = this->particlearray[this->currentCount - 1];
	    --this->currentCount;
	  }
++cnt;
      }
  }

  void					draw() throw()
  {
    static ALLEGRO_BITMAP *bmp;

    bmp = ImageManager::getInstance()->load("assets/imgs/point.png");
    for (size_t cnt = 0; cnt < this->currentCount; cnt++)
      {
	al_draw_tinted_scaled_rotated_bitmap(bmp,
					     this->particlearray[cnt].color,
					     this->particlearray[cnt].center.getX(),
					     this->particlearray[cnt].center.getY(),
					     this->particlearray[cnt].position.getX(),
					     this->particlearray[cnt].position.getY(),
					     this->particlearray[cnt].scale.getX(),
					     this->particlearray[cnt].scale.getY(),
					     0, 0);
	++cnt;
      }
  }

private:
  ParticleType				particlearray[size];
  size_t				currentCount;
};

template				<class ParticleType, class ColorPolicy, class CenterPolicy, class ScalePolicy, class VelocityPolicy, class LifePolicy, class PositionPolicy>
class					CompletePolicy
{
public:
  PositionPolicy			positionPlc;
  ColorPolicy				colorPlc;
  CenterPolicy				centerPlc;
  ScalePolicy				scalePlc;
  VelocityPolicy			velocityPlc;
  LifePolicy				lifePlc;

  inline void				prepareAction() throw() {
    this->positionPlc.prepareAction();
    this->velocityPlc.prepareAction();
    this->scalePlc.prepareAction();
    this->centerPlc.prepareAction();
    this->colorPlc.prepareAction();
    this->lifePlc.prepareAction();
  }
  inline void				operator() (ParticleType &particle) const throw()
  {
    this->positionPlc(particle);
    this->velocityPlc(particle);
    this->scalePlc(particle);
    this->centerPlc(particle);
    this->colorPlc(particle);
    this->lifePlc(particle);
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
    a -= 0.009;
    particle.color = al_map_rgba_f(r, g, b, a);
    // if (a <= 0.0f)
    //   particle.lifetime = 0;
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
