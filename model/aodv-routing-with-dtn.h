// aodv-routing-with-dtn.h
#ifndef AODV_ROUTING_WITH_DTN_H
#define AODV_ROUTING_WITH_DTN_H

#include "aodv-routing.h" // Base AODV header file in ns3
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include <map>
#include <vector>

namespace ns3 {

class AodvRoutingWithDtn : public AodvRouting {
public:
    AodvRoutingWithDtn();
    virtual ~AodvRoutingWithDtn();

    void BufferPacket(Ptr<Packet> packet, Ipv4Address destination);
    void SendPacketFromBuffer(Ipv4Address destination);
    void CheckAndForwardBufferedPackets();

private:
    struct PacketEntry {
        Ptr<Packet> packet;
        Time expiration;
    };

    std::map<Ipv4Address, std::vector<PacketEntry>> m_packetBuffer;
    Time m_packetExpirationTime;
};

} // namespace ns3

#endif // AODV_ROUTING_WITH_DTN_H
