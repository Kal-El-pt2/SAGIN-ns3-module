#ifndef NODE_ADDRESS_H
#define NODE_ADDRESS_H

#include <string>

namespace ns3 {

enum NodeType {
    SPACE_NODE,
    GROUND_NODE,
    AERIAL_NODE

};

class NodeAddress {
public:
    NodeAddress(NodeType type, int uniqueId) 
        : m_type(type), m_uniqueId(uniqueId) {}

    std::string GetAddress() const {
        return std::to_string(m_type) + "-" + std::to_string(m_uniqueId);
    }

    NodeType GetType() const {
        return m_type;
    }

    int GetUniqueId() const {
        return m_uniqueId;
    }
    std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& os, const NodeAddress& addr);
private:
    NodeType m_type;   // Type of the node (Space, Ground, Aerial)
    int m_uniqueId;    // Unique identifier for the node
};

} // namespace ns3

#endif // NODE_ADDRESS_H
