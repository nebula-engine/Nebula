	TCPServerSocket::TCPServerSocket(unsigned short localPort, int queueLen) throw(SocketException) : Socket(SOCK_STREAM, IPPROTO_TCP) {
setLocalPort(localPort);
setListen(queueLen);
}
	TCPServerSocket::TCPServerSocket(const string &localAddress, unsigned short localPort, int queueLen) throw(SocketException) : Socket(SOCK_STREAM, IPPROTO_TCP) {
setLocalAddressAndPort(localAddress, localPort);
setListen(queueLen);
}
	TCPSocket *TCPServerSocket::accept() throw(SocketException) {
int newConnSD;
if ((newConnSD = ::accept(sockDesc, NULL, 0)) < 0) {
throw SocketException("Accept failed (accept())", true);
}

return new TCPSocket(newConnSD);
}
int	TCPServerSocket::setListen(int queueLen) throw(SocketException) {
if (listen(sockDesc, queueLen) < 0) {
throw SocketException("Set listening socket failed (listen())", true);
}
}












