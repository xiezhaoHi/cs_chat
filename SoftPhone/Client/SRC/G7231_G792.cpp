// G7231_G792.cpp: implementation of the CG7231_G792 class.
//
//////////////////////////////////////////////////////////////////////
#include "G7231_G792.h"
extern "C"
{
#include "../SRC/G729/va_g729a.h"
#include "../SRC/G7231/typedef.h"
#include "../SRC/G7231/cst_lbc.h"
#include "../SRC/G7231/decod.h"
#include "../SRC/G7231/coder.h"
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CG7231_G792::CG7231_G792(CodeType codeType/* = G729*/)
{
	m_CodeType = codeType;
}

CG7231_G792::~CG7231_G792()
{

}

void CG7231_G792::SetCodeType(CodeType codeType)
{
	m_CodeType = codeType;
}

void CG7231_G792::InitEncode()
{
	if (m_CodeType == G729)
	{
		va_g729a_init_encoder();
	}
	else if (m_CodeType = G7231)
	{
		Init_Coder();
	}
}

void CG7231_G792::InitDecode()
{
	if (m_CodeType == G729)
	{
		va_g729a_init_decoder();
	}
	else if (m_CodeType == G7231)
	{
		Init_Decod();
	}
}

void CG7231_G792::Encode(char* rawData, char* Data)
{
	if (m_CodeType == G729)
	{
		va_g729a_encoder((short *)rawData, (unsigned char*)Data);
	}
	else if (m_CodeType == G7231)
	{
		::Coder((short*)rawData, (char *)Data);
	}
}

void CG7231_G792::Decode(char* Data, char* rawData)
{
	if (m_CodeType == G729)
	{
		va_g729a_decoder((unsigned char *)rawData, (short *)Data, 0);
	}
	else if (m_CodeType == G7231)
	{
		::Decod((short *)rawData, (char *)Data, 0);
	}
}