//
// Created by Bychin on 06.10.2017.
//

#ifndef LABORATORY_WORK_1_2_DATASTRUCTURES_H
#define LABORATORY_WORK_1_2_DATASTRUCTURES_H


#include <iostream>
#include <vector>

struct Node {
    int id;
    double x, y ,z;
    bool vertex;

    Node() = default;
    Node(int, double, double, double, bool);

    bool operator==(const Node&) const;
    bool operator<(const Node&) const;
    friend std::ostream& operator<<(std::ostream&, const Node&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<Node>&);
};

struct Element {
    int element_id;
    int material_id;
    std::vector<int> nodes_id;

    friend std::ostream& operator<<(std::ostream&, const Element&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<Element>&);
};

struct Surface : public Element {
    int surface_id;
    int border_id;

    friend std::ostream& operator<<(std::ostream&, const Surface&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<Surface>&);
};

struct Edge {
    int first_node_id;
    int last_node_id;
    int center_id;

    Edge() = default;
    Edge(int, int, int);

    bool operator==(const Edge&) const;
    bool operator<(const Edge&) const;
    void UpdateCenter(int);
};


#endif //LABORATORY_WORK_1_2_DATASTRUCTURES_H
