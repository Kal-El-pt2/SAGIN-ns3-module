#ifndef SAGIN_MAC_H
#define SAGIN_MAC_H

#include "node-address.h"
//#include "sagin-mac-header.h"
#include "sagin-node.h"
#include "sagin-phy.h"

#include "ns3/event-id.h"
#include "ns3/mac48-address.h"
#include "ns3/nstime.h"
#include "ns3/object.h"
#include "ns3/packet.h"

namespace ns3
{
class SaginNode;
class SaginPhy;

// class NodeType;//updated
class SaginMac : public Object
{
  public:
    static TypeId GetTypeId(void);

    SaginMac();
    SaginMac(Ptr<SaginNode> node);
    SaginMac(Ptr<SaginNode> node, Ptr<SaginPhy> phy); // Modified constructor to take node pointer
    ~SaginMac();

    void SetAddress(Mac48Address address);
    Mac48Address GetAddress(void) const;

    void SetForwardUpCallback(Callback<void, Ptr<Packet>> cb);

    void SendPacket(Ptr<Packet> packet);
    void ReceivePacket(Ptr<Packet> packet);

  private:
    void ForwardUp(Ptr<Packet> packet);

    Mac48Address m_address;
    Ptr<SaginNode> m_node; // Pointer to the parent SaginNode
    Ptr<SaginPhy> m_phy;   // Pointer to the associated PHY layer
    Callback<void, Ptr<Packet>> m_forwardUpCb;
};

} // namespace ns3

#endif // SAGIN_MAC_H
