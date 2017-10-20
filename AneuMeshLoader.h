//
// Created by Bychin on 06.10.2017.
//

#ifndef LABORATORY_WORK_1_2_ANEUMESHLOADER_H
#define LABORATORY_WORK_1_2_ANEUMESHLOADER_H


#include "MeshLoader.h"
#include "DataStructures.h"

class AneuMeshLoader : public MeshLoader {
public:
    void LoadMesh(const std::string&) override;
};


#endif //LABORATORY_WORK_1_2_ANEUMESHLOADER_H
