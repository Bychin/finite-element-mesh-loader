//
// Created by Bychin on 21.10.2017.
//

#ifndef LABORATORY_WORK_1_2_NEUMESHLOADER_H
#define LABORATORY_WORK_1_2_NEUMESHLOADER_H


#include <fstream>
#include <vector>

#include "MeshLoader.h"
#include "DataStructures.h"

class NeuMeshLoader : public MeshLoader {
public:
    void LoadMesh(const std::string&) override;
};


#endif //LABORATORY_WORK_1_2_NEUMESHLOADER_H
