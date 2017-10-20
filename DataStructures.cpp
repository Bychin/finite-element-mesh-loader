//
// Created by Bychin on 20.10.2017.
//

#include "DataStructures.h"

#include <iomanip>


bool Node::operator==(const Node& right_node) const {
    if (ID == right_node.ID && x == right_node.x && y == right_node.y &&
            z == right_node.z && vertex == right_node.vertex)
        return true;
    else return false;
};

std::ostream& operator<<(std::ostream& out_stream, const Node& node_) {
    out_stream << std::setw(4) << node_.ID << " |"
               << std::right << std::setw(11) << node_.x << std::setw(11) << node_.y << std::setw(11) << node_.z
               << " | " << node_.vertex << "\n";
    return out_stream;
}

std::ostream& operator<<(std::ostream& out_stream, const Element& element_) {
    out_stream << std::setw(4) << element_.element_ID << " |"
               << std::setw(11) << element_.material_ID << " |";
    for (const auto& nodes_ID_it : element_.nodes_ID)
        out_stream << std::right << std::setw(4) << nodes_ID_it;
    out_stream << "\n";
    return out_stream;
}

std::ostream& operator<<(std::ostream& out_stream, const Surface& surface_) {
    out_stream << std::setw(9) << surface_.surface_ID << " |"
               << std::setw(9) << surface_.border_ID << " |";
    for (const auto& nodes_ID_it : surface_.nodes_ID)
        out_stream << std::right << std::setw(4) << nodes_ID_it;
    out_stream << "\n";
    return out_stream;
}

std::ostream& operator<<(std::ostream& out_stream, const std::vector<Node>& nodes_) {
    out_stream << nodes_.size() << (nodes_.size() > 1 ? " Nodes:\n" : " Node:\n") << " ID"
               << std::setw(10) << "X" << std::setw(11) << "Y" << std::setw(11) << "Z" << std::setw(14) << "Vertex\n";
    for (const auto& it : nodes_)
        out_stream << it;
    return out_stream;
}

Node::Node(int ID_, double x_, double y_, double z_, bool vertex_) :
    ID(ID_), x(x_), y(y_), z(z_), vertex(vertex_) {}



std::ostream& operator<<(std::ostream& out_stream, const std::vector<Element>& elements_) {
    int elements_size = elements_.size();
    out_stream << elements_size << (elements_size > 1 ? " Elements:\n" : " Element:\n")
               << " ID" << std::setw(15) << "Material_ID" << std::setw(15) << "Nodes ID\n";
    for (const auto& it : elements_)
        out_stream << it;
    return out_stream;
}

std::ostream& operator<<(std::ostream& out_stream, const std::vector<Surface>& surfaces_) {
    int surfaces_size = surfaces_.size();
    out_stream << surfaces_size << (surfaces_size > 1 ? " Surfaces:\n" : " Surface:\n")
               << "Surface_ID" << std::setw(11) << "Border_ID" << std::setw(14) << "Nodes ID\n";
    for (const auto& it : surfaces_)
        out_stream << it;
    return out_stream;
}
