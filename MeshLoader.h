//
// Created by Bychin on 06.10.2017.
//

#ifndef LABORATORY_WORK_1_2_MESHLOADER_H
#define LABORATORY_WORK_1_2_MESHLOADER_H


#include <fstream>
#include <vector>

#include "DataStructures.h"

class MeshLoader {
protected:
    std::vector<Node> nodes;
    std::vector<Element> elements;
    std::vector<Surface> surfaces;
public:
    virtual void LoadMesh(const std::string&) = 0;
    virtual ~MeshLoader() = default;

    void Print_Data();

    // методы, позволяющие получить STL-контейнеры узлов, конечных элементов и поверхностных элементов
    std::vector<Node>& Get_Nodes();
    std::vector<Element>& Get_Elements();
    std::vector<Surface>& Get_Surfaces();

    // TODO: transfer to AneuMeshLoader.cpp
    // метод, позволяющий найти КЭ по ID трех его вершинных узлов
    std::vector<Element> Get_Elements_by_ID(int, int, int);
    // метод, позволяющий найти КЭ по ребру
    std::vector<Element> Get_Elements_by_edge(int, int);
    // метод, возвращающий контейнер поверхностных узлов по ID поверхности
    std::vector<Node> Get_Vertex_Nodes_by_Surface_ID(int);
    // метод, возвращающий контейнер КЭ с заданным ID материала
    std::vector<Element> Get_Elements_by_Material_ID(int);
    // метод, возвращающий контейнер поверхностных КЭ с заданным ID поверхности
    std::vector<Surface> Get_Surfaces_by_Surface_ID(int);
    // метод, преобразующий симплексные тетраэдральные КЭ в квадратичные путем внесения новых узлов в загруженную КЭ сетку
    void Transform_Elements_to_Quadratic();
    // метод, создающий контейнер, n-ый элемент которого хранит контейнер всех «соседей» для узла n
    std::vector<std::vector<Node>> Get_Nodes_Neighbors();
    Node Get_Node_by_ID(int);

private:
    int Get_Last_Nodes_ID();
};


#endif //LABORATORY_WORK_1_2_MESHLOADER_H
