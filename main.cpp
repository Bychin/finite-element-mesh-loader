//
// Created by Bychin on 06.10.2017.
//

#include "MeshLoader.h"
#include "AneuMeshLoader.h"

#include <iostream>
#include <string>
#include <fstream>


std::string FILEPATH = R"(C:\Users\Bychin\Documents\_Projects\ClionProjects\laboratory_work_1_2\a-neu-files\cube.aneu)";
//std::string FILEPATH = "./a-neu-files/cube.aneu";

MeshLoader* File_Format_Checker(std::string& file) { // deletes all whitespaces, checks correct format and call suitable loader
    while (file.back() == ' ')
        file.pop_back();
    MeshLoader* mesh_pointer = nullptr;
    // check ANEU
    std::size_t found = file.rfind(".aneu");
    if (found != std::string::npos)
        if (file.length() - found == 5) {
            std::cout << "File-format-checker was passed." << std::endl;
            dynamic_cast<AneuMeshLoader*>(mesh_pointer);
            mesh_pointer = new AneuMeshLoader;
            return mesh_pointer;
        }
        else {
            std::cout << "Warning! Look's like you've entered bad filepath in commandline." << std::endl;
            return nullptr;
        } // try-except ???

    // more else - if blocks for .neu, etc

    else std::cout << "Warning! Unknown file format may cause undefined behavior!" << std::endl; // try-except ???
    return nullptr;
}

int main(int argc, char* argv[]) {
    std::string filepath = FILEPATH;
    if (argc == 1)
        std::cout << "No arguments were added, using standard file PATH..." << std::endl;
    else if (argc > 2)
        std::cout << "There must be one or none arguments! Set file path to default..." << std::endl;
    else {
        std::cout << "Set file path to \"" << argv[1] << "\"..." << std::endl;
        filepath = argv[1]; // toLower?
    };

    MeshLoader* loader = File_Format_Checker(filepath);

    if (loader == nullptr) {
        std::cout << "Exiting!\n";
        return 1;
    };

    loader->LoadMesh(filepath);
    loader->Print_Data();




    return 0;
}