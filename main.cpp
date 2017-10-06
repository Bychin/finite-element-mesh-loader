//
// Created by Bychin on 06.10.2017.
//

#include "MeshLoader.h"
#include "AneuMeshLoader.h"

#include <iostream>
#include <string>
#include <fstream>


std::string FILEPATH = "./a-neu-files/ellipsoid.aneu";

void File_Format_Checker(std::string& file) { // delete all whitespaces and check correct .aneu format
    while (file.back() == ' ')
        file.pop_back();
    std::size_t found = file.rfind("aneu");
    if (found != std::string::npos)
        if (file.length() - found != 4)
            std::cout << "Warning! Look's like you've entered bad filepath in commandline." << std::endl; // try-except ???
        else std::cout << "File-format-checker was passed." << std::endl;
    else std::cout << "Warning! Unknown file format may cause undefined behavior!" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string filepath = FILEPATH;
    if (argc == 1)
        std::cout << "No arguments were added, using standard file PATH..." << std::endl;
    else if (argc > 2)
        std::cout << "There must be one or none arguments! Set file path to default..." << std::endl;
    else {
        std::cout << "Set file path to \"" << argv[1] << "\"..." << std::endl;
        filepath = argv[1];
    };
    File_Format_Checker(filepath);


    MeshLoader* loader = nullptr;



    return 0;
}