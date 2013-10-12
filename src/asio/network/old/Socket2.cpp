SocketClass::SocketClass(
    Entity* entityParam,
    int (*errorFun30000SendParam)( SocketClass*, int ),
    int (*packetFun30000SendParam)( SocketClass* ),
    int (*errorFun30000RecvParam)( SocketClass*, int ),
    int (*packetFun30000RecvParam)( SocketClass* ));
{
    entity = entityParam;
    s = INVALID_SOCKET;
    
    bufferSend = new SocketBuffer( this, errorFun30000SendParam, packetFun30000SendParam );
    bufferRecv = new SocketBuffer( this, errorFun30000RecvParam, packetFun30000RecvParam );
}

