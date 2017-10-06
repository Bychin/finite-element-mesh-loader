//
// Created by Bychin on 06.10.2017.
//

#include "AneuMeshLoader.h"

#include <fstream>
#include <iostream>

std::ifstream AneuMeshLoader::LoadMesh(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open file: \"" << filename << "\"!" << std::endl;
        exit(EXIT_FAILURE); // try-except?
    } else std::cout << "File \"" << filename << "\" was opened successfully." << std::endl;
    return file;
}
