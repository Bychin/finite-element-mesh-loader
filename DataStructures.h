//
// Created by Bychin on 06.10.2017.
//

#ifndef LABORATORY_WORK_1_2_DATASTRUCTURES_H
#define LABORATORY_WORK_1_2_DATASTRUCTURES_H


#include <list>


class Node {
    int ID;
    int x, y ,z;
    bool vertex;
};

class Element {
    int ID;
    int material_ID;
    std::list<int> nodes_ID;
};

class Surface {
    int ID;
    int element_ID;

};


#endif //LABORATORY_WORK_1_2_DATASTRUCTURES_H
