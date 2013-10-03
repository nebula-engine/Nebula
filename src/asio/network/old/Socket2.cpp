SocketClass::SocketClass(
    Entity* entityParam,
    int (*errorFuncSendParam)( SocketClass*, int ),
    int (*packetFuncSendParam)( SocketClass* ),
    int (*errorFuncRecvParam)( SocketClass*, int ),
    int (*packetFuncRecvParam)( SocketClass* ));
{
    entity = entityParam;
    s = INVALID_SOCKET;
    
    bufferSend = new SocketBuffer( this, errorFuncSendParam, packetFuncSendParam );
    bufferRecv = new SocketBuffer( this, errorFuncRecvParam, packetFuncRecvParam );
}

