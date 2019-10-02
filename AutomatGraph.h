#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <unordered_set>
#include <iomanip>

class DeterminedAutomatGraph {
    std::vector<std::vector<unsigned>> verticesList;
    std::unordered_set<unsigned> terminals;
public:
    unsigned alphabetSize;

    DeterminedAutomatGraph(unsigned vertcnt, unsigned max_vert_out_degree);

    void make_terminal(unsigned vert);

    void clear_terminal();

    bool is_terminal(unsigned vert) const;

    void add_vertice();

    void add_edge(unsigned from, unsigned to, unsigned weight);

    unsigned vertices_count() const;

    unsigned get_nxt(unsigned from, unsigned weight) const;

    void show_graph() const;
};


class AutomatGraph {
    std::vector<std::vector<std::vector<unsigned>>> verticesList;
    std::unordered_set<unsigned> terminals;
public:
    unsigned alphabetSize;

    AutomatGraph(unsigned vertcnt, unsigned max_vert_out_degree);

    void make_terminal(unsigned vert);

    bool is_terminal(unsigned vert) const;

    void add_vertice();

    void add_edge(unsigned from, unsigned to, unsigned weight);

    unsigned vertices_count() const;

    std::vector<unsigned> get_nxt(unsigned from, unsigned weight) const;

    void show_graph() const;
};