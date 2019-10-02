#include "Automates.h"

int main() {
    // ���������� ������, ������ ��������
    AutomatGraph aut(5, 2);
    // ���� ���������
    aut.add_edge(0, 1, 0);
    aut.add_edge(0, 2, 1);
    aut.add_edge(1, 0, 1);
    aut.add_edge(2, 3, 0);
    aut.add_edge(2, 3, 1);
    aut.add_edge(3, 2, 0);
    aut.add_edge(3, 4, 1);
    // ������������ �������
    aut.make_terminal(1);
    aut.make_terminal(3);
    aut.make_terminal(4);
    // ������������ ����������
    aut.show_graph();
    // �������������
    DeterminedAutomatGraph daut = determine(aut);
    // �������
    daut.show_graph();
    // ������ ������
    DeterminedAutomatGraph fdaut = make_full(daut);
    // �������
    fdaut.show_graph();
    // �����������
    DeterminedAutomatGraph ifdaut = invert(fdaut);
    //�������
    ifdaut.show_graph();
    // ������ �����������
    DeterminedAutomatGraph mdaut = make_minimal(fdaut);
    // �������
    mdaut.show_graph();
}
