#include "end_scene.h"

#include <Windows.h>
#include <conio.h>

#include "end_scene.h";
#include "enemy.h"
#include "fight_manager.h"
#include "forest_scene.h"
#include "global_void.h"
#include "item_game.h"
#include "narrator.h"
#include "start_scene.h"
EndScene::EndScene() {}

void EndScene::Display() {
  Narrator::Load("narrator.json");
  Print(Narrator::GetPhrase("intros.end1"));
  Print(Narrator::GetPhrase("intros.end2"));
  Print(Narrator::GetPhrase("intros.heart_danko"));
  Print(Narrator::GetPhrase("intros.heal_danko"));
  Print(Narrator::GetPhrase("intros.final_end"));
  exit(0);
}
