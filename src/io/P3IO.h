#ifndef P3IO_H
#define P3IO_H

#include "ProductInfo.h" // Used to look for PRODUCT_ID_BARE which means STEPMANIA 5, NOT OITG
#include <stdint.h>
#include "io/USBDriver.h"
#include "arch/ACIO/ACIO.h"

#define DDR_PAD_UP 0xFD
#define DDR_PAD_DOWN 0xFB
#define DDR_PAD_LEFT 0xF7
#define DDR_PAD_RIGHT 0xEF
#define DDR_CP_LEFT 0xBF
#define DDR_CP_SELECT 0xFE
#define DDR_CP_RIGHT 0x7F
#define DDR_CP_UP_P1 0xFE //byte 4
#define DDR_CP_UP_P2 0xFB //byte 4
#define DDR_CP_DOWN_P1 0xFD // byte 4
#define DDR_CP_DOWN_P2 0xF7 // byte 4
#define DDR_TEST 0xBF //byte 4?
#define DDR_SERVICE 0xEF //byte 4?
#define DDR_COIN	0xDF

#define BIT(i) (1<<(i))
#define BIT_IS_SET(v,i) ((v&BIT(i))!=0)
#define BYTE_BIT_M_TO_L(i) (1<<(7-i))
#define BYTE_BIT_IS_SET_M_TO_L(v,i) ((v&BIT(7-i))!=0)


	#define HDXB_INIT 0x28 //init?
	#define HDXB_SET_LIGHTS 0x12

#ifdef PRODUCT_ID_BARE
#define PSTRING std::string
#else
#define PSTRING CString
#endif

class P3IO : public USBDriver
{
public:
	static bool DeviceMatches(int iVendorID, int iProductID);
	bool Open();

	bool interruptRead(uint8_t* data);
	bool writeLights(uint8_t* payload);
	bool openHDXB();
	bool sendUnknownCommand();
	bool initHDXB();
	bool pingHDXB();
	bool spamBaudCheck();
	bool writeHDXB(uint8_t* payload, int len, uint8_t opcode=HDXB_SET_LIGHTS);
	bool readHDXB(int len=0x7e);
	void HDXBAllOnTest();

	void Reconnect();


	/* Globally accessible for diagnostics purposes. */
	static int m_iInputErrorCount;
	static PSTRING m_sInputError;


private:
	int GetResponseFromBulk(uint8_t* response, int response_length);
	bool WriteToBulkWithExpectedReply(uint8_t* message, bool init_packet);
	uint8_t checkInput(uint8_t x, uint8_t y);
	void InitHDAndWatchDog();

	static uint8_t acio_request[256];
	static uint8_t acio_response[256];

};

#endif /* P3IO_H */

