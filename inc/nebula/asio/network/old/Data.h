namespace Network
{
	struct MsgType
	{
		enum
		{
			eNONE,
			eTEXT
		};
	};

	template<typename T>
	class Msg
	{
	public:
        				Msg()	{ m_type = MsgType::eNONE; }
		virtual			~Msg()	{};
		virtual size_t	Size() { return sizeof(T); }
				int		Type() { return m_type; }
		

				int		m_type;
	};
	class MsgText: public Msg<MsgText>
    {
	public:
				MsgText() { m_type = MsgType::eTEXT; }

		TCHAR	text[64];
	};
	class Header
    {
	public:
        int size;
        int type;
    };
};
