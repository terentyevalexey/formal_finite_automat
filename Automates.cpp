#include "Automates.h"


DeterminedAutomatGraph determine(const AutomatGraph& UFA) {
    DeterminedAutomatGraph DFA(1, UFA.alphabetSize);
    if (UFA.is_terminal(0))
        DFA.make_terminal(0);
    std::vector<std::unordered_set<unsigned>> new_verts({ {0} });
    for (unsigned cur_verts_num = 0; cur_verts_num < new_verts.size(); ++cur_verts_num) {
        std::unordered_set<unsigned> cur_verts = new_verts[cur_verts_num];
        //рассматриваем подмножество исходных вершин, которое ещё не рассмотрели
        for (unsigned symbol = 0; symbol < UFA.alphabetSize; ++symbol) {
            //рассматриваем все возможные переходы
            std::unordered_set<unsigned> nxt_verts;
            bool nxt_is_terminal = false;
            for (auto cur_vert : cur_verts) {
                for (auto nxt_vert : UFA.get_nxt(cur_vert, symbol)) {
                    nxt_verts.insert(nxt_vert);
                    if (UFA.is_terminal(nxt_vert))
                        nxt_is_terminal = true;
                }
            }
            if (nxt_verts.empty())
                DFA.add_edge(cur_verts_num, UINT_MAX, symbol);
            else {
                //проверяем, рассматривали ли мы такое подмножество
                bool is_new = true;
                for (unsigned verts_num = 0; verts_num < new_verts.size(); ++verts_num)
                    if (new_verts[verts_num] == nxt_verts) {
                        is_new = false;
                        DFA.add_edge(cur_verts_num, verts_num, symbol);
                        break;
                    }
                if (is_new) {
                    new_verts.push_back(nxt_verts);
                    DFA.add_vertice();
                    if (nxt_is_terminal)
                        DFA.make_terminal(DFA.vertices_count() - 1);
                    DFA.add_edge(cur_verts_num, DFA.vertices_count() - 1, symbol);
                }
            }
        }
    }
    return DFA;
}

DeterminedAutomatGraph make_full(const DeterminedAutomatGraph& DFA) {
    DeterminedAutomatGraph FDFA(DFA);
    bool is_full = true;
    for (unsigned cur_vert = 0; cur_vert < FDFA.vertices_count(); ++cur_vert) {
        for (unsigned symbol = 0; symbol < FDFA.alphabetSize; ++symbol) {
            unsigned nxt_vert = FDFA.get_nxt(cur_vert, symbol);
            if (nxt_vert == UINT_MAX) {
                if (is_full) {
                    is_full = false;
                    FDFA.add_vertice();
                }
                FDFA.add_edge(cur_vert, FDFA.vertices_count() - 1, symbol);
            }
        }
    }
    return FDFA;
}

DeterminedAutomatGraph invert(const DeterminedAutomatGraph& FDFA) {
    DeterminedAutomatGraph IFDFA(FDFA);
    IFDFA.clear_terminal();
    for (unsigned i = 0; i < FDFA.vertices_count(); ++i)
        if (!FDFA.is_terminal(i))
            IFDFA.make_terminal(i);
    return IFDFA;
}

DeterminedAutomatGraph make_minimal(const DeterminedAutomatGraph& FDFA) {
    std::vector<unsigned> prev_eq;
    for (unsigned i = 0; i < FDFA.vertices_count(); ++i)
        if (FDFA.is_terminal(i))
            prev_eq.push_back(1);
        else
            prev_eq.push_back(0);
    unsigned not_changed_for = 0;
    unsigned total_components;
    while (not_changed_for < FDFA.alphabetSize) {
        for (unsigned symbol = 0; symbol < FDFA.alphabetSize; ++symbol) {
            std::vector<unsigned> nxt_eq;
            for (unsigned i = 0; i < FDFA.vertices_count(); ++i)
                nxt_eq.push_back(prev_eq[FDFA.get_nxt(i, symbol)]);
            //теперь посчитаем состояния
            std::vector<std::pair<unsigned, unsigned>> components;
            components.emplace_back(prev_eq[0], nxt_eq[0]);
            nxt_eq[0] = 0;
            for (unsigned i = 1; i < FDFA.vertices_count(); ++i) {
                bool is_new = true;
                for (unsigned j = 0; j < components.size(); ++j)
                    if (components[j] == std::make_pair(prev_eq[i], nxt_eq[i])) {
                        nxt_eq[i] = j;
                        is_new = false;
                    }
                if (is_new) {
                    components.emplace_back(prev_eq[i], nxt_eq[i]);
                    nxt_eq[i] = components.size() - 1;
                }
            }
            total_components = components.size();
            if (prev_eq == nxt_eq)
                ++not_changed_for;
            else {
                not_changed_for = 0;
                prev_eq = nxt_eq;
            }
        }
    }

    DeterminedAutomatGraph MDFA(total_components, FDFA.alphabetSize);
    for (unsigned i = 0; i < FDFA.vertices_count(); ++i) {
        if (FDFA.is_terminal(i))
            MDFA.make_terminal(prev_eq[i]);
        for (unsigned j = 0; j < FDFA.alphabetSize; ++j)
            if (FDFA.get_nxt(i, j) != UINT_MAX)
                MDFA.add_edge(prev_eq[i], prev_eq[FDFA.get_nxt(i, j)], j);
    }
    return MDFA;
}