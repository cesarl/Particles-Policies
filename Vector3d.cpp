#include				<math.h>
#include				"Vector3d.hh"

Vector3d::Vector3d() : _x(0), _y(0), _z(0)
{}

Vector3d::Vector3d(const Vector3d& other)
{
  *this = other;
}

Vector3d::Vector3d(double x, double y, double z)
{
  this->set(x, y, z);
}

Vector3d::Vector3d(int x, int y, int z)
{
  this->set((double)x, (double)y, (double)z);
}

Vector3d::~Vector3d()
{}

void					Vector3d::set(double x,double y,double z)
{
  this->_x = x;
  this->_y = y;
  this->_z = z;
}

void					Vector3d::set(const Vector3d& other)
{
  this->_x = other._x;
  this->_y = other._y;
  this->_z = other._z;
}

void					Vector3d::move(double mx, double my, double mz)
{
  this->_x += mx;
  this->_y += my;
  this->_z += mz;
}

void					Vector3d::operator+=(const Vector3d& other)
{
  this->_x += other._x;
  this->_y += other._y;
  this->_z += other._z;
}

void					Vector3d::operator-=(const Vector3d& other)
{
  this->_x -= other._x;
  this->_y -= other._y;
  this->_z -= other._z;
}

void					Vector3d::operator*=(const Vector3d& other)
{
  this->_x *= other._x;
  this->_y *= other._y;
  this->_z *= other._z;
}

void					Vector3d::operator/=(const Vector3d& other)

{
  this->_x /= other._x;
  this->_y /= other._y;
  this->_z /= other._z;
}

bool					Vector3d::operator==(const Vector3d& other) const
{
  return (
	  (((other._x - 0.0001f) < this->_x) && (this->_x < (other._x + 0.0001f))) &&
	  (((other._y - 0.0001f) < this->_y) && (this->_y < (other._y + 0.0001f))) &&
	  (((other._z - 0.0001f) < this->_z) && (this->_z < (other._z + 0.0001f))) );
}

bool					Vector3d::operator!=(const Vector3d& other) const
{
  return (!(*this == other));
}

Vector3d				&Vector3d::operator=(const Vector3d& other)
{
  this->set(other);
  return *this;
}
