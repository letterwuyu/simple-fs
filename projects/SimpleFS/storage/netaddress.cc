#include "netaddress.h"

NetAddress::Netaddress(std::string& address, NetAddress::port_type port):
	address_(address), port_(port) {}

NetAddress::NetAddress(struct sockaddr_in& sin):
	address_(inet_ntoa(sin.sin_addr)), port_(sin.sin_port) {}

NetAddress(const NetAddress& net_address):
	address_(net_address.GetAddress()), port_(net_address.GetPort()) {}

NetAdress(NetAddress&& net_address) noexcept:
	address_(net_address.GetAddress()), port_(net_address.GetPort()) {}

const std::string& NetAddress::GetAddress() const
{
	return address_;
}

const NetAddress::port_type NetAddress::GetPort() const
{
	return port_;
}

const struct sockaddr_in NetAddress::GetSockaddrIn() const
{
	struct sockaddr_in sin;
	sin.family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(address_.c_str());
	sin.sin_port = htons(port_);
	return sin;
}

NetAddress& NetAddress::operator=(const NetAddress& rhs)
{
	if(&rhs != this)
	{
		this.address_ = rhs.GetAddress();
		this.port_ = rhs.GetPort();
	}
	return *this;
}

NetAddress& NetAddress::operator=(NetAddress&& rhs) noexcept
{
	if(&rhs != this)
	{
		this.address_ = rhs.GetAddress();
		this.port_ = rhs.GetPort();
	}
	return *this;
}

bool operator==(const NetAddress& lsh, const NetAddress& rhs)
{
	return lsh.address_ == rhs.address_ && lsh.port_ == rhs.port_;
}

bool operator!=(const NetAddress& lsh, const NetAddress& rhs)
{
	return !(lsh == rhs);
}

std::ostream& std::ostream<<(std::ostream& os, const NetAddress& net_address)
{
	os << net_address.string_ << net_address.port_;
	return os;	
}

std::istream std::istream>>(std::istream& is, NetAddress& net_address)
{
	is >> net_address.string_ >> net_address.port_;
	return is;
}
























