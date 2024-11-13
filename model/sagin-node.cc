#include "sagin-node.h"

#include "node-address.h"
#include "sagin-mac.h"
#include "sagin-phy.h"
#include "sagin-routing.h"

#include "ns3/channel.h"
#include "ns3/log.h"
#include "ns3/vector.h"
#include "ns3/simulator.h" // For scheduling events
#include "ns3/double.h"    // For time intervals
#include <atomic>

namespace ns3
{

NS_OBJECT_ENSURE_REGISTERED(SaginNode);
NS_LOG_COMPONENT_DEFINE("SaginNode");

TypeId
SaginNode::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::SaginNode")
                            .SetParent<Node>()
                            .SetGroupName("SAGIN")
                            .AddConstructor<SaginNode>();
    return tid;
}

SaginNode::SaginNode()
    : m_uniqueId(0),                     // or a meaningful default unique ID
      m_address(NodeType::SPACE_NODE, 0), // or a default NodeType value
      m_trafficCount(0)                  // Initialize traffic count to zero
{
    NS_LOG_FUNCTION(this);
    // Additional default setup if necessary
}

SaginNode::SaginNode(int uniqueId, NodeType type)
    : m_uniqueId(uniqueId),
      m_address(type, uniqueId),
      m_trafficCount(0)                  // Initialize traffic count to zero
{
    NS_LOG_FUNCTION(this);

    // Create PHY, MAC, and Routing layers with error handling

    m_phy = CreateObject<SaginPhy>();
    if (!m_phy)
    {
        NS_LOG_ERROR("Failed to create SaginPhy");
        return; // Handle error as appropriate
    }

    m_routing = CreateObject<SaginRouting>(this);
    if (!m_routing)
    {
        NS_LOG_ERROR("Failed to create SaginRouting");
        return; // Handle error as appropriate
    }

    m_mac = CreateObject<SaginMac>(this, m_phy);
    if (!m_mac)
    {
        NS_LOG_ERROR("Failed to create SaginMac");
        return; // Handle error as appropriate
    }

    // Set the node address based on unique ID and type
    SetAddress(uniqueId, type);

    // Connect MAC to Routing layer via forward-up callback
    m_mac->SetForwardUpCallback(MakeCallback(&SaginRouting::ReceivePacket, m_routing));

    // Connect PHY to MAC layer via receive callback
    m_phy->SetReceiveCallback(MakeCallback(&SaginMac::ReceivePacket, m_mac));

    // Initialize any additional attributes or states for the node if necessary
}

SaginNode::~SaginNode()
{
}

void
SaginNode::SetPosition(const Vector& position)
{
    m_position = position;
}

Vector
SaginNode::GetPosition(void) const
{
    return m_position;
}

void
SaginNode::SetVelocity(const Vector& velocity)
{
    m_velocity = velocity;
}

Vector
SaginNode::GetVelocity(void) const
{
    return m_velocity;
}

void
SaginNode::StartMobilityUpdate(double interval)
{
    NS_LOG_FUNCTION(this << interval);
    // Schedule the UpdatePosition function to be called periodically
    Simulator::Schedule(Seconds(interval), &SaginNode::UpdatePosition, this, interval);
}

void
SaginNode::UpdatePosition(double interval)
{
    NS_LOG_FUNCTION(this << interval);
    
    // Update position based on the velocity
    m_position.x += m_velocity.x * interval;
    m_position.y += m_velocity.y * interval;
    m_position.z += m_velocity.z * interval;

    NS_LOG_INFO("Updated position of node " << GetId() << " to " << m_position);

    // Schedule the next update
    Simulator::Schedule(Seconds(interval), &SaginNode::UpdatePosition, this, interval);
}

void
SaginNode::SetUniqueId(int uniqueId)
{
    m_uniqueId = uniqueId;
}

int
SaginNode::GetUniqueId() const
{
    return m_uniqueId;
}

void
SaginNode::SetSignalRange(double range)
{
    m_signalRange = range;
}

double
SaginNode::GetSignalRange() const
{
    return m_signalRange;
}

void
SaginNode::SetNode(Ptr<Node> node)
{
    m_node = node;
}

Ptr<Node>
SaginNode::GetNode(void) const
{
    return m_node;
}

// Set and Get for Routing Layer
void
SaginNode::SetRoutingLayer(Ptr<SaginRouting> routing)
{
    m_routing = routing;
}

Ptr<SaginRouting>
SaginNode::GetRoutingLayer(void) const
{
    return m_routing;
}

// Set and Get for MAC Layer
void
SaginNode::SetMacLayer(Ptr<SaginMac> mac)
{
    m_mac = mac;
}

Ptr<SaginMac>
SaginNode::GetMacLayer(void) const
{
    return m_mac;
}

// Set and Get for PHY Layer
void
SaginNode::SetPhyLayer(Ptr<SaginPhy> phy)
{
    m_phy = phy;
}

Ptr<SaginPhy>
SaginNode::GetPhyLayer(void) const
{
    return m_phy;
}

void
SaginNode::SetAddress(int uniqueId, NodeType type)
{
    m_address = NodeAddress(type, uniqueId);
    m_mac->SetAddress(Mac48Address::Allocate());
}

NodeAddress
SaginNode::GetAddress() const
{
    return m_address;
}

void
SaginNode::SendPacket(Ptr<Packet> packet, NodeAddress destination)
{
    NS_LOG_FUNCTION(this << packet << destination);

    // Increment traffic count when processing a new packet
    m_trafficCount.store(m_trafficCount.load() + 1);

    // Check if the destination is on the same node type
    if (destination.GetType() == m_address.GetType())
    {
        // Directly forward to MAC for local delivery
        m_mac->ReceivePacket(packet);
    }
    else
    {
        // Use routing layer for inter-node type communication
        m_routing->RoutePacket(packet, destination);
    }

    // Decrement traffic count after processing the packet
    m_trafficCount.store(m_trafficCount.load() - 1);
}

void
SaginNode::ReceivePacket(Ptr<Packet> packet)
{
    NS_LOG_FUNCTION(this << packet);
    NS_LOG_INFO("Packet received at node: " << GetId());

    // Increment traffic count when a packet is received
    m_trafficCount.store(m_trafficCount.load() + 1);

    // Additional processing for received packet at application layer if needed

    // Decrement traffic count after packet processing
    m_trafficCount.store(m_trafficCount.load() - 1);
}

// Getter for traffic count
int
SaginNode::GetTrafficCount() const
{
    return m_trafficCount.load();
}

} // namespace ns3
