//
// Created by Bychin on 06.10.2017.
//

#include "MeshLoader.h"
#include "NeuMeshLoader.h"
#include "AneuMeshLoader.h"

#include <iostream>
#include <string>
#include <fstream>


std::string FILEPATH = R"(C:\Users\Bychin\Documents\_Projects\ClionProjects\laboratory_work_1_2\a-neu-files\cube.neu)";
//std::string FILEPATH = "./a-neu-files/cube.aneu";

MeshLoader* File_Format_Checker(std::string& file) { // deletes all whitespaces, checks correct format
    while (file.back() == ' ')                       //  and call suitable loader
        file.pop_back();
    MeshLoader* mesh_pointer = nullptr;

    // check .aneu
    std::size_t found = file.rfind(".aneu");
    if (found != std::string::npos && file.length() - found == 5) {
        std::cout << "File-format-checker was passed." << std::endl;
        dynamic_cast<AneuMeshLoader*>(mesh_pointer);
        mesh_pointer = new AneuMeshLoader;
        return mesh_pointer;
    }

    // check .neu
    found = file.rfind(".neu");
    if (found != std::string::npos && file.length() - found == 4) {
        std::cout << "File-format-checker was passed." << std::endl;
        dynamic_cast<NeuMeshLoader*>(mesh_pointer);
        mesh_pointer = new NeuMeshLoader;
        return mesh_pointer;
    }

    else std::cout << "Warning! File-format-checker was not passed!" << std::endl;
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
        std::cout << "Exiting!\n"; // EXCEPTION
        return 1;
    };

    loader->LoadMesh(filepath);
    loader->Print_Data();
    std::vector<Element> elements_vector;
    std::vector<Node> nodes_vector;
    std::vector<std::vector<Node>> neighbors;
    std::vector<Surface> surfaces_vector;

    std::cout << "Result of Get_Elements_by_ID(2, 4, 8) function:\n";
    elements_vector = loader->Get_Elements_by_ID(2, 4, 8);
    std::cout << elements_vector;
    elements_vector.clear();

    std::cout << "\nResult of Get_Elements_by_edge(2, 8) function:\n";
    elements_vector = loader->Get_Elements_by_edge(2, 8);
    std::cout << elements_vector;
    elements_vector.clear();

    std::cout << "\nResult of Get_Vertex_Nodes_by_Surface_ID(12) function:\n";
    nodes_vector = loader->Get_Vertex_Nodes_by_Surface_ID(12);
    std::cout << nodes_vector;
    nodes_vector.clear();

    std::cout << "\nResult of Get_Elements_by_Material_ID(1) function:\n";
    elements_vector = loader->Get_Elements_by_Material_ID(1);
    std::cout << elements_vector;
    elements_vector.clear();

    std::cout << "\nResult of Get_Surfaces_by_Surface_ID(1) function:\n";
    surfaces_vector = loader->Get_Surfaces_by_Surface_ID(1);
    std::cout << surfaces_vector;
    surfaces_vector.clear();

    std::cout << "\nResult of Get_Nodes_Neighbors() function:\n";
    neighbors = loader->Get_Nodes_Neighbors();
    for (int i = 1; i < neighbors.size(); ++i)
        std::cout << "Neighbors for Node with ID = " << i << "\n" << neighbors[i];
    neighbors.clear();

    std::cout << "\nResult of Transform_Elements_to_Quadratic() function:\n";
    loader->Transform_Elements_to_Quadratic();
    loader->Print_Data();

    return 0;
}
