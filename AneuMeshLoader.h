//
// Created by Bychin on 06.10.2017.
//

#ifndef LABORATORY_WORK_1_2_ANEUMESHLOADER_H
#define LABORATORY_WORK_1_2_ANEUMESHLOADER_H


#include <fstream>

#include "MeshLoader.h"

class AneuMeshLoader : MeshLoader {
public:
    std::ifstream LoadMesh(const std::string& filename) override;



};


#endif //LABORATORY_WORK_1_2_ANEUMESHLOADER_H
