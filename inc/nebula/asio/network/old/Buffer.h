namespace Network
{
	class Buffer
	{
	public:
        int remaining;
		int position;
        
        int result = 0;
        char temp_buffer[sizeof(DataHeader)+SOCK_BUF_LEN];
        int temp_position = 0;
        
        
        
        
        union
        {
            DataHeader header;
            char bufferHeader[sizeof(DataHeader)];
        };
        
        //Data* socketData;
        char bufferData[SOCK_BUF_LEN]; // for receiving
        
        
        bool reading_header;
        
        
        char bufferSend[sizeof(DataHeader)+SOCK_BUF_LEN]; // just for sending
        
        
        
        
        
		int (*errorFunc)( SocketClass*, int );
        
        
        
        SocketBuffer(
            SocketClass* socketClassParam,
            int (*errorFuncParam)( SocketClass*, int ),
            int (*packetFuncParam)( SocketClass* ));
        ~SocketBuffer();
        
        
        
        void castDataToBuffer();
        void castBufferToData();
		void send();
        void recv();
        void route();
	};
    
	SocketBuffer* bufferSend;
    SocketBuffer* bufferRecv;
	
    
	Entity* entity;
    SOCKET s;
    
    
    
	SocketClass(
        Entity* entityParam,
        int (*errorFuncSendParam)( SocketClass*, int ),
        int (*packetFuncSendParam)( SocketClass* ),
        int (*errorFuncRecvParam)( SocketClass*, int ),
        int (*packetFuncRecvParam)( SocketClass* ));
    ~SocketClass();
};

class SocketClassClient: public SocketClass
{
private:
	static int next_client_id;
public:
    GameEngine* gameEngine;
    Entity* entity;
    
	SocketClassClient();
};

        
enum SOCK_MSG_TYPE
{
    SOCKET_DATA_TYPE_INPUT,
    SOCKET_DATA_TYPE_TEXT,
    SOCKET_DATA_TYPE_END_OF_LIST
    /*
    SM_CLI_CREATEGAME, 
    SM_CLI_JOINGAME, 
    SM_CLI_REQUGAME,
    SM_CLI_POSUP,
    SM_CLI_SENDSHOT,
    SM_CLI_EXITGAME,
    SM_CLI_DISCONNECT,
    SM_CLI_CTRLCHANGE,
    SM_CLI_CO,
    SM_SRV_CREATEGAME,
    SM_SRV_JOINGAME, 
    SM_SRV_REQUGAME,
    SM_SRV_POSUP,
    SM_SRV_POSUPALL,
    SM_SRV_VICTIM,
    SM_SRV_CO,
    SM_SRV_BLANK
    */
};

#include "method_socket_buffer.h"
#include "method_SocketClass.h"




/*





struct base {
  virtual size_t size() const =0;
  virtual ~base() { }
};

template<typename T> 
struct intermediate : base {
  virtual size_t size() const { return sizeof(T); }
};

struct derived : intermediate<derived> 
{ };






WOULD THIS WORK???

       |
       V



template<typename T>
struct base {
  size_t size() const { return sizeof(T); }
  virtual ~base() { }
};


struct derived : base<derived> 
{ };




*/









/*

class SD_GEN
{
public:
	Vector3Base x;
	QuaternionBase q;
	Vector3Base v;
	Vector3Base r;
	int int1[8];
	int len;
	Orgtree<NUM_LEVEL>::AddressBase addressBase;
	int id;
	int game_id;
};
class SD_POSUP
{
	struct MARINE_POS
	{
		Vector3Base x;
		QuaternionBase q;
	} marine_pos[10];
	int id[10];
	int len;
};
struct SD_JOIN
{
	int game_id;
	int my_id;
	float health[10];
	int id[10];
	int len;
};
class SD_CO
{
public:
	int creator_id;
	int lower_id;
	OBJECTIVE_DATA<MARINE> data;
};


union
{
	char text[64];
	SD_GEN gen;
	SD_POSUP posup;
	SD_JOIN join;
	SD_CTRLCHANGE cc;
	SD_CO co;
};


*/