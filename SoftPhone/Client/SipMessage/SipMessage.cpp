// SipMessage.cpp: implementation of the CSipMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "SipMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSipMessage::CSipMessage()
{
	m_pMessage = NULL;
	m_remoteIp = NULL;
	m_localIp = NULL;
	m_name = NULL;
	m_password = NULL;
	m_count = 0;
	m_bodyLen = 0;
	m_body = NULL;
// 	m_callID = NULL;
// 	m_tag = NULL;
// 	m_branch = NULL;
}

CSipMessage::~CSipMessage()
{
	if (m_remoteIp != NULL)
	{
		delete[] m_remoteIp;
	}
	if (m_localIp != NULL)
	{
		delete[] m_localIp;
	}	
	if (m_name != NULL)
	{
		delete[] m_localIp;
	}	
	if (m_password != NULL)
	{
		delete[] m_localIp;
	}
// 	if (m_callID != NULL)
// 	{
// 		delete[] m_callID;
// 	}
// 	if (m_tag != NULL)
// 	{
// 		delete[] m_tag;
// 	}
// 	if (m_branch != NULL)
// 	{
// 		delete[] m_branch;
// 	}
}

void CSipMessage::SetRemoteAdd(char *ip,unsigned int ipLen,unsigned int port)
{
	if (m_remoteIp != NULL)
	{
		delete[] m_remoteIp;
		m_remoteIp = NULL;
	}
	m_remoteIp = new char[ipLen+1];
	memset(m_remoteIp,'\0',ipLen);
	strncpy(m_remoteIp,ip,ipLen+1);
	m_remotePort = port;
}

void CSipMessage::SetLocalAdd(char *ip,unsigned int ipLen,unsigned int port)
{
	if (m_localIp != NULL)
	{
		delete[] m_localIp;
		m_localIp = NULL;
	}
	m_localIp = new char[ipLen+1];
	memset(m_localIp,'\0',ipLen);
	strncpy(m_localIp,ip,ipLen+1);
	m_localPort = port;
}

void CSipMessage::SetRemoteName(char *name,unsigned int nameLen)
{
	if (m_remoteName != NULL)
	{
		delete[] m_remoteName;
		m_remoteName = NULL;
	}
	m_remoteName = new char[nameLen+1];
	memset(m_remoteName,'\0',nameLen);
	strncpy(m_remoteName,name,nameLen+1);
}

void CSipMessage::SetUserInfo(char *name,unsigned int nameLen,
							  char *password,unsigned int pwdLen)
{
	if (m_name != NULL)
	{
		delete[] m_name;
		m_name = NULL;
	}
	if (m_password != NULL)
	{
		delete[] m_password;
		m_password = NULL;
	}
	m_name = new char[nameLen+1];
	memset(m_name,'\0',nameLen);
	strncpy(m_name,name,nameLen+1);

	m_password = new char[pwdLen+1];
	memset(m_password,'\0',pwdLen);
	strncpy(m_password,password,pwdLen+1);
}
/*
int CSipMessage::GetRegistStr(char *registStr,unsigned int *len)
{
	MessageInit();
	m_count++;
	char count[10] = {0};
	//////////////////////////////////////////////////////////////////////////
	// MessageInit()
	//////////////////////////////////////////////////////////////////////////	
	m_pMessage->sip_method = strdup("REGISTER");
	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	//	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	sprintf(count,"%d",m_count);
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	osip_cseq_set_method(m_pMessage->cseq,osip_strdup("REGISTER"));
	char *str = NULL;
 	unsigned int strlen = 0;
	osip_message_to_str(m_pMessage,&str,&strlen);
	memset(registStr,'\0',*len);
	strncpy(registStr,str,*len);
	osip_message_free(m_pMessage);
	return strlen;
}

int CSipMessage::GetInvoidStr(char *InvoidStr,unsigned int *len)
{
	MessageInit();
	m_count++;
	//////////////////////////////////////////////////////////////////////////
	// MessageInit()
	//////////////////////////////////////////////////////////////////////////	
	m_pMessage->sip_method = strdup("INVITE");
	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	//	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	char count[10] = {0};
	sprintf(count,"%d",m_count);
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	osip_cseq_set_method(m_pMessage->cseq,osip_strdup("INVITE"));
	char *str = NULL;
 	unsigned int strlen = 0;
	osip_message_to_str(m_pMessage,&str,&strlen);
	memset(InvoidStr,'\0',*len);
	strncpy(InvoidStr,str,*len);
	osip_message_free(m_pMessage);
	return strlen;
}
*/
int CSipMessage::GetReqStr(char *registStr,unsigned int *len,SipMode mode)
{
	MessageInit();
	m_count++;
	//////////////////////////////////////////////////////////////////////////
	// MessageInit()
	//////////////////////////////////////////////////////////////////////////	
//	m_pMessage->sip_method = strdup("INVITE");
	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	//	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	char count[10] = {0};
	sprintf(count,"%d",m_count);
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	switch(mode)
	{
	case Regist:
		m_pMessage->sip_method = strdup("Regist");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("Regist"));
		break;
	case Invoid:
		m_pMessage->sip_method = strdup("INVITE");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("INVITE"));
		break;
	case Bye:
		m_pMessage->sip_method = strdup("Bye");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("Bye"));
		break;
	case Ack:
		m_pMessage->sip_method = strdup("Ack");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("Ack"));
		break;
	case Unregist:
		m_pMessage->sip_method = strdup("regist");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("regist"));
//////////////////////////////////////////////////////////////////////////
//²¹³äUNregisted
//////////////////////////////////////////////////////////////////////////
		break;
	default:
	    break;
	}
	char *str = NULL;
 	unsigned int strlen = 0;
	osip_message_to_str(m_pMessage,&str,&strlen);
	memset(registStr,'\0',*len);
	strncpy(registStr,str,*len);
	osip_message_free(m_pMessage);
	return strlen;
}

void CSipMessage::GetRandomString(char *str,const unsigned int len)
{
	unsigned int strLen = len;
	char *tStr = new char[strLen];
	memset(tStr,'\0',strLen);
	const int SIZE_CHAR = strLen;  //Éú³ÉSIZE_CHARÎ»C Style×Ö·û´®
	const char CCH[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	srand((unsigned)time(NULL));
	for (int i = 0; i < SIZE_CHAR; ++i)
	{
		int x = rand() % (sizeof(CCH) - 1);  
		tStr[i] = CCH[x];
	}
 	strncpy(str,tStr,strLen);
	delete[] tStr;
}

void CSipMessage::NewCallIDTag()
{
	GetRandomString(m_callID,CALLID_LEN);
	GetRandomString(m_tag,TAG_LEN);
	GetRandomString(m_branch,BRANCH_LEN);
}

void CSipMessage::MessageInit()
{
	osip_message_init(&m_pMessage);
	if(NULL == m_pMessage)
	{
		ASSERT(0);
	}
//	if (m_sipMode == Invoid || m_sipMode == Regist)
//	{
		if(osip_uri_init(&m_pMessage->req_uri) != 0)
		{
			ASSERT(0);
		}
//	}


	if( osip_to_init(&(m_pMessage->to)) != 0)
	{
		ASSERT(0);
	}

	if(osip_from_init(&(m_pMessage->from)) != 0)
	{
		ASSERT(0);
	}
	osip_uri_init(&(m_pMessage->to->url));
	osip_uri_init(&(m_pMessage->from->url));
	osip_cseq_init(&(m_pMessage->cseq));
}

void CSipMessage::InitNormalInfo()
{
	char port[10] = {0};
	//////////////////////////////////////////////////////////////////////////
	osip_uri_set_username(m_pMessage->req_uri,osip_strdup(m_name));
 	osip_uri_set_password(m_pMessage->req_uri,osip_strdup(m_password)); 	
	m_pMessage->sip_version = strdup("SIP/2.0");
	osip_uri_set_host(m_pMessage->req_uri,osip_strdup(m_remoteIp));	
	sprintf(port,"%d",m_remotePort);
	osip_uri_set_port(m_pMessage->req_uri,osip_strdup(port));
	char acVia[100] = {0};
	sprintf(acVia,"SIP/2.0/UDP %s:%d;branch=%s;received=%s"
		,m_localIp,m_localPort,m_branch,m_remoteIp);
	osip_message_set_via(m_pMessage,acVia);
	//////////////////////////////////////////////////////////////////////////
	m_pMessage->to->displayname = osip_strdup(m_remoteName);
	m_pMessage->to->url->username = osip_strdup(m_remoteName);
	m_pMessage->to->url->host = osip_strdup(m_remoteIp);
	m_pMessage->to->url->port = osip_strdup(port);
	m_pMessage->to->url->scheme = osip_strdup("sip");
	//////////////////////////////////////////////////////////////////////////
	m_pMessage->from->displayname = osip_strdup(m_name);
	m_pMessage->from->url->username = osip_strdup(m_name);
	m_pMessage->from->url->host = osip_strdup(m_localIp);
	sprintf(port,"%d",m_localPort);
	m_pMessage->from->url->port = osip_strdup(port);
	m_pMessage->from->url->scheme = osip_strdup("sip");
	osip_from_set_tag(m_pMessage->from,osip_strdup(m_tag));
	osip_message_set_call_id(m_pMessage,m_callID);
	osip_message_set_content_type(m_pMessage,"application/text");
	if (m_bodyLen != 0)
	{
		char length[BUFSIZ] = {0};
		sprintf(length,"%d",m_bodyLen);
		osip_message_set_content_length(m_pMessage,length);
		osip_message_set_body(m_pMessage,m_body,m_bodyLen);
	}		
}

/*int CSipMessage::GetReg200Str(char *registStr,unsigned int *len)
{
	MessageInit();
	m_count++;
	char count[10] = {0};
	//////////////////////////////////////////////////////////////////////////
	// MessageInit()
	//////////////////////////////////////////////////////////////////////////	
	m_pMessage->sip_method = strdup("REGISTER");
	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	//	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	sprintf(count,"%d",m_count);
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	osip_cseq_set_method(m_pMessage->cseq,osip_strdup("REGISTER"));
	m_pMessage->req_uri = NULL;
	m_pMessage->sip_method = NULL;
	m_pMessage->sip_version = NULL;
	m_pMessage->status_code = 200;
	osip_message_set_reason_phrase(m_pMessage,strdup("OK"));
	char *str = NULL;
 	unsigned int strlen = 0;
	osip_message_to_str(m_pMessage,&str,&strlen);
	memset(registStr,'\0',*len);
	strncpy(registStr,str,*len);
 	osip_message_free(m_pMessage);
	return strlen;
}*/

int CSipMessage::GetAnwStr(char *registStr,unsigned int *len,SipMode mode)
{
	MessageInit();
	m_count++;
	char count[10] = {0};
	//////////////////////////////////////////////////////////////////////////
	// MessageInit()
	//////////////////////////////////////////////////////////////////////////	
	m_pMessage->sip_method = strdup("REGISTER");
	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	//	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	sprintf(count,"%d",m_count);
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	switch(mode)
	{
	case Invoid200:
	case CMD100:
	case CMD180:
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("INVOID"));
	    break;
	case Regist200:
	case CMD400:
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("REGISTER"));
		break;
	default:
	    break;
	}
	m_pMessage->req_uri = NULL;
	m_pMessage->sip_method = NULL;
	m_pMessage->sip_version = NULL;
	m_pMessage->status_code = 200;
	switch(mode)
	{
	case Invoid200: 
	case Regist200:
		osip_message_set_reason_phrase(m_pMessage,strdup("OK"));
		break;
	case CMD100:
		osip_message_set_reason_phrase(m_pMessage,strdup("Trying"));
	    break;
	case CMD180:
		osip_message_set_reason_phrase(m_pMessage,strdup("Ringing"));
	    break;
	case CMD400:
		osip_message_set_reason_phrase(m_pMessage,strdup("Unauthorized"));
		break;
	default:
	    break;
	}
	char *str = NULL;
 	unsigned int strlen = 0;
	osip_message_to_str(m_pMessage,&str,&strlen);
	memset(registStr,'\0',*len);
	strncpy(registStr,str,*len);
 	osip_message_free(m_pMessage);
	return strlen;
}

/*int CSipMessage::GetInv200Str(char *registStr,unsigned int *len)
{
	MessageInit();
	m_count++;
	char count[10] = {0};
	//////////////////////////////////////////////////////////////////////////
	// MessageInit()
	//////////////////////////////////////////////////////////////////////////	
	m_pMessage->sip_method = strdup("INVITE");
	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	//	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	sprintf(count,"%d",m_count);
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	osip_cseq_set_method(m_pMessage->cseq,osip_strdup("INVITE"));
	m_pMessage->req_uri = NULL;
	m_pMessage->sip_method = NULL;
	m_pMessage->sip_version = NULL;
	m_pMessage->status_code = 200;
	osip_message_set_reason_phrase(m_pMessage,strdup("OK"));
	char *str = NULL;
 	unsigned int strlen = 0;
	osip_message_to_str(m_pMessage,&str,&strlen);
	memset(registStr,'\0',*len);
	strncpy(registStr,str,*len);
 	osip_message_free(m_pMessage);
	return strlen;
}

int CSipMessage::GetCMD100Str(char *registStr,unsigned int *len)
{
	MessageInit();
	m_count++;
	char count[10] = {0};
	//////////////////////////////////////////////////////////////////////////
	// MessageInit()
	//////////////////////////////////////////////////////////////////////////	
	m_pMessage->sip_method = strdup("INVITE");
	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	//	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	sprintf(count,"%d",m_count);
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	osip_cseq_set_method(m_pMessage->cseq,osip_strdup("INVITE"));
	m_pMessage->req_uri = NULL;
	m_pMessage->sip_method = NULL;
	m_pMessage->sip_version = NULL;
	m_pMessage->status_code = 100;
	osip_message_set_reason_phrase(m_pMessage,strdup("Tr"));
	char *str = NULL;
 	unsigned int strlen = 0;
	osip_message_to_str(m_pMessage,&str,&strlen);
	memset(registStr,'\0',*len);
	strncpy(registStr,str,*len);
 	osip_message_free(m_pMessage);
	return strlen;
}

int CSipMessage::GetCMD180Str(char *registStr,unsigned int *len)
{
	MessageInit();
	m_count++;
	char count[10] = {0};
	//////////////////////////////////////////////////////////////////////////
	// MessageInit()
	//////////////////////////////////////////////////////////////////////////	
	m_pMessage->sip_method = strdup("INVITE");
	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	//	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	sprintf(count,"%d",m_count);
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	osip_cseq_set_method(m_pMessage->cseq,osip_strdup("INVITE"));
	m_pMessage->req_uri = NULL;
	m_pMessage->sip_method = NULL;
	m_pMessage->sip_version = NULL;
	m_pMessage->status_code = 200;
	osip_message_set_reason_phrase(m_pMessage,strdup("Ringing"));
	char *str = NULL;
 	unsigned int strlen = 0;
	osip_message_to_str(m_pMessage,&str,&strlen);
	memset(registStr,'\0',*len);
	strncpy(registStr,str,*len);
 	osip_message_free(m_pMessage);
	return strlen;
}

int CSipMessage::GetCMD400Str(char *registStr,unsigned int *len)
{
	MessageInit();
	m_count++;
	char count[10] = {0};
	//////////////////////////////////////////////////////////////////////////
	// MessageInit()
	//////////////////////////////////////////////////////////////////////////	
	m_pMessage->sip_method = strdup("INVITE");
	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	//	InitNormalInfo();
	//////////////////////////////////////////////////////////////////////////
	sprintf(count,"%d",m_count);
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	osip_cseq_set_method(m_pMessage->cseq,osip_strdup("INVITE"));
	m_pMessage->req_uri = NULL;
	m_pMessage->sip_method = NULL;
	m_pMessage->sip_version = NULL;
	m_pMessage->status_code = 200;
	osip_message_set_reason_phrase(m_pMessage,strdup("OK"));
	char *str = NULL;
 	unsigned int strlen = 0;
	osip_message_to_str(m_pMessage,&str,&strlen);
	memset(registStr,'\0',*len);
	strncpy(registStr,str,*len);
 	osip_message_free(m_pMessage);
	return strlen;
}
*/

void CSipMessage::SetMsgBody(char *buf,unsigned int len)
{
	m_bodyLen = 0;
	if (m_body != NULL)
	{
		delete [] m_body;
	}
	m_body = new char[len];
	strncpy(m_body,buf,len);
	m_bodyLen = len;
}

void CSipMessage::GetSipMessage(char *msgStr,unsigned int *len,SipMode mode)
{
	m_sipMode = mode;
	switch(mode)
	{
	case Regist:
	case Invoid:
	case Bye:
	case Ack:
	case Unregist:
	    GetReqStr(msgStr,len,mode);
		break;
	case Regist200:
	case Invoid200:
	case CMD100:
	case CMD180:
	case CMD400:
		GetAnwStr(msgStr,len,mode);
		break;
	default:
	    break;
	}
}