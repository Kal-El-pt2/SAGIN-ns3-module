#include "sagin-routing.h"
#include "sagin-mac.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("SaginRouting");
NS_OBJECT_ENSURE_REGISTERED(SaginRouting);

TypeId SaginRouting::GetTypeId() {
    static TypeId tid = TypeId("ns3::SaginRouting")
                            .SetParent<Object>()
                            .SetGroupName("Sagin")
                            .AddConstructor<SaginRouting>();
    return tid;
}

SaginRouting::SaginRouting() {
    NS_LOG_FUNCTION(this);
    InitializeRoutingTable();
}

SaginRouting::SaginRouting(Ptr<SaginNode> node) : m_node(node) {
    NS_LOG_FUNCTION(this);
    InitializeRoutingTable();
}

SaginRouting::~SaginRouting() {
    NS_LOG_FUNCTION(this);
}

void SaginRouting::SetNode(Ptr<SaginNode> node) {
    m_node = node;
}

void SaginRouting::SetMacLayer(Ptr<SaginMac> mac) {
    m_mac = mac;
}

void SaginRouting::ReceivePacket(Ptr<Packet> packet) {
    NS_LOG_FUNCTION(this << packet);
    if (m_mac) {
        m_mac->SendPacket(packet);
    }
}

bool SaginRouting::RoutePacket(Ptr<Packet> packet, NodeAddress destination) {
    if (!m_node) {
        NS_LOG_ERROR("Node not set in SaginRouting");
        return false;
    }

    uint32_t destId = destination.GetUniqueId();
    auto it = m_routingTable.find(destId);

    if (it != m_routingTable.end()) {
        m_mac->SendPacket(packet);
        return true;
    } else {
        SendRouteRequest(destination);
        return false;
    }
}

void SaginRouting::SendRouteRequest(NodeAddress destination) {
    NS_LOG_INFO("Sending route request for destination " << destination.GetUniqueId());

    // Check if the request already exists before inserting
    if (m_activeRouteRequests.find(destination.GetUniqueId()) == m_activeRouteRequests.end()) {
        m_activeRouteRequests.insert(destination.GetUniqueId());
        // Further logic to send the request
    }
}


void SaginRouting::ReceiveRouteRequest(NodeAddress source, NodeAddress destination, uint32_t hopCount, uint32_t traffic) {
    uint32_t destId = destination.GetUniqueId();
    RoutingEntry entry = {source.GetUniqueId(), hopCount, traffic, Simulator::Now()};
    m_routingTable[destId] = entry;
}

void SaginRouting::ProcessRrep(NodeAddress source, NodeAddress destination, uint32_t hopCount, uint32_t trafficCount) {
    uint32_t destId = destination.GetUniqueId();
    auto &entry = m_routingTable[destId];

    // Only update the route if it is better (lower hop count or less traffic)
    if (hopCount < entry.hopCount || (hopCount == entry.hopCount && trafficCount < entry.trafficCount)) {
        entry.nextHopId = source.GetUniqueId();
        entry.hopCount = hopCount;
        entry.trafficCount = trafficCount;
        entry.lastUpdate = Simulator::Now();
    }
}

void SaginRouting::InitializeRoutingTable() {
    NS_LOG_INFO("Initialized routing table.");
}

} // namespace ns3
