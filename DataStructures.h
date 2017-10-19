//
// Created by Bychin on 06.10.2017.
//

#ifndef LABORATORY_WORK_1_2_DATASTRUCTURES_H
#define LABORATORY_WORK_1_2_DATASTRUCTURES_H


#include <list>


struct Node {
    int ID;
    double x, y ,z;
    bool vertex;

    Node() = default;
};

struct Element {
    int element_ID;
    int material_ID;
    std::vector<int> nodes_ID;

    Element() = default;
};

struct Surface : public Element {
    int surface_ID;
    int type_ID;

    Surface() = default;
};


#endif //LABORATORY_WORK_1_2_DATASTRUCTURES_H
