#include "AutomatGraph.h"

DeterminedAutomatGraph::DeterminedAutomatGraph(unsigned vertcnt, unsigned max_vert_out_degree) :
    verticesList(vertcnt, std::vector<unsigned>(max_vert_out_degree, UINT_MAX)),
    alphabetSize(max_vert_out_degree) {}

void DeterminedAutomatGraph::make_terminal(unsigned vert) {
    terminals.insert(vert);
}

void DeterminedAutomatGraph::clear_terminal() {
    terminals.clear();
}

bool DeterminedAutomatGraph::is_terminal(unsigned vert) const {
    return (terminals.find(vert) != terminals.end());
}

void DeterminedAutomatGraph::add_vertice() {
    verticesList.emplace_back(alphabetSize, UINT_MAX);
}

void DeterminedAutomatGraph::add_edge(unsigned from, unsigned to, unsigned weight) {
    verticesList[from][weight] = to;
}

unsigned DeterminedAutomatGraph::vertices_count() const {
    return verticesList.size();
}

unsigned DeterminedAutomatGraph::get_nxt(unsigned from, unsigned weight) const {
    return verticesList[from][weight];
}

void DeterminedAutomatGraph::show_graph() const {
    for (unsigned i = 0; i < vertices_count(); ++i) {
        if (is_terminal(i))
            std::cout << std::setw(3) << i << "x" << "|";
        else
            std::cout << std::setw(4) << i << "|";
        for (auto nxt_vert : verticesList[i]) {
            if (nxt_vert != UINT_MAX)
                if (is_terminal(nxt_vert))
                    std::cout << std::setw(3) << nxt_vert << "x";
                else
                    std::cout << std::setw(4) << nxt_vert;
            else
                std::cout << "    ";
            std::cout << "|";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

AutomatGraph::AutomatGraph(unsigned vertcnt, unsigned max_vert_out_degree) :
    verticesList(vertcnt, std::vector<std::vector<unsigned>>(max_vert_out_degree)),
    alphabetSize(max_vert_out_degree) {
}

void AutomatGraph::make_terminal(unsigned vert) {
    terminals.insert(vert);
}

bool AutomatGraph::is_terminal(unsigned vert) const {
    return (terminals.find(vert) != terminals.end());
}

void AutomatGraph::add_vertice() {
    verticesList.emplace_back(alphabetSize);
}

void AutomatGraph::add_edge(unsigned from, unsigned to, unsigned weight) {
    verticesList[from][weight].push_back(to);
}

unsigned AutomatGraph::vertices_count() const {
    return verticesList.size();
}

std::vector<unsigned> AutomatGraph::get_nxt(unsigned from, unsigned weight) const {
    return verticesList[from][weight];
}

void AutomatGraph::show_graph() const {
    for (unsigned i = 0; i < vertices_count(); ++i) {        
        if (is_terminal(i))
            std::cout << std::setw(3) << i << "x" << "|";
        else
            std::cout << std::setw(4) << i << "|";
        for (unsigned symbol = 0; symbol < verticesList[i].size(); ++symbol)
            for (auto nxt_vert : verticesList[i][symbol]) {
                if (is_terminal(nxt_vert))
                    std::cout << symbol << ":" << std::setw(3) << nxt_vert << "x";
                else
                    std::cout << symbol << ":" << std::setw(4) << nxt_vert;
                std::cout << "|";
            }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
