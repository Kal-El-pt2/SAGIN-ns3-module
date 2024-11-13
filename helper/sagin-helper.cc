#include "sagin-helper.h"
#include "ground-node.h"
#include "aerial-node.h"
#include "space-node.h"
#include "ns3/vector.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("SaginHelper");

SaginHelper::SaginHelper() {
  // Constructor implementation
}

SaginHelper::~SaginHelper() {
  // Destructor implementation
}

Ptr<GroundNode> SaginHelper::CreateGroundNode(const Vector &position) {
  Ptr<GroundNode> groundNode = CreateObject<GroundNode>();
  // Adjust for 2D by setting z=0
  groundNode->SetPosition(Vector(position.x, position.y, 0.0));  // Set z to 0 for 2D positioning
  m_groundNodes.Add(groundNode);
  return groundNode;
}

Ptr<AerialNode> SaginHelper::CreateAerialNode(const Vector &position, AerialType type) {
  Ptr<AerialNode> aerialNode = CreateObject<AerialNode>(type);
  aerialNode->SetPosition(position);  // AerialNode uses 3D position
  m_aerialNodes.Add(aerialNode);
  return aerialNode;
}

Ptr<SpaceNode> SaginHelper::CreateSpaceNode(const Vector &position) {
  Ptr<SpaceNode> spaceNode = CreateObject<SpaceNode>();
  // Pass x and y coordinates separately, assuming SetPosition expects double values
  spaceNode->SetPosition(position.x, position.y);  // Using spherical coordinates or 2D space
  m_spaceNodes.Add(spaceNode);
  return spaceNode;
}

}  // namespace ns3
