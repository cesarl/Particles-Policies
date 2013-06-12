#ifndef					__VECTOR3D_H__
#define					__VECTOR3D_H__

class					Vector3d
{
private:
  double _x, _y, _z;
public:
  Vector3d();
  Vector3d(const Vector3d& other);
  Vector3d(double x, double y, double z);
  Vector3d(int x, int y, int z);
  ~Vector3d();

  void					set(double x,double y,double z);
  void					set(const Vector3d& other);
  double				getX() const { return this->_x; }
  void					setX(double v) { this->_x = v; }
  double				getY() const { return this->_y; }
  void					setY(double v) { this->_y = v; }
  double				getZ() const { return this->_z; }
  void					setZ(double v) { this->_z = v; }
  void					move(double mx, double my, double mz);
  void					operator+=(const Vector3d& other);
  void					operator-=(const Vector3d& other);
  void					operator*=(const Vector3d& other);
  void					operator/=(const Vector3d& other);
  bool					operator==(const Vector3d& other) const;
  bool					operator!=(const Vector3d& other) const;
  Vector3d				&operator=(const Vector3d& other);
};

#endif					// __VECTOR3D_H__
