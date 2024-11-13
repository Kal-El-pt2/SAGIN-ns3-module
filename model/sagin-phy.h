#ifndef SAGIN_PHY_H
#define SAGIN_PHY_H

#include "sagin-mac.h"
#include "sagin-node.h"
#include "sagin-routing.h" // Include this header file

#include "ns3/callback.h"
#include "ns3/core-module.h"
#include "ns3/nstime.h"
#include "ns3/object.h"
#include "ns3/packet.h"

namespace ns3
{

class SaginMac;   // Forward declaration of SaginMac
class SaginNode;  // Forward declaration of SaginNode
class SaginRouting; // Forward declaration (no class definition here)

class SaginPhy : public Object
{
  public:
    static TypeId GetTypeId(void);

    SaginPhy();
    SaginPhy(Ptr<SaginMac> mac); // Constructor with MAC pointer
    ~SaginPhy();

    void SetTransmissionPower(double power);
    double GetTransmissionPower() const;

    void SetPropagationDelay(Time delay);
    Time GetPropagationDelay() const;

    void SetReceiveCallback(Callback<void, Ptr<Packet>> cb);

    void SendPacket(Ptr<Packet> packet);
    void ReceivePacket(Ptr<Packet> packet);
    std::vector<Ptr<SaginNode>> GetNodesInRange();

  private:
    void ForwardPacketUp(Ptr<Packet> packet);

    double m_transmissionPower;
    Time m_propagationDelay;
    Callback<void, Ptr<Packet>> m_receiveCallback;
    Ptr<SaginMac> m_mac; // Pointer to the MAC layer for upward communication
};

} // namespace ns3

#endif // SAGIN_PHY_H
