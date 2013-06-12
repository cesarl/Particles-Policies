#ifndef					__ID_MANAGER_H__
# define				__ID_MANAGER_H__

class					IdManager
{
public:
  ~IdManager();
  int					newId();
  static IdManager			*getInstance();
private:
  int					inc();
  IdManager();
  int					lastId_;
};

#endif					// __ID_MANAGER_H__
