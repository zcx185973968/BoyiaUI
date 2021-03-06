#ifndef JSNetwork_h
#define JSNetwork_h

#include "NetworkBase.h"
#include "BoyiaCore.h"

namespace boyia
{
// JSNetwork会根据回调的情况，自动释放自己
class JSNetwork : public yanbo::NetworkClient
{
public:
	JSNetwork(BoyiaValue* callback, BoyiaValue* obj);
	virtual ~JSNetwork();

public:
	void load(const String& url);

	virtual void onDataReceived(const String& data);
	virtual void onStatusCode(LInt statusCode);
	virtual void onFileLen(LInt len);
	virtual void onRedirectUrl(const String& redirectUrl);
	virtual void onLoadError(LInt error);
	virtual void onLoadFinished(const String& data);

private:
	BoyiaValue m_callback;
	BoyiaValue m_obj;
};
}
#endif
