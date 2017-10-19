//
// Created by Bychin on 08.10.2017.
//

#include "MeshLoader.h"

#include <vector>


std::vector<Node>& MeshLoader::Get_Nodes() {
    return nodes;
}

std::vector<Element>& MeshLoader::Get_Elements() {
    return elements;
}

std::vector<Surface>& MeshLoader::Get_Surfaces() {
    return surfaces;
}
