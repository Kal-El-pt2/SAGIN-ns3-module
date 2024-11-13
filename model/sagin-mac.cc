#include "sagin-mac.h"
#include "ns3/log.h"
//#include "ns3/mac-header.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("SaginMac");

NS_OBJECT_ENSURE_REGISTERED(SaginMac);

TypeId
SaginMac::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::SaginMac")
                            .SetParent<Object>()
                            .SetGroupName("Sagin")
                            .AddConstructor<SaginMac>();
    return tid;
}

SaginMac::SaginMac()
{
    NS_LOG_FUNCTION(this);
}

// Define SaginMac constructor with node reference
SaginMac::SaginMac(Ptr<SaginNode> node)
    : m_node(node) // Initialize m_node with the passed node
{
    NS_LOG_FUNCTION(this);
    // Additional initialization code if necessary
}

// In sagin-mac.cc
SaginMac::SaginMac(Ptr<SaginNode> node, Ptr<SaginPhy> phy)
    : m_node(node),
      m_phy(phy) // Initialize m_phy with the passed PHY layer
{
    NS_LOG_FUNCTION(this);
}

SaginMac::~SaginMac()
{
    NS_LOG_FUNCTION(this);
}

void
SaginMac::SetAddress(Mac48Address address)
{
    m_address = address;
}

Mac48Address
SaginMac::GetAddress(void) const
{
    return m_address;
}

void
SaginMac::SetForwardUpCallback(Callback<void, Ptr<Packet>> cb)
{
    m_forwardUpCb = cb;
}

void
SaginMac::SendPacket(Ptr<Packet> packet)
{
    NS_LOG_FUNCTION(this << packet);
    // Here you would implement logic to pass the packet to the physical layer
    m_phy->SendPacket(packet); // Pass packet to PHY layer for transmission
    NS_LOG_INFO("Sending packet from MAC layer: " << packet);
}

void
SaginMac::ReceivePacket(Ptr<Packet> packet)
{
    NS_LOG_FUNCTION(this << packet);
    NS_LOG_INFO("Received packet at MAC layer: " << packet);

    NS_LOG_INFO("Packet received from compatible node type.");
    // Forward the packet up the stack if callback is set
    if (!m_forwardUpCb.IsNull())
    {
        ForwardUp(packet); // Forward to routing layer
    }
}

void
SaginMac::ForwardUp(Ptr<Packet> packet)
{
    NS_LOG_FUNCTION(this << packet);
    m_forwardUpCb(packet);
}

} // namespace ns3
