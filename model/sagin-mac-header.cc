#include "sagin-mac-header.h"

#include "ns3/buffer.h"
#include "ns3/log.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("SaginMacHeader");

TypeId
SaginMacHeader::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::SaginMacHeader")
                            .SetParent<Header>()
                            .SetGroupName("Sagin")
                            .AddConstructor<SaginMacHeader>();
    return tid;
}

SaginMacHeader::SaginMacHeader()
{
    NS_LOG_FUNCTION(this);
}

SaginMacHeader::~SaginMacHeader()
{
    NS_LOG_FUNCTION(this);
}

void
SaginMacHeader::SetAddress(Mac48Address address)
{
    m_address = address;
}

Mac48Address
SaginMacHeader::GetAddress(void) const
{
    return m_address;
}

void
SaginMacHeader::Serialize(Buffer::Iterator start) const
{
    NS_LOG_FUNCTION(this << start);
    // Serialize the MAC address by writing it to the buffer as raw bytes
    uint8_t bytes[6];
    m_address.CopyTo(bytes); // Copy the MAC address into a byte array
    for (uint32_t i = 0; i < 6; ++i)
    {
        start.WriteU8(bytes[i]);
    }
}

// uint32_t
// SaginMacHeader::Deserialize(Buffer::Iterator start)
// {
//     NS_LOG_FUNCTION(this << start);
//     // Deserialize the MAC address by reading raw bytes from the buffer
//     uint8_t bytes[6];
//     for (uint32_t i = 0; i < 6; ++i)
//     {
//         bytes[i] = start.ReadU8();
//     }
//     // m_address = Mac48Address::ConvertFrom(bytes);  // Use ConvertFrom method to create
//     // Mac48Address from bytes
//     return GetSerializedSize();
// }

uint32_t
SaginMacHeader::Deserialize(Buffer::Iterator start)
{
    NS_LOG_FUNCTION(this << start);
    uint8_t bytes[6];
    for (uint32_t i = 0; i < 6; ++i)
    {
        bytes[i] = start.ReadU8();
    }
    m_address.CopyFrom(bytes); // Set m_address from byte array
    return GetSerializedSize();
}


uint32_t
SaginMacHeader::GetSerializedSize(void) const
{
    return 6; // Size of the MAC address (6 bytes)
}

} // namespace ns3
