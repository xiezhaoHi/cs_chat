// SipMessage.h: interface for the CSipMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIPMESSAGE_H__1B23AA72_24FF_4FCE_809C_6B1AE85B3F1A__INCLUDED_)
#define AFX_SIPMESSAGE_H__1B23AA72_24FF_4FCE_809C_6B1AE85B3F1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "osipparser2/osip_parser.h"
#include "osipparser2/osip_message.h"

#define CALLID_LEN 32
#define TAG_LEN 10
#define BRANCH_LEN 12

enum SipMode{
	Regist,
	Invoid,
	Regist200,
	Invoid200,
	CMD100,
	CMD180,
	CMD400,
	Bye,
	Ack,
	Unregist
};

class CSipMessage  
{
public:
	CSipMessage();
	virtual ~CSipMessage();
	void SetRemoteAdd(char *ip,unsigned int ipLen,unsigned int port);
	void SetLocalAdd(char *ip,unsigned int ipLen,unsigned int port);
	void SetUserInfo(char *name,unsigned int nameLen,char *password,unsigned int pwdLen);
	void SetRemoteName(char *name,unsigned int nameLen);
	void GetSipMessage(char *msgStr,unsigned int *len,SipMode mode);
	void SetMsgBody(char *buf,unsigned int len);
	void NewCallIDTag();
protected:
//	int GetRegistStr(char *registStr,unsigned int *len);
//	int GetInvoidStr(char *InvoidStr,unsigned int *len);
// 	int GetReg200Str(char *registStr,unsigned int *len);
// 	int GetInv200Str(char *registStr,unsigned int *len);
// 	int GetCMD100Str(char *registStr,unsigned int *len);
// 	int GetCMD180Str(char *registStr,unsigned int *len);
// 	int GetCMD400Str(char *registStr,unsigned int *len);
// 	int GetByeStr(char *registStr,unsigned int *len);
// 	int GetAckStr(char *registStr,unsigned int *len);
// 	int GetUnRegist(char *registStr,unsigned int *len);
	int GetReqStr(char *registStr,unsigned int *len,SipMode mode);
	int GetAnwStr(char *registStr,unsigned int *len,SipMode mode);
	void InitNormalInfo();
	void MessageInit();
	void GetRandomString(char *str,unsigned int len);
	osip_message_t *m_pMessage;
	char *m_remoteIp;
	char *m_localIp;
	char *m_name;
	char *m_password;
	char *m_remoteName;
	char *m_body;
	char m_callID[CALLID_LEN+1];
	char m_tag[TAG_LEN+1];
	char m_branch[BRANCH_LEN+1];
	SipMode m_sipMode;
	unsigned int m_bodyLen;
	unsigned int m_count;
	unsigned int m_remotePort;
	unsigned int m_localPort;
};

#endif // !defined(AFX_SIPMESSAGE_H__1B23AA72_24FF_4FCE_809C_6B1AE85B3F1A__INCLUDED_)
