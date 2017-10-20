//
// Created by Bychin on 08.10.2017.
//

#include "MeshLoader.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>


std::vector<Node>& MeshLoader::Get_Nodes() {
    return nodes;
}

std::vector<Element>& MeshLoader::Get_Elements() {
    return elements;
}

std::vector<Surface>& MeshLoader::Get_Surfaces() {
    return surfaces;
}

void MeshLoader::Print_Data() {
    std::cout << nodes << std::endl
              << elements << std::endl
              << surfaces << std::endl;
}

std::vector<Element> MeshLoader::Get_Elements_by_ID(int id1, int id2, int id3) {
    std::vector<Element> answer;

    for (const auto& it : elements) {
        auto current_iter = it.nodes_ID.begin();
        auto last_iter = it.nodes_ID.end();
        auto correct_iter = std::find_if(current_iter, last_iter, [id1](int i){ return i == id1; });
        if (correct_iter == last_iter)
            continue;
        correct_iter = std::find_if(current_iter, last_iter, [id2](int i){ return i == id2; });
        if (correct_iter == last_iter)
            continue;
        correct_iter = std::find_if(current_iter, last_iter, [id3](int i){ return i == id3; });
        if (correct_iter == last_iter)
            continue;
        answer.push_back(it);
    }

    return answer;
}

std::vector<Element> MeshLoader::Get_Elements_by_edge(int id1, int id2) {
    std::vector<Element> answer;

    for (const auto& it : elements) {
        auto current_iter = it.nodes_ID.begin();
        auto last_iter = it.nodes_ID.end();
        auto correct_iter = std::find_if(current_iter, last_iter, [id1](int i){ return i == id1; });
        if (correct_iter == last_iter)
            continue;
        correct_iter = std::find_if(current_iter, last_iter, [id2](int i){ return i == id2; });
        if (correct_iter == last_iter)
            continue;
        answer.push_back(it);
    }

    return answer;
}

std::vector<Node> MeshLoader::Get_Vertex_Nodes_by_Surface_ID(int s_id) {
    std::vector<Node> result;
    auto surface_by_ID = std::find_if(surfaces.begin(), surfaces.end(), [s_id](Surface s){ return s.surface_ID == s_id; });
    if (surface_by_ID == surfaces.end())
        result.clear();
    else
        for (const auto& it : surface_by_ID->nodes_ID) {
            auto node_by_ID = std::find_if(nodes.begin(), nodes.end(), [it](Node n){ return n.ID == it; });
            result.push_back(*node_by_ID);
        }
    return result;
}

std::vector<Element> MeshLoader::Get_Elements_by_Material_ID(int m_id) {
    std::vector<Element> result;
    auto element_by_material = elements.begin();
    auto last_element = elements.end();
    while (element_by_material != last_element) {
        element_by_material = std::find_if(element_by_material, last_element, [m_id](Element e){ return e.material_ID == m_id; });
        if (element_by_material != last_element) {
            result.push_back(*element_by_material);
            ++element_by_material;
        }
    }
    return result;
}

std::vector<Surface> MeshLoader::Get_Surfaces_by_Surface_ID(int s_id) {
    std::vector<Surface> result;
    auto surface_by_ID = surfaces.begin();
    auto last_element = surfaces.end();
    while (surface_by_ID != last_element) {
        surface_by_ID = std::find_if(surface_by_ID, last_element, [s_id](Surface s){ return s.surface_ID == s_id; });
        if (surface_by_ID != last_element) {
            result.push_back(*surface_by_ID);
            ++surface_by_ID;
        }
    }
    return result;
}

std::vector<std::vector<Node>> MeshLoader::Get_Nodes_Neighbors() {
    std::vector<std::vector<Node>> result(nodes.size() + 1);
    for (int i = 1; i < nodes.size() + 1; ++i) {
        std::vector<Node> neighbors;
        int node_id = nodes[i - 1].ID;
        for (const auto& it : elements){
            auto current_id = std::find(it.nodes_ID.begin(), it.nodes_ID.end(), node_id); // check if node_id is in current element node ID's
            if (current_id != it.nodes_ID.end()) { // if it is then scan and add all others node's ID as neighbors
                for (const auto& it2 : it.nodes_ID)
                    if (it2 != node_id) {
                        Node temp = Get_Node_by_ID(it2);
                        if (std::find(neighbors.begin(), neighbors.end(), temp) == neighbors.end())
                            neighbors.push_back(temp);
                    }
            }
        }
        result[i] = std::move(neighbors);
    }
    return result;
}

Node MeshLoader::Get_Node_by_ID(int n_id) {
    for (const auto& it : nodes)
        if (it.ID == n_id)
            return it;
    return {};
}

void MeshLoader::Transform_Elements_to_Quadratic() {

}
