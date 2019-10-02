#include "Automates.h"

int main() {
    // количество вершин, размер алфавита
    AutomatGraph aut(5, 2);
    // ввод переходов
    aut.add_edge(0, 1, 0);
    aut.add_edge(0, 2, 1);
    aut.add_edge(1, 0, 1);
    aut.add_edge(2, 3, 0);
    aut.add_edge(2, 3, 1);
    aut.add_edge(3, 2, 0);
    aut.add_edge(3, 4, 1);
    // терминальные вершины
    aut.make_terminal(1);
    aut.make_terminal(3);
    aut.make_terminal(4);
    // правильность построения
    aut.show_graph();
    // детерминируем
    DeterminedAutomatGraph daut = determine(aut);
    // смотрим
    daut.show_graph();
    // делаем полным
    DeterminedAutomatGraph fdaut = make_full(daut);
    // смотрим
    fdaut.show_graph();
    // инвертируем
    DeterminedAutomatGraph ifdaut = invert(fdaut);
    //смотрим
    ifdaut.show_graph();
    // делаем минимальным
    DeterminedAutomatGraph mdaut = make_minimal(fdaut);
    // смотрим
    mdaut.show_graph();
}
