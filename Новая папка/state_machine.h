#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_
#include <memory>
#include <stack>

#include "fight_manager.h"
#include "player.h"
#include "scene.h"
class StateMachine {
 public:
  void ChangeScene(std::unique_ptr<Scene> scene);
  Scene* GetCurrentScene();
  void PushScene(std::unique_ptr<Scene> scene);

 private:
  std::stack<std::unique_ptr<Scene>> scenes_;
  void PopScene();
};
#endif
