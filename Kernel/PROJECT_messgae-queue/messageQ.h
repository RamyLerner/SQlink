#ifndef MESSAGE_Q
#define MESSAGE_Q


#define WRITE_MSG 150
#define GET_MSG 151

#pragma pack (push, 1)
struct message_t{
	char* data;
	size_t size;
};
#pragma pack (pop)

#endif
