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
    virtual void LoadMesh(const std::string& filename) = 0;

    // методы, позволяющие получить STL-контейнеры узлов, конечных элементов и поверхностных элементов
    std::vector<Node> Get_Nodes();
    std::vector<Element> Get_Elements();
    std::vector<Surface> Get_Surfaces();

    // метод, позволяющий найти КЭ по ID трех его вершинных узлов
    std::vector<Element> Get_Elements_by_ID(int id1, int id2, int id3); // stream??
    // метод, позволяющий найти КЭ по ребру
    std::vector<Element> Get_Elements_by_edge(int id1, int id2); // stream ??
    // метод, возвращающий контейнер поверхностных узлов по ID поверхности
    std::vector<Node> Get_Vertex_Nodes_by_Surface_ID(int s_id);
    // метод, возвращающий контейнер КЭ с заданным ID материала
    std::vector<Element> Get_Elements_by_Material_ID(int m_id);
    // метод, возвращающий контейнер поверхностных КЭ с заданным ID поверхности
    std::vector<Surface> Get_Surfaces_by_Surface_ID(int s_id);
    // метод, преобразующий симплексные тетраэдральные КЭ в квадратичные путем внесения новых узлов в загруженную КЭ сетку
    // ??????????????????
    // метод, создающий контейнер, n-ый элемент которого хранит контейнер всех «соседей» для узла n
    std::vector<std::vector<Node>> Get_Nodes_Neighbors();
};


#endif //LABORATORY_WORK_1_2_MESHLOADER_H
