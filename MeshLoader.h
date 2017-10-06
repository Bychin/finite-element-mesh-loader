//
// Created by Bychin on 06.10.2017.
//

#ifndef LABORATORY_WORK_1_2_MESHLOADER_H
#define LABORATORY_WORK_1_2_MESHLOADER_H


#include <fstream>

class MeshLoader {
public:
    virtual std::ifstream& LoadMesh(const std::string& filename) = 0;
};


#endif //LABORATORY_WORK_1_2_MESHLOADER_H
