//
// Created by Bychin on 06.10.2017.
//

#ifndef LABORATORY_WORK_1_2_DATASTRUCTURES_H
#define LABORATORY_WORK_1_2_DATASTRUCTURES_H


#include <iostream>
#include <vector>

struct Node {
    int ID;
    double x, y ,z;
    bool vertex;

    Node() = default;
    Node(int, double, double, double, bool);

    bool operator==(const Node&) const;
    friend std::ostream& operator<<(std::ostream&, const Node&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<Node>&);
};

struct Element {
    int element_ID;
    int material_ID;
    std::vector<int> nodes_ID;

    friend std::ostream& operator<<(std::ostream&, const Element&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<Element>&);
};

struct Surface : public Element {
    int surface_ID;
    int border_ID;

    friend std::ostream& operator<<(std::ostream&, const Surface&);
    friend std::ostream& operator<<(std::ostream&, const std::vector<Surface>&);
};


#endif //LABORATORY_WORK_1_2_DATASTRUCTURES_H
