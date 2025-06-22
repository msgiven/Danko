#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
class Scene {
 public:
  virtual ~Scene() = default;
  virtual void Display() = 0;
};

#endif
