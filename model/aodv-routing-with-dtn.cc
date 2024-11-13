// aodv-routing-with-dtn.cc
#include "aodv-routing-with-dtn.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("AodvRoutingWithDtn");

AodvRoutingWithDtn::AodvRoutingWithDtn() : m_packetExpirationTime(Seconds(60)) {}

AodvRoutingWithDtn::~AodvRoutingWithDtn() {}

void AodvRoutingWithDtn::BufferPacket(Ptr<Packet> packet, Ipv4Address destination) {
    PacketEntry entry = {packet, Simulator::Now() + m_packetExpirationTime};
    m_packetBuffer[destination].push_back(entry);
    NS_LOG_INFO("Buffered packet for destination " << destination);
}

void AodvRoutingWithDtn::SendPacketFromBuffer(Ipv4Address destination) {
    if (m_packetBuffer.find(destination) != m_packetBuffer.end()) {
        for (auto it = m_packetBuffer[destination].begin(); it != m_packetBuffer[destination].end();) {
            if (Simulator::Now() <= it->expiration) {
                AodvRouting::SendPacket(it->packet, destination);
                NS_LOG_INFO("Forwarding buffered packet to " << destination);
                it = m_packetBuffer[destination].erase(it);
            } else {
                NS_LOG_INFO("Discarding expired packet for " << destination);
                it = m_packetBuffer[destination].erase(it);
            }
        }
        if (m_packetBuffer[destination].empty()) {
            m_packetBuffer.erase(destination);
        }
    }
}

void AodvRoutingWithDtn::CheckAndForwardBufferedPackets() {
    for (auto& entry : m_packetBuffer) {
        SendPacketFromBuffer(entry.first);
    }
}

void AodvRoutingWithDtn::RoutePacket(Ptr<Packet> packet, Ipv4Address destination) {
    if (HasRoute(destination)) {
        AodvRouting::RoutePacket(packet, destination);
    } else {
        BufferPacket(packet, destination);
    }
}

void AodvRoutingWithDtn::ProcessRrep(Ptr<Packet> packet, Ipv4Address source, Ipv4Address destination) {
    AodvRouting::ProcessRrep(packet, source, destination);
    CheckAndForwardBufferedPackets();
}

void AodvRoutingWithDtn::ProcessRreq(Ptr<Packet> packet, Ipv4Address source, Ipv4Address destination) {
    AodvRouting::ProcessRreq(packet, source, destination);
    CheckAndForwardBufferedPackets();
}

} // namespace ns3
