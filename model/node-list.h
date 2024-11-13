#ifndef NODE_LIST_H
#define NODE_LIST_H

#include "sagin-node.h"
#include <map>

namespace ns3 {

class NodeList {
public:
    static NodeList& GetInstance();

    void AddNode(Ptr<SaginNode> node);
    Ptr<SaginNode> GetNode(uint32_t nodeId) const;
    std::vector<Ptr<SaginNode>> GetAllNodes() const;

    void RemoveNode(uint32_t nodeId);
    uint32_t GetNodeCount() const;

private:
    NodeList() {}  // Private constructor for singleton pattern
    NodeList(const NodeList&) = delete;
    NodeList& operator=(const NodeList&) = delete;

    std::map<uint32_t, Ptr<SaginNode>> m_nodes;  // Map node IDs to SaginNode pointers
};

} // namespace ns3

#endif // NODE_LIST_H
