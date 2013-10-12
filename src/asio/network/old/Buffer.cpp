SocketClass::SocketBuffer::SocketBuffer(
    SocketClass* socketClassParam,
    int (*errorFun30000Param)( SocketClass*, int ),
    int (*packetFun30000Param)( SocketClass* ))
{
    socketClass = socketClassParam;
    
    socketData = NULL;
    buffer = NULL;
    
    errorFun30000 = errorFun30000Param;
    packetFun30000 = packetFun30000Param;
    
    position = 0;
    remaining = 0;
    buffer = &bufferHeader;
}
void SocketClass::SocketBuffer::send( SocketClass* recipient )
{
    if ( errorFun30000 == NULL )
    {
		swprintf_s( msgbox_tchar, _T("SocketClass::SocketBuffer::send error=NULL" ));
        MessageBox( NULL, msgbox_tchar, NULL, 0 );
        return;
    }
    
    
    
    castSocketDataToBuffer();
    
    
    
    int result = send( recipient->s, buffer, socketData.size, 0);
    int error = 0;
    if ( result == SOCKET_ERROR )
    {
        error = WSAGetLastError();
        if ( error != WSAEWOULDBLOCK )
        {
            (*errorFun30000)( recipient, error );
            swprintf_s( msgbox_tchar, _T("SocketClass::SocketBuffer::send %i"), error );
            MessageBox( NULL, msgbox_tchar, NULL, 0 );
        }
    }
}
void SocketClass::SocketBuffer::recv( char* buffer, void (*done)() )
{
	
}
void SocketClass::SocketBuffer::recv()
{
	int result = 0;

    char temp_buffer[SOCK_BUF_LEN];
	int temp_position = 0;
    
	if ( s != INVALID_SOCKET )
	{
		do
		{
			result = recv(s, temp_buffer, SOCK_BUF_LEN, 0);
			if ( result > 0 )
			{
				temp_position = 0;
				while ( temp_position < result )
				{
					if ( remaining > ( result - temp_position ) )
					{
						read = result - temp_position;
					}
					else
					{
						read = remaining;
					}
                    
                    memcpy( &buffer[position], &temp_buf[temp_position], read );
    				
					remaining -= read;
					position += read;
					temp_position += read;
                    
                    if ( remaining == 0 )
                    {
                        if ( buffer == &bufferHeader )
                        {
                            buffer = bufferData;
                            remaining = header.size;
                        }
                        else if ( buffer == bufferData )
                        {
                            route();
                            buffer = bufferHeader;
                            remaining = sizeof(SocketDataHeader);
                        }
                        position = 0;
                    }
				}
			}
			else
			{
				int error = WSAGetLastError();
				if ( error != WSAEWOULDBLOCK )
				{
					swprintf_s( msgbox_tchar, _T("SOCKET_CLASS::rec %i"), error );
					MessageBox( NULL, msgbox_tchar, NULL, 0 );
					(*error_handler)( this, error );
				}
			}
		} while (result > 0);
	}
}



int SocketClass::SocketBuffer::recvControl()
{
    do 
    {
        if ( reading_header )
        {
            recv( &bufferHeader, doneHeader );
        }
        else
        {
            recv( &bufferData, doneData );
        }
    } while ( result > 0 )
}
void SocketClass::SocketBuffer::doneHeader()
{
    
}
void SocketClass::SocketBuffer::doneData()
{
    route();
}
int SocketClass::SocketBuffer::route()
{
    switch ( header.type )
    {
    case SOCKET_DATA_TYPE_INPUT:
        (*route_Input)( socketClass, reinterpret_cast<SocketDataInput*>(&bufferData) );
        break;
    case SOCKET_DATA_TYPE_TEXT:
        (*route_Text)( socketClass, reinterpret_cast<SocketDataText*>(&bufferData) );
        break;
    default:
        
        break;
    }
    return 0;
}



/*

void SocketClass::SocketBuffer::len()
{
    switch ( data.type )
    {
    case SM_CLI_CREATEGAME:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_CLI_JOINGAME:
        data.len = 8 + sizeof(SD_JOIN);
        break;
    case SM_CLI_REQUGAME:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_CLI_POSUP:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_CLI_SENDSHOT:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_CLI_EXITGAME:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_CLI_DISCONNECT:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_CLI_CTRLCHANGE:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_CLI_CO:
        data.len = 8 + sizeof(SD_CO);
        break;
    case SM_SRV_CREATEGAME:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_SRV_JOINGAME:
        data.len = 8 + sizeof(SD_JOIN);
        break;
    case SM_SRV_REQUGAME:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_SRV_POSUP:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_SRV_POSUPALL:
        data.len = 8 + sizeof(SD_POSUP);
        break;
    case SM_SRV_VICTIM:
        data.len = 8 + sizeof(SD_GEN);
        break;
    case SM_SRV_CO:
        data.len = 8 + sizeof(SD_CO);
        break;
    case SM_SRV_BLANK:
        data.len = 8;
        break;
    default:
        MessageBox( NULL, TEXT("SOCKET_BUFFER::len"), NULL, 0 );
        break;
    }
}



int SocketClass::SocketBuffer::route()
{
    switch ( header.type )
    {
    case SM_SRV_POSUP:
        //MessageBox( NULL, TEXT("shouldnt see this"), NULL, 0 );
        break;
    case SM_POSUPALL:
        (*route_Input)( socketClass, reinterpret_cast<SocketDataInput*>(bufferData) );
        //clientEngine->clientGameEngine( server->buffer.data );
        break;
    case SM_SRV_CREATEGAME:
        client_socket_server_create_game();
        break;
    case SM_SRV_JOINGAME:
        client_socket_server_join_game();
        break;
    case SM_SRV_REQUGAME:
         print("games:");
         game_list_len = server->buf.data.gen.len;
		 game_list_offset = 0;
         for ( short a = 0; a < server->buf.data.gen.len; a++ )
         {
             print( "%i", server->buf.data.gen.int1[a] );
			 game_list[a] = server->buf.data.gen.int1[a];
         }
		 menu = MENU_SERVER_JOIN;
         break;
	case SM_SRV_VICTIM:
        client_socket_server_victim();
        break;
    case SM_SRV_CO:
        client_obj_recv_obj();
        break;
    }
    return 0;
}
