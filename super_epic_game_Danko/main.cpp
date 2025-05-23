#include "player.h"
#include "fight.h"
#include <iostream>
#include <locale>

int main() {
    setlocale(LC_ALL, "ru");

    Player player(100);
    Fight fight(25, 3);

    std::cout << "Игра началась! Будьте готовы к последовательностям стрелок." << std::endl;
    std::cout << "Управление: W, S, A, D" << std::endl;
    std::cout << "У вас есть 3 секунды на ввод!" << std::endl;

    while (player.isAlive()) {
        if (!fight.playRound(player)) break;

        std::cout << "Готовы к следующему раунду? (Нажмите Enter...)";
        std::cin.ignore();
        //std::cin.get();
    }

    std::cout << "Игра окончена! Вы проиграли." << std::endl;
    return 0;
}