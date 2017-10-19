//
// Created by Bychin on 06.10.2017.
//

#include "AneuMeshLoader.h"

#include <fstream>
#include <iostream>

void AneuMeshLoader::LoadMesh(const std::string& filename) {
    // check ANEU
    std::size_t found = filename.rfind("aneu");
    if (found != std::string::npos)
        if (filename.length() - found != 4) // correct?
            std::cout << "Warning! Look's like you've entered bad filepath in commandline." << std::endl; // try-except ???
        else std::cout << "File-format-checker was passed." << std::endl;
    else std::cout << "Warning! Unknown file format may cause undefined behavior!" << std::endl; // try-except ???

    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Cannot open file: \"" << filename << "\"!" << std::endl;
        exit(EXIT_FAILURE); // try-except?
    } else std::cout << "File \"" << filename << "\" was opened successfully." << std::endl;

    int amount, dimension;
    fin >> amount >> dimension;
    nodes.reserve(amount);
    for (int i = 1; i <= amount; ++i) {
        Node temp_node;
        temp_node.ID = i;
        fin >> temp_node.x >> temp_node.y >> temp_node.z;
        temp_node.vertex = true;
        nodes.push_back(temp_node);
    }

    fin >> amount >> dimension;
    elements.reserve(amount);
    for (int i = 1; i <= amount; ++i) {
        Element temp_element;
        temp_element.nodes_ID.reserve(dimension);
        temp_element.element_ID = i;
        fin >> temp_element.material_ID;
        for (int j = 0; j < dimension; ++j)
            fin >> temp_element.nodes_ID.at(j);
        elements.push_back(std::move(temp_element));
    }

    fin >> amount >> dimension;
    surfaces.reserve(amount);
    for (int i = 1; i <= amount; ++i) {
        Surface temp_surface;
        temp_surface.surface_ID = i;
        fin >> temp_surface.type_ID;
        temp_surface.nodes_ID.reserve(dimension);
        for (int j = 0; j < dimension; ++j)
            fin >> temp_surface.nodes_ID.at(j);
        surfaces.push_back(std::move(temp_surface));
    }
}
