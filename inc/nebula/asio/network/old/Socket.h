namespace Network
{
	class Socket
	{
	public:
		Socket(
			int (*errFuncSend)( shared_ptr<Socket*, int ),
			int (*msgFuncSend)( Socket* ),
			int (*errFuncRecv)( Socket*, int ),
			int (*msgFuncRecv)( Socket* ));
		~Socket();

		shared_ptr<Buffer>	m_bufferSend;
		shared_ptr<Buffer>	m_bufferRecv;

		SOCKET				m_s;

	};
};




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
