#include "JSNetwork.h"
#include "UIView.h"
#include "BoyiaLib.h"

namespace boyia
{
JSNetwork::JSNetwork(BoyiaValue* callback, BoyiaValue* obj)
{
	ValueCopy(&m_callback, callback);
	ValueCopy(&m_obj, obj);
}

JSNetwork::~JSNetwork()
{
}

void JSNetwork::load(const String& url)
{
	yanbo::UIView::getInstance()->network()->loadUrl(url, this, false);
}

void JSNetwork::onDataReceived(const String& data)
{
}

void JSNetwork::onStatusCode(LInt statusCode)
{
}

void JSNetwork::onFileLen(LInt len)
{
}

void JSNetwork::onRedirectUrl(const String& redirectUrl)
{
}

void JSNetwork::onLoadError(LInt error)
{
    delete this;
}

void JSNetwork::onLoadFinished(const String& data)
{
	KFORMATLOG("JSNetwork::onLoadFinished %d", 1);
	BoyiaValue value;
	value.mValueType = BY_STRING;
	value.mValue.mStrVal.mPtr = (LInt8*)data.GetBuffer();
	value.mValue.mStrVal.mLen = data.GetLength();
	KFORMATLOG("JSNetwork::onLoadFinished, data=%s", (const char*)data.GetBuffer());
	SaveLocalSize();
	LocalPush(&m_callback);
	LocalPush(&value);
	BoyiaValue* obj = m_obj.mValue.mObj.mPtr == 0 ? NULL : &m_obj;
	NativeCall(obj);
	delete this;
}

}
