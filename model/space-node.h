#ifndef SPACE_NODE_H
#define SPACE_NODE_H

#include "sagin-node.h"
#include "ns3/vector.h"
#include "ns3/mobility-model.h"

namespace ns3 {

class SpaceNode : public SaginNode {
public:
  static TypeId GetTypeId (void);

  SpaceNode(double radius, int uniqueId);
  SpaceNode ();
  
  ~SpaceNode ();

  void SetPosition(double angleX, double angleY);
  Vector3D GetPosition(void) const;

  void SetVelocity(const Vector& velocity);
  Vector GetVelocity(void) const;

  void StartOrbitUpdates(double interval);

private:
  double m_radius;             // Fixed radial distance from Earth’s center
  double m_angleX;             // Angle in X-axis for orbital position
  double m_angleY;             // Angle in Y-axis for orbital position
  Vector m_velocity;           // Velocity vector
  Ptr<MobilityModel> m_mobility; // Mobility model for orbital path
  EventId m_updateEvent;       // Event for periodic orbital updates
  double m_updateInterval;     // Interval for updating orbital position

  void UpdatePosition();       // Method to periodically update orbital position
};

} // namespace ns3

#endif /* SPACE_NODE_H */
