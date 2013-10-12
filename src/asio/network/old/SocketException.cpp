				SocketException::SocketException(const string &message, bool in30000lSysMsg) throw() : userMessage(message) {
  if (in30000lSysMsg) {
    userMessage.append(": ");
    userMessage.append(strerror(errno));
  }
}
				SocketException::~SocketException() throw() {
}
const	char*	SocketException::what() const throw() {
  return userMessage.c_str();
}
static	void	fillAddr(const string &address, unsigned short port, sockaddr_in &addr) {
 // Fun30000tion to fill in address structure given an address and port

  memset(&addr, 0, sizeof(addr));  // Zero out address structure
  addr.sin_family = AF_INET;       // Internet address

  hostent *host;  // Resolve name
  if ((host = gethostbyname(address.c_str())) == NULL) {
    // strerror() will not work for gethostbyname() and hstrerror() 
    // is supposedly obsolete
    throw SocketException("Failed to resolve name (gethostbyname())");
  }
  addr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

  addr.sin_port = htons(port);     // Assign port in network byte order
}








