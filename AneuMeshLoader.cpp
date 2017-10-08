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

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open file: \"" << filename << "\"!" << std::endl;
        exit(EXIT_FAILURE); // try-except?
    } else std::cout << "File \"" << filename << "\" was opened successfully." << std::endl;

    // Get_Nodes
    // Get_Surf
    // etc
}
