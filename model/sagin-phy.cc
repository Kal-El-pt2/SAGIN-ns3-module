#include "sagin-phy.h"

#include "ns3/log.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("SaginPhy");

NS_OBJECT_ENSURE_REGISTERED(SaginPhy);

TypeId
SaginPhy::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::SaginPhy")
                            .SetParent<Object>()
                            .SetGroupName("Sagin")
                            .AddConstructor<SaginPhy>()
                            .AddAttribute("TransmissionPower",
                                          "Transmission power in watts.",
                                          DoubleValue(1.0),
                                          MakeDoubleAccessor(&SaginPhy::SetTransmissionPower,
                                                             &SaginPhy::GetTransmissionPower),
                                          MakeDoubleChecker<double>())
                            .AddAttribute("PropagationDelay",
                                          "Signal propagation delay.",
                                          TimeValue(Seconds(0.01)),
                                          MakeTimeAccessor(&SaginPhy::SetPropagationDelay,
                                                           &SaginPhy::GetPropagationDelay),
                                          MakeTimeChecker());
    return tid;
}

SaginPhy::SaginPhy()
    : m_transmissionPower(1.0),         // default power
      m_propagationDelay(Seconds(0.01)) // default delay
{
    NS_LOG_FUNCTION(this);
}

SaginPhy::SaginPhy(Ptr<SaginMac> mac)
    : m_transmissionPower(1.0),
      m_propagationDelay(Seconds(0.01)),
      m_mac(mac) // Initialize MAC pointer
{
    NS_LOG_FUNCTION(this);
}

SaginPhy::~SaginPhy()
{
    NS_LOG_FUNCTION(this);
}

void
SaginPhy::SetTransmissionPower(double power)
{
    m_transmissionPower = power;
}

double
SaginPhy::GetTransmissionPower() const
{
    return m_transmissionPower;
}

void
SaginPhy::SetPropagationDelay(Time delay)
{
    m_propagationDelay = delay;
}

Time
SaginPhy::GetPropagationDelay() const
{
    return m_propagationDelay;
}

void
SaginPhy::SetReceiveCallback(Callback<void, Ptr<Packet>> cb)
{
    m_receiveCallback = cb;
}

void
SaginPhy::SendPacket(Ptr<Packet> packet)
{
    NS_LOG_FUNCTION(this << packet);
    NS_LOG_INFO("Sending packet from PHY layer with power: " << m_transmissionPower);

    // Loop through all nodes in range and send the packet to each
    for (Ptr<SaginNode> node : GetNodesInRange())
    {
        node->GetPhyLayer()->ReceivePacket(packet); // Transmit to PHY layer of other nodes
    }
}

void
SaginPhy::ReceivePacket(Ptr<Packet> packet)
{
    NS_LOG_FUNCTION(this << packet);
    NS_LOG_INFO("Packet received at PHY layer.");

    // Use ForwardPacketUp to send packet to MAC or other upper layer
    if (!m_receiveCallback.IsNull())
    {
        ForwardPacketUp(packet);
    }
    else if (m_mac)
    {
        m_mac->ReceivePacket(packet); // Direct call to MAC if no callback is set
    }
}

std::vector<Ptr<SaginNode>>
SaginPhy::GetNodesInRange()
{
    std::vector<Ptr<SaginNode>> nodesInRange;
    // This function would access position information and calculate distances
    // For now, this is a placeholder. Add nodes based on distance calculations.

    return nodesInRange;
}

void
SaginPhy::ForwardPacketUp(Ptr<Packet> packet)
{
    NS_LOG_FUNCTION(this << packet);
    m_receiveCallback(packet);
}

} // namespace ns3
