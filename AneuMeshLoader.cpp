//
// Created by Bychin on 06.10.2017.
//

#include "AneuMeshLoader.h"

#include <fstream>
#include <iostream>

void AneuMeshLoader::LoadMesh(const std::string& filename) {


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
        temp_element.element_ID = i;
        fin >> temp_element.material_ID;
        temp_element.nodes_ID.reserve(dimension);
        int temp_id;
        for (int j = 0; j < dimension; ++j) {
            fin >> temp_id;
            temp_element.nodes_ID.push_back(temp_id);
        }
        elements.push_back(std::move(temp_element));
    }

    fin >> amount >> dimension;
    surfaces.reserve(amount);
    for (int i = 1; i <= amount; ++i) {
        Surface temp_surface;
        temp_surface.surface_ID = i;
        fin >> temp_surface.border_ID;
        temp_surface.nodes_ID.reserve(dimension);
        int temp_id;
        for (int j = 0; j < dimension; ++j) {
            fin >> temp_id;
            temp_surface.nodes_ID.push_back(temp_id);
        }
        surfaces.push_back(std::move(temp_surface));
    }

    fin.close();
    std::cout << "All data was loaded, closing the file..." << std::endl;
}
