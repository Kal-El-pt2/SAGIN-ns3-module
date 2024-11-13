#ifndef SAGIN_ROUTING_H
#define SAGIN_ROUTING_H

#include "node-address.h"
#include "sagin-node.h"
#include "ns3/node.h"
#include "ns3/object.h"
#include "ns3/packet.h"
#include "ns3/socket.h"
#include "ns3/object-base.h" // Include ObjectBase for Unref
#include "ns3/nstime.h"
#include <map>
#include <set>

namespace ns3 {
class SaginNode;
class SaginMac;

class SaginRouting : public Object {
public:
    static TypeId GetTypeId();
    SaginRouting();
    SaginRouting(Ptr<SaginNode> node);
    ~SaginRouting();

    void ReceivePacket(Ptr<Packet> packet);
    void InitializeRoutingTable();

    bool RoutePacket(Ptr<Packet> packet, NodeAddress destination);

    void SetNode(Ptr<SaginNode> node);
    void SetMacLayer(Ptr<SaginMac> mac);

    void SendRouteRequest(NodeAddress destination);
    void ReceiveRouteRequest(NodeAddress source, NodeAddress destination, uint32_t hopCount, uint32_t traffic);

private:
    struct RoutingEntry {
        uint32_t nextHopId;
        uint32_t hopCount;
        uint32_t trafficCount;
        Time lastUpdate; // Time now has a full definition
    };

    std::map<uint32_t, RoutingEntry> m_routingTable;
    std::set<uint32_t> m_activeRouteRequests;

    Ptr<SaginNode> m_node;
    Ptr<SaginMac> m_mac;

    void ProcessRrep(NodeAddress source, NodeAddress destination, uint32_t hopCount, uint32_t trafficCount);
};

} // namespace ns3

#endif // SAGIN_ROUTING_H
