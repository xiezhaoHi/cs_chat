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
	m_remoteName = NULL;
	m_audioFlag = false;
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
		delete[] m_name;
	}	
	if (m_password != NULL)
	{
		delete[] m_password;
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
	char *strtemp = NULL;
	unsigned int bodylen = 0;
	char audio_ip[20] = {0};
	char port[10] = {0};
	osip_cseq_set_number(m_pMessage->cseq,osip_strdup(count));
	switch(mode)
	{
	case Regist:
		m_pMessage->sip_method = strdup("REGISTER");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("REGISTER"));
		osip_message_set_expires(m_pMessage,osip_strdup("1"));
		break;
	case Invoid:
		m_pMessage->sip_method = strdup("INVITE");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("INVITE"));
		
		if (m_audioFlag == false)
		{
			break;
		}
		//设置包体

		g_audioCtrl->m_sockStream->GetLocalIp(audio_ip,18);
		sprintf(port,"%d",g_audioCtrl->m_sockStream->GetSockPort());

		sdp_message_t *pSdpMsg;
		sdp_message_init(&pSdpMsg);
		//设置V
		sdp_message_v_version_set(pSdpMsg, osip_strdup("0"));
		
		//设置O
		sdp_message_o_origin_set(
			pSdpMsg,
			osip_strdup("Linchen"),
			osip_strdup("2890844526"),
			osip_strdup("2890844526"),
			osip_strdup("IN"),
			osip_strdup("IP4"),
			osip_strdup(audio_ip)
			);
		//设置S
		sdp_message_s_name_set(pSdpMsg, osip_strdup("-"));
		//设置C
		sdp_message_c_connection_add(
			pSdpMsg,
			0,
			osip_strdup("IN"),
			osip_strdup("IP4"),
			osip_strdup(audio_ip),
			NULL,
			NULL
			);
		//设置T
		sdp_message_t_time_descr_add(
			pSdpMsg,
			osip_strdup("0"),
			osip_strdup("0")
			);
		//设置M
		sdp_message_m_media_add(
			pSdpMsg,
			osip_strdup("audio"),
			osip_strdup(port),
			NULL,
			osip_strdup("RTP/AVP 4")
			);
		//设置A
		sdp_message_a_attribute_add(
			pSdpMsg,
			0,
			osip_strdup("rtpmap"),
			osip_strdup("4 PCMU/8000")
			);
		

		bodylen = sdp_message_to_str(pSdpMsg, &strtemp);
		
		osip_message_set_body(m_pMessage, strtemp, strlen(strtemp));
		osip_free(strtemp);
		strtemp = NULL;


		break;
	case ByeSip:
		m_pMessage->sip_method = strdup("BYE");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("BYE"));
		break;
	case AckSip:
		m_pMessage->sip_method = strdup("ACK");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("ACK"));
		break;
	case Unregist:
		m_pMessage->sip_method = strdup("REGISTER");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("REGISTER"));
		osip_message_set_expires(m_pMessage,osip_strdup("0"));
//////////////////////////////////////////////////////////////////////////
//补充UNregisted
//////////////////////////////////////////////////////////////////////////
		break;
	case CancelSip:
		m_pMessage->sip_method = strdup("CANCEL");
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("CANCEL"));
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
	const int SIZE_CHAR = strLen;  //生成SIZE_CHAR位C Style字符串
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
	m_callID[CALLID_LEN]='\0';
	GetRandomString(m_tag,TAG_LEN);
	m_tag[TAG_LEN]='\0';
	GetRandomString(m_branch,BRANCH_LEN);
	m_branch[BRANCH_LEN]='\0';
}

void CSipMessage::MessageInit()
{
	osip_message_init(&m_pMessage);
	if(NULL == m_pMessage)
	{
		ASSERT(0);
	}
	if(osip_uri_init(&m_pMessage->req_uri) != 0)
	{
		ASSERT(0);
	}
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
	if (m_remoteName != NULL)
	{
		m_pMessage->to->displayname = osip_strdup(m_remoteName);
		m_pMessage->to->url->username = osip_strdup(m_remoteName);
	}
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

int CSipMessage::GetAnwStr(char *registStr,unsigned int *len,SipMode mode)
{
	MessageInit();
	m_count++;
	char count[10] = {0};
	char audio_ip[20] = {0};
	char port[10] = {0};
	char *strtemp = NULL;
	unsigned int bodylen = 0;
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
	case CMD487:
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("INVITE"));
	    if (m_audioFlag == false)
		{
			break;
		}
		//设置包体
//		CSocketStream 
 		g_audioCtrl->m_sockStream->GetLocalIp(audio_ip,18);
//		CSocketStream::GetLocalIp(audio_ip,18);
		sprintf(port,"%d",g_audioCtrl->m_sockStream->GetSockPort());

		sdp_message_t *pSdpMsg;
		sdp_message_init(&pSdpMsg);
		//设置V
		sdp_message_v_version_set(pSdpMsg, osip_strdup("0"));
		
		//设置O
		sdp_message_o_origin_set(
			pSdpMsg,
			osip_strdup("Linchen"),
			osip_strdup("2890844526"),
			osip_strdup("2890844526"),
			osip_strdup("IN"),
			osip_strdup("IP4"),
			osip_strdup(audio_ip)
			);
		//设置S
		sdp_message_s_name_set(pSdpMsg, osip_strdup("-"));
		//设置C
		sdp_message_c_connection_add(
			pSdpMsg,
			0,
			osip_strdup("IN"),
			osip_strdup("IP4"),
			osip_strdup(audio_ip),
			NULL,
			NULL
			);
		//设置T
		sdp_message_t_time_descr_add(
			pSdpMsg,
			osip_strdup("0"),
			osip_strdup("0")
			);
		//设置M
		sdp_message_m_media_add(
			pSdpMsg,
			osip_strdup("audio"),
			osip_strdup(port),
			"8",
			osip_strdup("RTP/AVP 4")
			);
		//设置A
		sdp_message_a_attribute_add(
			pSdpMsg,
			0,
			osip_strdup("rtpmap"),
			osip_strdup("4 PCMU/8000")
			);
		bodylen = sdp_message_to_str(pSdpMsg, &strtemp);	
		osip_message_set_body(m_pMessage, strtemp, strlen(strtemp));
		osip_free(strtemp);
		strtemp = NULL;


		break;
	case Regist200:
	case CMD400:
	
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("REGISTER"));
		break;
	case CancelSip:
		osip_cseq_set_method(m_pMessage->cseq,osip_strdup("CANCEL"));
		break;
	case Unregist:
		osip_message_set_expires(m_pMessage,"0");
	default:
	    break;
	}
	m_pMessage->req_uri = NULL;
	m_pMessage->sip_method = NULL;
	m_pMessage->sip_version = NULL;
	
	switch(mode)
	{
	case Invoid200: 
	case Regist200:
		m_pMessage->status_code = 200;
		osip_message_set_reason_phrase(m_pMessage,strdup("OK"));
		break;
	case CMD100:
		m_pMessage->status_code = 100;
		osip_message_set_reason_phrase(m_pMessage,strdup("Trying"));
	    break;
	case CMD180:
		m_pMessage->status_code = 180;
		osip_message_set_reason_phrase(m_pMessage,strdup("Ringing"));
	    break;
	case CMD400:
		m_pMessage->status_code = 400;
		osip_message_set_reason_phrase(m_pMessage,strdup("Unauthorized"));
		break;
	case CMD487:
		m_pMessage->status_code = 487;
		osip_message_set_reason_phrase(m_pMessage,strdup("Unauthorized"));
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
	case ByeSip:
	case AckSip:
	case Unregist:
	case CancelSip:
	    GetReqStr(msgStr,len,mode);
		break;
	case Regist200:
	case Invoid200:
	case CMD100:
	case CMD180:
	case CMD400:
	case CMD487:
		GetAnwStr(msgStr,len,mode);
		break;
	default:
	    break;
	}
}

void CSipMessage::UnZipString(char *pMsg)
{
	string tMsg = "";
	string temp = "";
	tMsg += pMsg;
	unsigned int bPos = tMsg.find_first_of("<") - 1;
	temp = &tMsg[bPos];
	bPos = temp.find_first_of("sip:",bPos) + strlen("sip:") + 1;
	temp = &tMsg[bPos];
	unsigned int ePos = temp.find_first_of("@");
	//////////////////////////////////////////////////////////////////////////
	// 获得远程用户名称
	Strdup(m_remoteName,ePos+1);
	strncpy(m_remoteName,temp.c_str(),ePos);
	m_remoteName[ePos]='\0';
	tMsg = temp;
	temp = &tMsg[ePos+1];
	/////// ///////////////////////////////////////////////////////////////////
	// 获得远程IP地址
	ePos = temp.find_first_of(":");	
	Strdup(m_remoteIp,ePos);
	strncpy(m_remoteIp,temp.c_str(),ePos);
	m_remoteIp[ePos]='\0';

	tMsg = temp;
	temp = &tMsg[ePos+1];
	//////////////////////////////////////////////////////////////////////////
	// 获得远程端口
	ePos = temp.find_first_of(">");
	char *tRemotePort = new char[ePos];
	Strdup(tRemotePort,ePos);
	strncpy(tRemotePort,temp.c_str(),ePos);
	tRemotePort[ePos]='\0';
	m_remotePort = atoi(tRemotePort);
	tMsg = temp;
	temp = &tMsg[ePos+1];

	//////////////////////////////////////////////////////////////////////////
	//
	ePos = temp.find_first_of("<sip:");
	tMsg = temp;
	temp = &tMsg[ePos+strlen("<sip:")];
	ePos = temp.find_first_of("@");
	if (m_toName == NULL)
	{
		m_toName = new char[ePos];
	}
	Strdup(m_toName,ePos);
	strncpy(m_toName,temp.c_str(),ePos);
	m_toName[ePos]='\0';
	tMsg = temp;
	temp = &tMsg[ePos+1];

	//////////////////////////////////////////////////////////////////////////
	//
}

bool CSipMessage::Strdup(char *str,int len)
{
	if (str != NULL)
	{
		delete[] str;
	}
	str = new char[len];
	memset(str,'\0',len);
	if (str == NULL)
	{
		return false;
	}
	return true;
}

void CSipMessage::SetCallID(char *callID)
{
	char *str = new char[CALLID_LEN];
	memset(str,'\0',CALLID_LEN);
	memcpy(str,callID,CALLID_LEN);
	strncpy(m_tag,str,TAG_LEN);
	strncpy(m_branch,str,BRANCH_LEN);	
	strncpy(m_callID,str,CALLID_LEN);
	m_callID[CALLID_LEN]='\0';
	m_branch[BRANCH_LEN]='\0';
	m_tag[TAG_LEN]='\0';
}

osip_message_t* CSipMessage::GetSipMessage()
{
	return m_pMessage;
}

char* CSipMessage::GetCallId()
{
	return m_callID;
}

void CSipMessage::SetAudioBody(bool flag)
{
	m_audioFlag = flag;
}
