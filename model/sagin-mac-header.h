#ifndef SAGIN_MAC_HEADER_H
#define SAGIN_MAC_HEADER_H

#include "ns3/buffer.h"
#include "ns3/header.h"
#include "ns3/mac48-address.h"

namespace ns3
{

class SaginMacHeader : public Header
{
  public:
    SaginMacHeader();
    virtual ~SaginMacHeader();

    void SetAddress(Mac48Address address);
    Mac48Address GetAddress(void) const;

    // Override the serialization methods
    virtual void Serialize(Buffer::Iterator start) const override;
    virtual uint32_t Deserialize(Buffer::Iterator start) override;
    virtual uint32_t GetSerializedSize(void) const override;

    static TypeId GetTypeId(void);

  private:
    Mac48Address m_address; // MAC address
};

} // namespace ns3

#endif // SAGIN_MAC_HEADER_H
