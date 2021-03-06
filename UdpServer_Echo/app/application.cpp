#include <user_config.h>
#include <SmingCore/SmingCore.h>

// Put you SSID and Password here
#define WIFI_SSID "PleaseEnterSSID"
#define WIFI_PWD "PleaseEnterPassword"

void onReceive(UdpConnection& connection, char *data, int size, IPAddress remoteIP, uint16_t remotePort); // Declaration


// UDP server
const uint16_t EchoPort = 1234;
UdpConnection udp(onReceive);


void onReceive(UdpConnection& connection, char *data, int size, IPAddress remoteIP, uint16_t remotePort)
{
	debugf("UDP Sever callback from %s:%d, %d bytes", remoteIP.toString().c_str(), remotePort, size);

	// We implement string mode server for example
	Serial.print(">\t");
	Serial.print(data);

	// Send echo to remote sender
	String text = String("echo: ") + data;
	udp.sendStringTo(remoteIP, EchoPort, text);
}

void onConnected()
{
	udp.listen(EchoPort);

	Serial.println("\r\n=== UDP SERVER STARTED ===");
	Serial.print(WifiStation.getIP().toString()); Serial.print(":"); Serial.println(EchoPort);
	Serial.println("=============================\r\n");

	//udp.connect(IPAddress(192, 168, 1, 180), 1234);
	//udp.sendString("Hello!");
}

void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true);

	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiStation.waitConnection(onConnected);
}
