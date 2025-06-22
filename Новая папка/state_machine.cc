#include "state_machine.h"
void StateMachine::PushScene(std::unique_ptr<Scene> scene) {
  scenes_.push(std::move(scene));
}

void StateMachine::PopScene() { scenes_.pop(); }

void StateMachine::ChangeScene(std::unique_ptr<Scene> scene) {
  scenes_.pop();
  scenes_.push(std::move(scene));
}

Scene* StateMachine::GetCurrentScene() {
  if (!scenes_.empty()) {
    return scenes_.top().get();
  }
  return nullptr;
}
