#ifndef MESSAGE_Q
#define MESSAGE_Q


#define WRTIE_MSG 1
#define GET_MSG 2

#pragma pack (push, 1)
struct message_t{
	char* data;
	size_t size;
};
#pragma pack (pop)

#endif
