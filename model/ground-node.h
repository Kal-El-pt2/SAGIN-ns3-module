#ifndef GROUND_NODE_H
#define GROUND_NODE_H

#include "sagin-node.h"
#include "ns3/vector.h"
#include "ns3/mobility-model.h"

namespace ns3
{

class GroundNode : public SaginNode
{
public:
    static TypeId GetTypeId(void);

    GroundNode();
    GroundNode(int uniqueId);
    ~GroundNode();

    void SetPosition(const Vector& position);
    Vector GetPosition(void) const;

    void SetVelocity(const Vector& velocity);
    Vector GetVelocity(void) const;

    void StartPositionUpdates(double interval);

private:
    Vector m_position;               // 3D position: (x, y, z) as Vector
    Vector m_velocity;               // Velocity vector
    Ptr<MobilityModel> m_mobility;   // Mobility model for dynamic movement
    EventId m_updateEvent;           // Event to periodically update position
    double m_updateInterval;         // Interval for position updates

    void UpdatePosition();           // Method to periodically update position
};

} // namespace ns3

#endif // GROUND_NODE_H
