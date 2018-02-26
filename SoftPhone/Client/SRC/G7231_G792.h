// G7231_G792.h: interface for the CG7231_G792 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G7231_G792_H__BCE7ACDE_D1FD_4362_B974_2E5045E58605__INCLUDED_)
#define AFX_G7231_G792_H__BCE7ACDE_D1FD_4362_B974_2E5045E58605__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum CodeType
{
	G729,
	G7231,
};

class CG7231_G792  
{
public:
	
	CG7231_G792(CodeType codeType = G729);
	virtual ~CG7231_G792();
	
	void SetCodeType(CodeType codeType);
	void InitEncode();
	void InitDecode();
	void Encode(char* rawData, char* Data);
	void Decode(char* Data, char* rawData);

private:
	CodeType m_CodeType;
};

#endif // !defined(AFX_G7231_G792_H__BCE7ACDE_D1FD_4362_B974_2E5045E58605__INCLUDED_)
