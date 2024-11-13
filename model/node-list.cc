#include "node-list.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("NodeList");

NodeList& NodeList::GetInstance() {
    static NodeList instance;
    return instance;
}

void NodeList::AddNode(Ptr<SaginNode> node) {
    uint32_t nodeId = node->GetId();
    m_nodes[nodeId] = node;
    NS_LOG_INFO("Node " << nodeId << " added to NodeList.");
}

Ptr<SaginNode> NodeList::GetNode(uint32_t nodeId) const {
    auto it = m_nodes.find(nodeId);
    if (it != m_nodes.end()) {
        return it->second;
    } else {
        NS_LOG_WARN("Node " << nodeId << " not found in NodeList.");
        return nullptr;
    }
}

std::vector<Ptr<SaginNode>> NodeList::GetAllNodes() const {
    std::vector<Ptr<SaginNode>> nodes;
    for (const auto& entry : m_nodes) {
        nodes.push_back(entry.second);
    }
    return nodes;
}

void NodeList::RemoveNode(uint32_t nodeId) {
    m_nodes.erase(nodeId);
    NS_LOG_INFO("Node " << nodeId << " removed from NodeList.");
}

uint32_t NodeList::GetNodeCount() const {
    return m_nodes.size();
}

} // namespace ns3
