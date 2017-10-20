//
// Created by Bychin on 08.10.2017.
//

#include "MeshLoader.h"

#include <vector>
#include <iostream>
#include <iomanip>


std::vector<Node>& MeshLoader::Get_Nodes() {
    return nodes;
}

std::vector<Element>& MeshLoader::Get_Elements() {
    return elements;
}

std::vector<Surface>& MeshLoader::Get_Surfaces() {
    return surfaces;
}

void MeshLoader::Print_Data() {
    std::cout << nodes.size() << " Nodes:\n"
              << " ID" << std::setw(10) << "X" << std::setw(11) << "Y" << std::setw(11) << "Z" << std::setw(14) << "Vertex\n";
    for (auto& it : nodes) {
        std::cout << std::setw(4) << it.ID << " |"
                  << std::right << std::setw(11) << it.x << std::setw(11) << it.y << std::setw(11) << it.z
                  << " | " << it.vertex << "\n";
    };
    std::cout << std::endl;

    int elements_size = elements.size();
    std::cout << elements_size << " Elements:\n"
              << " ID" << std::setw(15) << "Material_ID" << std::setw(15) << "Nodes ID\n";
    for (auto& it : elements) {
        std::cout << std::setw(4) << it.element_ID << " |"
                  << std::setw(11) << it.material_ID << " |";
        for (auto& nodes_ID_it : it.nodes_ID)
            std::cout << std::right << std::setw(4) << nodes_ID_it;
        std::cout << "\n";
    };
    std::cout << std::endl;

    int surfaces_size = surfaces.size();
    std::cout << surfaces_size << " Surfaces:\n"
              << "Surface_ID" << std::setw(11) << "Border_ID" << std::setw(14) << "Nodes ID\n";
    for (auto& it : surfaces) {
        std::cout << std::setw(9) << it.surface_ID << " |"
                  << std::setw(9) << it.border_ID << " |";
        for (auto& nodes_ID_it : it.nodes_ID)
            std::cout << std::right << std::setw(4) << nodes_ID_it;
        std::cout << "\n";
    };
}
