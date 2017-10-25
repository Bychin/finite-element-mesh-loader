//
// Created by Bychin on 08.10.2017.
//

#include "MeshLoader.h"

#include <iomanip>
#include <algorithm>
#include <list>
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
    std::cout << Get_Nodes() << std::endl
              << Get_Elements() << std::endl
              << Get_Surfaces() << std::endl;
}

std::vector<Element> MeshLoader::Get_Elements_by_ID(int id1, int id2, int id3) { //find_if<elements>
    std::vector<Element> answer;
    auto current_iter = elements.begin();
    auto last_iter = elements.end();
    while (current_iter != last_iter) {
        current_iter = std::find_if(current_iter, last_iter, [id1, id2, id3](Element current_element){
            return std::find(current_element.nodes_id.begin(), current_element.nodes_id.end(), id1) != current_element.nodes_id.end()
                && std::find(current_element.nodes_id.begin(), current_element.nodes_id.end(), id2) != current_element.nodes_id.end()
                && std::find(current_element.nodes_id.begin(), current_element.nodes_id.end(), id3) != current_element.nodes_id.end(); });
        if (current_iter != last_iter) {
            answer.push_back(*current_iter);
            ++current_iter;
        }
    }
    return answer;
}

std::vector<Element> MeshLoader::Get_Elements_by_edge(int id1, int id2) {
    std::vector<Element> answer;

    auto current_iter = elements.begin();
    auto last_iter = elements.end();
    while (current_iter != last_iter) {
        current_iter = std::find_if(current_iter, last_iter, [id1, id2](Element current_element){
            return std::find(current_element.nodes_id.begin(), current_element.nodes_id.end(), id1) != current_element.nodes_id.end()
                && std::find(current_element.nodes_id.begin(), current_element.nodes_id.end(), id2) != current_element.nodes_id.end(); });
        if (current_iter != last_iter) {
            answer.push_back(*current_iter);
            ++current_iter;
        }
    }
    return answer;
}

std::vector<Node> MeshLoader::Get_Vertex_Nodes_by_Surface_ID(int s_id) {
    std::set<Node> result;
    auto current_iter = surfaces.begin();
    auto last_iter = surfaces.end();
    while (current_iter != last_iter) {
        current_iter = std::find_if(current_iter, last_iter, [s_id](Surface s){ return s.border_id == s_id; });
        if (current_iter != last_iter) {
            for (const auto& it : current_iter->nodes_id) {
                auto node_by_ID = std::find_if(nodes.begin(), nodes.end(), [it](Node n){ return n.id == it; });
                result.insert(*node_by_ID);
            }
            ++current_iter;
        }
    }
    return std::vector<Node>(result.begin(), result.end());
}

std::vector<Element> MeshLoader::Get_Elements_by_Material_ID(int m_id) {
    std::list<Element> result;
    auto element_by_material = elements.begin();
    auto last_element = elements.end();
    while (element_by_material != last_element) {
        element_by_material = std::find_if(element_by_material, last_element, [m_id](Element e){ return e.material_id == m_id; });
        if (element_by_material != last_element) {
            result.push_back(*element_by_material);
            ++element_by_material;
        }
    }
    return std::vector<Element>(result.begin(), result.end());
}

std::vector<Surface> MeshLoader::Get_Surfaces_by_Surface_ID(int s_id) {
    std::list<Surface> result;
    auto surface_by_ID = surfaces.begin();
    auto last_element = surfaces.end();
    while (surface_by_ID != last_element) {
        surface_by_ID = std::find_if(surface_by_ID, last_element, [s_id](Surface s){ return s.surface_id == s_id; });
        if (surface_by_ID != last_element) {
            result.push_back(*surface_by_ID);
            ++surface_by_ID;
        }
    }
    return std::vector<Surface>(result.begin(), result.end());
}

std::vector<std::vector<Node>> MeshLoader::Get_Nodes_Neighbors() {
    std::vector<std::set<int>> result_int(nodes.size() + 1); //vector<set>
    for (auto& it : elements)
        for (auto node_it : it.nodes_id) {
            for (auto node_it2 : it.nodes_id) // std::copy ???
                result_int[node_it].insert(node_it2);
            result_int[node_it].erase(node_it);
        }

    std::vector<std::vector<Node>> result(nodes.size() + 1);
    for (int i = 1; i < nodes.size() + 1; ++i) {
        std::vector<Node> temp_vec;
        temp_vec.reserve(result_int[i].size());
        for (auto& it_set : result_int[i])
            temp_vec.push_back(Get_Node_by_ID(it_set));
        result[i] = std::move(temp_vec);
    }
    return result;
}

Node MeshLoader::Get_Node_by_ID(int n_id) {
    for (const auto& it : nodes)
        if (it.id == n_id)
            return it;
    return {};
}

void MeshLoader::Transform_Elements_to_Quadratic() {
    std::set<Edge> edges;

    for (auto& it : elements) {
        std::vector<int> current_nodes(it.nodes_id);
        for (auto i = current_nodes.begin(); i < current_nodes.end() - 1; ++i)
            for (auto j = i + 1; j < current_nodes.end(); ++j) {
                Edge current_edge(*i, *j, 0);
                auto founded_edge = std::find(edges.begin(), edges.end(), current_edge);
                if (founded_edge == edges.end()) {
                    // if there was not same edge before, make new center-Node for this edge...
                    Node left_node = Get_Node_by_ID(*i);
                    Node right_node = Get_Node_by_ID(*j);
                    int center_id_ = Get_Last_Nodes_ID() + 1;
                    Node center_node(center_id_, (left_node.x + right_node.x) / 2,
                                     (left_node.y + right_node.y) / 2, (left_node.z + right_node.z) / 2, false);

                    current_edge.UpdateCenter(center_id_);
                    nodes.push_back(center_node);
                    edges.insert(current_edge);

                    // ...and push_back new id to current elements.nodes_id
                    it.nodes_id.push_back(center_id_);
                } else {
                    // if there was same edge before, get its center node's id
                    it.nodes_id.push_back(founded_edge->center_id);
                }
            }
        it.nodes_id.shrink_to_fit();
    }

    // update Surface.nodes_id because of new Nodes
    for (auto& it : surfaces) {
        std::vector<int> current_nodes(it.nodes_id);
        for (auto i = current_nodes.begin(); i < current_nodes.end() - 1; ++i)
            for (auto j = i + 1; j < current_nodes.end(); ++j) {
                Edge current_edge(*i, *j, 0);
                auto founded_edge = std::find(edges.begin(), edges.end(), current_edge);
                if (founded_edge != edges.end())
                    it.nodes_id.push_back(founded_edge->center_id);
            }
        it.nodes_id.shrink_to_fit();
    }
    surfaces.shrink_to_fit();
    nodes.shrink_to_fit();
}

int MeshLoader::Get_Last_Nodes_ID() {
    return nodes.rbegin()->id;
}
