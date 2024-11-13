#ifndef SAGIN_NODE_H
#define SAGIN_NODE_H

/**
 * \defgroup sagin Description of the SAGIN module
 */

#include "node-address.h"
#include "sagin-mac.h"
#include "sagin-phy.h"
#include "sagin-routing.h"

#include "ns3/node.h"
#include "ns3/vector.h"
#include <atomic>

namespace ns3
{

// Forward declarations for PHY, MAC, and Routing layers
class SaginMac;
class SaginPhy;
class SaginRouting;

/**
 * \ingroup sagin
 * \brief Represents a node in the Space-Air-Ground Integrated Network (SAGIN)
 */
class SaginNode : public Node
{
public:
    static TypeId GetTypeId(void);

    // Constructors and Destructor
    SaginNode(int uniqueId, NodeType type = NodeType::SPACE_NODE);
    SaginNode();
    ~SaginNode();

    // Position setters and getters
    void SetPosition(const Vector& position);
    Vector GetPosition(void) const;

    // Velocity setters and getters
    void SetVelocity(const Vector& velocity);
    Vector GetVelocity(void) const;

    // Mobility update functions
    void StartMobilityUpdate(double interval);  // Start periodic updates
    void UpdatePosition(double interval); // Update position based on velocity

    // Unique ID setters and getters
    void SetUniqueId(int uniqueId);
    int GetUniqueId() const;

    // Address setters and getters
    NodeAddress GetAddress() const;
    void SetAddress(int uniqueId, NodeType type);

    // Signal range setters and getters
    void SetSignalRange(double range);
    double GetSignalRange() const;

    // Node pointer setters and getters
    void SetNode(Ptr<Node> node);
    Ptr<Node> GetNode(void) const;

    // Setters and getters for Routing, MAC, and PHY layers
    void SetRoutingLayer(Ptr<SaginRouting> routing);
    Ptr<SaginRouting> GetRoutingLayer(void) const;

    void SetMacLayer(Ptr<SaginMac> mac);
    Ptr<SaginMac> GetMacLayer(void) const;

    void SetPhyLayer(Ptr<SaginPhy> phy);
    Ptr<SaginPhy> GetPhyLayer(void) const;

    // Traffic count getter
    int GetTrafficCount() const;

    // Packet sending and receiving methods
    void SendPacket(Ptr<Packet> packet, NodeAddress destination);
    void ReceivePacket(Ptr<Packet> packet);

protected:
    int m_uniqueId;                  // Unique identifier for the node
    NodeAddress m_address;           // Address of the node
    Vector m_position;               // 3D position of the node
    Vector m_velocity;               // Velocity vector for the node's movement
    double m_signalRange;            // Signal range in meters
    Ptr<Node> m_node;                // Pointer to the node
    Ptr<SaginRouting> m_routing;     // Routing layer
    Ptr<SaginMac> m_mac;             // MAC layer
    Ptr<SaginPhy> m_phy;             // PHY layer
    std::atomic<int> m_trafficCount; // Tracks current traffic being processed
};

} // namespace ns3

#endif /* SAGIN_NODE_H */
