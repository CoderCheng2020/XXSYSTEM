/* soapcalcProxy.cpp
   Generated by gSOAP 2.8.22 from XX_System_Transportation.h

Copyright(C) 2000-2015, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/
#include "stdafx.h"
#include "soapcalcProxy.h"

calcProxy::calcProxy()
{	calcProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

calcProxy::calcProxy(const struct soap &_soap) : soap(_soap)
{ }

calcProxy::calcProxy(const char *url)
{	calcProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = url;
}

calcProxy::calcProxy(soap_mode iomode)
{	calcProxy_init(iomode, iomode);
}

calcProxy::calcProxy(const char *url, soap_mode iomode)
{	calcProxy_init(iomode, iomode);
	soap_endpoint = url;
}

calcProxy::calcProxy(soap_mode imode, soap_mode omode)
{	calcProxy_init(imode, omode);
}

calcProxy::~calcProxy()
{ }

void calcProxy::calcProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:XXSystem", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
}

void calcProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void calcProxy::reset()
{	destroy();
	soap_done(this);
	soap_initialize(this);
	calcProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void calcProxy::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *calcProxy::soap_header()
{	return this->header;
}

const SOAP_ENV__Fault *calcProxy::soap_fault()
{	return this->fault;
}

const char *calcProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *calcProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int calcProxy::soap_close_socket()
{	return soap_closesock(this);
}

int calcProxy::soap_force_close_socket()
{	return soap_force_closesock(this);
}

void calcProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void calcProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *calcProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int calcProxy::SendAndReceiveMessage(const char *endpoint, const char *soap_action, char *sendMesssage, char **recevieMessage)
{	struct soap *soap = this;
	struct ns__SendAndReceiveMessage soap_tmp_ns__SendAndReceiveMessage;
	struct ns__SendAndReceiveMessageResponse *soap_tmp_ns__SendAndReceiveMessageResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__SendAndReceiveMessage.sendMesssage = sendMesssage;
	soap_serializeheader(soap);
	soap_serialize_ns__SendAndReceiveMessage(soap, &soap_tmp_ns__SendAndReceiveMessage);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__SendAndReceiveMessage(soap, &soap_tmp_ns__SendAndReceiveMessage, "ns:SendAndReceiveMessage", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__SendAndReceiveMessage(soap, &soap_tmp_ns__SendAndReceiveMessage, "ns:SendAndReceiveMessage", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!recevieMessage)
		return soap_closesock(soap);
	*recevieMessage = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__SendAndReceiveMessageResponse = soap_get_ns__SendAndReceiveMessageResponse(soap, NULL, "", NULL);
	if (!soap_tmp_ns__SendAndReceiveMessageResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (recevieMessage && soap_tmp_ns__SendAndReceiveMessageResponse->recevieMessage)
		*recevieMessage = *soap_tmp_ns__SendAndReceiveMessageResponse->recevieMessage;
	return soap_closesock(soap);
}
/* End of client proxy code */
