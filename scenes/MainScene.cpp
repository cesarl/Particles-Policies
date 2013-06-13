#include				"MainScene.hh"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{}

void					MainScene::update(ALLEGRO_EVENT *event)
{
  this->particles_.emit(10, Vector3d(500, 100, 0));
  this->particles_.update();
  (void)(event);
}

void					MainScene::draw(ALLEGRO_EVENT *event)
{
  this->particles_.draw();
  (void)(event);
}

void					MainScene::input(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					MainScene::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

bool					MainScene::initialize()
{
  // at init : life range - between 10 and 100 iterations
  this->particles_.initPlc.lifePlc.setLifeRange(100, 300);
  // at init : center of particle
  this->particles_.initPlc.centerPlc.center = Vector3d(40, 40, 0);

  // at intit : color of particles
  // this->particles_.initializePolicy.colorPlc.color = al_map_rgba(255, 0, 255, 255);

  // at update : particle lose X unity of life
  this->particles_.updatePlc.lifePlc.lifeless = 1;

  // at update : particle velocity add gravity of X
  this->particles_.updatePlc.positionPlc.gravity = Vector3d(0.0f, 0.03f, 0.0f);
  return true;
}

void					MainScene::uninitialize()
{
}
