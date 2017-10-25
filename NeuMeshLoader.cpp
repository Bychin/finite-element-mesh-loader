//
// Created by Bychin on 21.10.2017.
//

#include "NeuMeshLoader.h"
#include "Exceptions.h"

#include <fstream>
#include <iostream>

void NeuMeshLoader::LoadMesh(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        throw NoFileFoundException(filename);
    } else std::cout << "File \"" << filename << "\" was opened successfully." << std::endl;

    int amount;

    fin >> amount;
    nodes.reserve(amount);
    for (int i = 1; i <= amount; ++i) {
        Node temp_node;
        temp_node.id = i;
        fin >> temp_node.x >> temp_node.y >> temp_node.z;
        temp_node.vertex = true;
        nodes.push_back(temp_node);
    }

    fin >> amount;
    // some manipulations to find out dimension should be added
    int dimension = 4;

    elements.reserve(amount);
    for (int i = 1; i <= amount; ++i) {
        Element temp_element;
        temp_element.element_id = i;
        fin >> temp_element.material_id;
        temp_element.nodes_id.reserve(dimension);
        int temp_id;
        for (int j = 0; j < dimension; ++j) {
            fin >> temp_id;
            temp_element.nodes_id.push_back(temp_id);
        }
        elements.push_back(std::move(temp_element));
    }

    fin >> amount;
    // some manipulations to find out dimension should be added
    dimension = 3;

    surfaces.reserve(amount);
    for (int i = 1; i <= amount; ++i) {
        Surface temp_surface;
        temp_surface.surface_id = i;
        fin >> temp_surface.border_id;
        temp_surface.nodes_id.reserve(dimension);
        int temp_id;
        for (int j = 0; j < dimension; ++j) {
            fin >> temp_id;
            temp_surface.nodes_id.push_back(temp_id);
        }
        std::vector<Element> temp_elements = Get_Elements_by_ID(temp_surface.nodes_id[0],
                                                                temp_surface.nodes_id[1],
                                                                temp_surface.nodes_id[2]);
        temp_surface.element_id = temp_elements[0].element_id;
        temp_surface.material_id = temp_elements[0].material_id;
        surfaces.push_back(std::move(temp_surface));
    }

    fin.close();
    std::cout << "All data was loaded, closing the file..." << std::endl;
}
