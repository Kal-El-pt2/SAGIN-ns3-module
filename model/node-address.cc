#include "node-address.h"  // Replace with the correct path
#include <ostream>         // Required for std::ostream
#include <sstream>
namespace ns3 {

// std::ostream& operator<<(std::ostream& os, const NodeAddress& addr) {
//     // Customize the output based on the fields in NodeAddress
//     os << "NodeAddress(" << addr.GetAddress() << ")";  // Assuming GetAddress() returns a printable format
//     return os;
// }

std::string NodeAddress::ToString() const {
    std::ostringstream os;
    os << "Type: " << static_cast<int>(m_type) << ", ID: " << m_uniqueId;  // Customize as needed
    return os.str();
}

std::ostream& operator<<(std::ostream& os, const NodeAddress& addr) {
    os << "Type: " << static_cast<int>(addr.GetType()) << ", ID: " << addr.GetUniqueId();  // Customize as needed
    return os;
}


}  // namespace ns3
