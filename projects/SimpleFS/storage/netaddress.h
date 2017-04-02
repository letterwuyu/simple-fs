#ifndef __NETADDRESS_H__
#define __NETADDRESS_H__
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
class NetAddress {
public:
	typedef port_type int;
	NetAddress(std::string& address, port_type port);
	NetAddress(struct sockaddr_in& sin);
	NetAddress(const NetAddress& net_address);
	NetAddress(NetAddress&& net_address) noexcept;
	NetAddress& operator=(const NetAddress& rhs);
	NetAddress& operator=(NetAddress&& rhs)noexcept;
	friend bool operator==(const NetAddress& lhs, const NetAddress& rhs);
	friend bool operator!=(const NetAddress& lhs, const NetAddress& rhs);
	friend std::ostream& std::ostream<<(std::ostream& os, const NetAddress& net_address);
	friend std::istream& std::istream>>(std::ostream& is, NetAddress& net_address);

	const std::string& GetAddress() const;
	const port_type GetPort() const;
	const struct sockaddr_in GetSockaddrIn() const;
private:
	std::string address_;
	port_type port_;
};

bool operator==(const NetAddress& lhs, const NetAddress& rhs);
bool operator!=(const NetAddress& lhs, const NetAddress& rhs);
std::ostream& std::ostream<<(std::ostream& os, const NetAddress& net_address);
std::istream& std::istream>>(std::ostream& is, NetAddress& net_address);
#endif /* __NETADDRESS_H__ */
