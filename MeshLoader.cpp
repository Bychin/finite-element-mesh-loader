//
// Created by Bychin on 08.10.2017.
//

#include "MeshLoader.h"

#include <iomanip>
#include <algorithm>
#include <map>


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
    std::cout << Get_Nodes() << std::endl
              << Get_Elements() << std::endl
              << Get_Surfaces() << std::endl;
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
    std::map<std::pair<int, int>, int> pair_to_node_ID; // key - 2 node's ID (real edge),
                                                        // value - node's ID which is between them
    for (auto& it : elements) {
        std::vector<int> current_nodes(it.nodes_ID);
        std::sort(current_nodes.begin(), current_nodes.end());

        // i && j get all combinations of (x, y) in (x, y, z...)
        for (auto i = current_nodes.begin(); i < current_nodes.end() - 1; ++i)
            for (auto j = i + 1; j < current_nodes.end(); ++j) {
                std::pair<int, int> temp_pair(*i, *j);
                if (pair_to_node_ID.find(temp_pair) == pair_to_node_ID.end()) {
                    // if there was not same pair before, make new center-Node for this edge...
                    Node left_node = Get_Node_by_ID(*i);
                    Node right_node = Get_Node_by_ID(*j);
                    int center_id = Get_Last_Nodes_ID() + 1;
                    Node center_node(center_id, (left_node.x + right_node.x) / 2,
                           (left_node.y + right_node.y) / 2, (left_node.z + right_node.z) / 2, false);

                    nodes.push_back(center_node);
                    pair_to_node_ID.insert({temp_pair, center_id});

                    // ...and push_back new ID to current elements.nodes_ID
                    it.nodes_ID.push_back(center_id);
                } else {
                    // if there was same pair before, get it's center node's ID
                    int center_id = pair_to_node_ID.at(temp_pair);
                    it.nodes_ID.push_back(center_id);
                }
            }
        it.nodes_ID.shrink_to_fit();
    }
    // update Surface.nodes_ID because of new Nodes
    for (auto& it : surfaces) {
        std::vector<int> current_nodes(it.nodes_ID);
        std::sort(current_nodes.begin(), current_nodes.end());
        for (auto i = current_nodes.begin(); i < current_nodes.end() - 1; ++i)
            for (auto j = i + 1; j < current_nodes.end(); ++j) {
                std::pair<int, int> temp_pair(*i, *j);
                if (pair_to_node_ID.find(temp_pair) != pair_to_node_ID.end()) {
                    int center_id = pair_to_node_ID.at(temp_pair);
                    it.nodes_ID.push_back(center_id);
                }
            }
        it.nodes_ID.shrink_to_fit();
    }
    surfaces.shrink_to_fit();
    nodes.shrink_to_fit();
}

int MeshLoader::Get_Last_Nodes_ID() {
    return nodes.rbegin()->ID;
}
