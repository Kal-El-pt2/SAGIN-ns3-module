#include "space-node.h"
#include "ns3/log.h"
#include "ns3/constant-velocity-mobility-model.h"
#include "ns3/simulator.h"
#include <cmath>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("SpaceNode");
NS_OBJECT_ENSURE_REGISTERED(SpaceNode);

TypeId
SpaceNode::GetTypeId(void) {
  static TypeId tid = TypeId("ns3::SpaceNode")
    .SetParent<SaginNode>()
    .SetGroupName("SAGIN")
    .AddConstructor<SpaceNode>();
  return tid;
}

SpaceNode::SpaceNode(double radius, int uniqueId)
    : SaginNode(uniqueId, NodeType::SPACE_NODE),
      m_radius(radius), m_angleX(0), m_angleY(0), m_updateInterval(1.0)
{
    m_mobility = CreateObject<ConstantVelocityMobilityModel>();
}

SpaceNode::SpaceNode() 
    : SaginNode(0, NodeType::SPACE_NODE),
      m_radius(1.0), m_angleX(0), m_angleY(0), m_updateInterval(1.0)
{
    m_mobility = CreateObject<ConstantVelocityMobilityModel>();
}

SpaceNode::~SpaceNode() {
    if (m_updateEvent.IsPending()) {
        Simulator::Cancel(m_updateEvent);
    }
}

void SpaceNode::SetPosition(double angleX, double angleY) {
  m_angleX = angleX;
  m_angleY = angleY;

  // Calculate Cartesian coordinates based on spherical coordinates
  double x = m_radius * std::cos(m_angleX) * std::cos(m_angleY);
  double y = m_radius * std::cos(m_angleX) * std::sin(m_angleY);
  double z = m_radius * std::sin(m_angleX);

  Vector3D position(x, y, z);
  m_mobility->SetPosition(position);
}

Vector3D SpaceNode::GetPosition(void) const {
  return m_mobility->GetPosition();
}

void SpaceNode::SetVelocity(const Vector& velocity) {
  m_velocity = velocity;
  if (m_mobility->GetObject<ConstantVelocityMobilityModel>()) {
    m_mobility->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(velocity);
  }
}

Vector SpaceNode::GetVelocity(void) const {
  return m_velocity;
}

void SpaceNode::StartOrbitUpdates(double interval) {
    m_updateInterval = interval;
    m_updateEvent = Simulator::Schedule(Seconds(interval), &SpaceNode::UpdatePosition, this);
}

void SpaceNode::UpdatePosition() {
    // Increment orbital angles based on velocity (simplified orbital dynamics)
    m_angleX += m_velocity.x * m_updateInterval;
    m_angleY += m_velocity.y * m_updateInterval;

    // Calculate new position
    double x = m_radius * std::cos(m_angleX) * std::cos(m_angleY);
    double y = m_radius * std::cos(m_angleX) * std::sin(m_angleY);
    double z = m_radius * std::sin(m_angleX);
    Vector3D position(x, y, z);

    m_mobility->SetPosition(position);

    // Log position update
    NS_LOG_INFO("Updated position of SpaceNode " << GetId() << " to " << position);

    // Reschedule the next update
    m_updateEvent = Simulator::Schedule(Seconds(m_updateInterval), &SpaceNode::UpdatePosition, this);
}

} // namespace ns3
