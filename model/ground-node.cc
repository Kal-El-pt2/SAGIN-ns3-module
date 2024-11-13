#include "ground-node.h"
#include "ns3/log.h"
#include "ns3/constant-velocity-mobility-model.h"
#include "ns3/simulator.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("GroundNode");
NS_OBJECT_ENSURE_REGISTERED(GroundNode);

TypeId
GroundNode::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::GroundNode")
                            .SetParent<SaginNode>()
                            .SetGroupName("SAGIN")
                            .AddConstructor<GroundNode>();
    return tid;
}

GroundNode::GroundNode()
    : SaginNode(0, NodeType::GROUND_NODE),
      m_position(Vector(0.0, 0.0, 0.0)),
      m_velocity(Vector(0.0, 0.0, 0.0)),
      m_updateInterval(1.0) // Default update interval in seconds
{
    m_mobility = CreateObject<ConstantVelocityMobilityModel>();
}

GroundNode::GroundNode(int uniqueId)
    : SaginNode(uniqueId, NodeType::GROUND_NODE),
      m_position(Vector(0.0, 0.0, 0.0)),
      m_velocity(Vector(0.0, 0.0, 0.0)),
      m_updateInterval(1.0) // Default update interval in seconds
{
    m_mobility = CreateObject<ConstantVelocityMobilityModel>();
}

GroundNode::~GroundNode()
{
    if (m_updateEvent.IsRunning())
    {
        Simulator::Cancel(m_updateEvent);
    }
}

void
GroundNode::SetPosition(const Vector& position)
{
    m_position = position;
    m_mobility->SetPosition(position);
}

Vector
GroundNode::GetPosition(void) const
{
    return m_mobility->GetPosition();
}

void
GroundNode::SetVelocity(const Vector& velocity)
{
    m_velocity = velocity;
    if (m_mobility->GetObject<ConstantVelocityMobilityModel>())
    {
        m_mobility->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(velocity);
    }
}

Vector
GroundNode::GetVelocity(void) const
{
    return m_velocity;
}

void
GroundNode::StartPositionUpdates(double interval)
{
    m_updateInterval = interval;
    m_updateEvent = Simulator::Schedule(Seconds(interval), &GroundNode::UpdatePosition, this);
}

void
GroundNode::UpdatePosition()
{
    m_position.x += m_velocity.x * m_updateInterval;
    m_position.y += m_velocity.y * m_updateInterval;
    m_position.z += m_velocity.z * m_updateInterval;

    m_mobility->SetPosition(m_position);

    // Log position update
    NS_LOG_INFO("Updated position of GroundNode " << GetId() << " to " << m_position);

    // Reschedule the next update
    m_updateEvent = Simulator::Schedule(Seconds(m_updateInterval), &GroundNode::UpdatePosition, this);
}

} // namespace ns3
