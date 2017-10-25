//
// Created by Bychin on 06.10.2017.
//

#include "AneuMeshLoader.h"
#include "Exceptions.h"

#include <fstream>
#include <iostream>

void AneuMeshLoader::LoadMesh(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        throw NoFileFoundException(filename);
    } else std::cout << "File \"" << filename << "\" was opened successfully." << std::endl;

    int amount, dimension;

    fin >> amount >> dimension;
    nodes.reserve(amount);
    for (int i = 1; i <= amount; ++i) {
        Node temp_node;
        temp_node.id = i;
        fin >> temp_node.x >> temp_node.y >> temp_node.z;
        temp_node.vertex = true;
        nodes.push_back(temp_node);
    }

    fin >> amount >> dimension;
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

    fin >> amount >> dimension; //valgrind
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
