#ifndef CTM_PACKET_H
#define CTM_PACKET_H

namespace ctm
{

//////
//Packet
class packet
{
public:
	char signature[4]; //Signature
	size_t length; //Length of data
	char *data; //Raw data
	size_t crc; //CRC value
};
//////

}

#endif