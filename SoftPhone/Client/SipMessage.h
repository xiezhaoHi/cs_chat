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
#include "osipparser2/sdp_message.h"
#include <string>
using namespace std;

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
	CMD302,
	CMD400,
	CMD487,
	ByeSip,
	AckSip,
	Unregist,
	CancelSip
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
	void SetAudioBody(bool flag);
	void UnZipString(char *pMsg);
	void SetCallID(char *callID);
	char *GetCallId();
	osip_message_t* GetSipMessage();
protected:
	bool m_audioFlag;
	bool Strdup(char *str,int len);
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
	char *m_toName;
	char *m_body;
	unsigned int m_port;
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
