//
// Created by Bychin on 21.10.2017.
//

#include "NeuMeshLoader.h"

#include <fstream>
#include <iostream>

void NeuMeshLoader::LoadMesh(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Cannot open file: \"" << filename << "\"!" << std::endl;
        exit(EXIT_FAILURE); // try-except?
    } else std::cout << "File \"" << filename << "\" was opened successfully." << std::endl;

    int amount;

    fin >> amount;
    nodes.reserve(amount);
    for (int i = 1; i <= amount; ++i) {
        Node temp_node;
        temp_node.ID = i;
        fin >> temp_node.x >> temp_node.y >> temp_node.z;
        temp_node.vertex = true;
        nodes.push_back(temp_node);
    }

    fin >> amount;
    // some manipulations to find out dimension
    auto position = fin.tellg();
    char c;
    bool already_found = false;
    int dimension = 0;
    fin.get(c); // catch '\n'
    while (fin.get(c) && c != '\n') {
        if (c != ' ') {
            if (!already_found) {
                ++dimension;
                already_found = true;
            };
        } else
            already_found = false;
    }
    fin.seekg(position, fin.beg);
    std::cout << dimension << std::endl;//
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

    fin >> amount;
    // some manipulations to find out dimension
    position = fin.tellg();
    already_found = false;
    dimension = 0;
    fin.get(c); // catch '\n'
    while (fin.get(c) && c != '\n') {
        if (c != ' ') {
            if (!already_found) {
                ++dimension;
                already_found = true;
            }
        } else
            already_found = false;
    }
    fin.seekg(position, fin.beg);

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
        std::vector<Element> temp_elements = Get_Elements_by_ID(temp_surface.nodes_ID[0],
                                                                temp_surface.nodes_ID[1],
                                                                temp_surface.nodes_ID[2]);
        temp_surface.element_ID = temp_elements[0].element_ID;
        temp_surface.material_ID = temp_elements[0].material_ID;
        surfaces.push_back(std::move(temp_surface));
    }

    fin.close();
    std::cout << "All data was loaded, closing the file..." << std::endl;
}
