#include "sagin-helper.h"

#include "ns3/core-module.h"
#include "ns3/vector.h"
// #include "ns3/internet-module.h"
// #include "ns3/point-to-point-module.h"
// #include "ns3/applications-module.h"
// #include "sagin-routing.h"

#include "ns3/network-module.h"

using namespace ns3;

int
main(int argc, char* argv[])
{
    // // Create a SaginHelper instance
    // SaginHelper sagin;

    // // Create nodes using helper
    // Ptr<GroundNode> groundNode = sagin.CreateGroundNode(Vector(0, 0, 0));
    // Ptr<AerialNode> aerialNode = sagin.CreateAerialNode(Vector(100, 100, 100), UAV);
    // Ptr<SpaceNode> spaceNode = sagin.CreateSpaceNode(Vector(500, 500, 500));

    // // Install Internet stack on these nodes
    // InternetStackHelper internet;
    // internet.Install(groundNode);
    // internet.Install(aerialNode);
    // //internet.Install(spaceNode); //if using space node

    // // Set up Point-to-Point channel
    // PointToPointHelper p2p;
    // p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    // p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    // NetDeviceContainer devices;
    // devices = p2p.Install(groundNode, aerialNode); // Connect ground and aerial nodes

    // // Assign IP addresses
    // Ipv4AddressHelper ipv4;
    // ipv4.SetBase("10.1.1.0", "255.255.255.0");
    // Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);

    // // Application Setup
    // uint16_t port = 9; // Choose a port number
    // UdpEchoServerHelper echoServer(port);
    // ApplicationContainer serverApps = echoServer.Install(groundNode);
    // serverApps.Start(Seconds(1.0));
    // serverApps.Stop(Seconds(10.0));

    // UdpEchoClientHelper echoClient(interfaces.GetAddress(0), port);
    // echoClient.SetAttribute("MaxPackets", UintegerValue(1));
    // echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    // echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    // ApplicationContainer clientApps = echoClient.Install(aerialNode);
    // clientApps.Start(Seconds(2.0));
    // clientApps.Stop(Seconds(10.0));

    // // Run the simulation
    // Simulator::Run();
    // Simulator::Destroy();

    return 0;
}
