/*
 * ResourceLoader.cpp
 *
 *  Created on: 2011-7-15
 *      Author: yanbo
 */
#include "ResourceLoader.h"
#include "UIView.h"
#include "SalLog.h"
#include "StringUtils.h"
#include <android/log.h>

extern LVoid compileJs(char* code);
namespace yanbo
{
class ResourceHandle : public NetworkClient
{
public:
	ResourceHandle(ResourceLoader* loader, const String& url, LInt type)
	    : m_loader(loader)
	    , m_resType(type)
	    , m_url(url)
	{
	}

	virtual void onDataReceived(const String& data)
	{
		m_loader->onDataReceived(data);
	}

	virtual void onStatusCode(LInt statusCode)
	{
		m_loader->onStatusCode(statusCode);
	}

	virtual void onRedirectUrl(const String& redirectUrl)
	{
		m_loader->onRedirectUrl(redirectUrl);
	}

	virtual void onLoadError(LInt error)
	{
		m_loader->onLoadError(error);
		delete this;
	}

	virtual void onLoadFinished(const String& data)
	{
		__android_log_print(ANDROID_LOG_INFO, "MiniJS", "Parse url=%s", (const char*)m_url.GetBuffer());
		m_loader->onLoadFinished(data, m_resType);
		delete this;
	}

	virtual void onFileLen(LInt len)
	{
		m_loader->onFileLen(len);
	}

private:
	ResourceLoader* m_loader;
	LInt            m_resType;
	String          m_url;
};

ResourceLoader::ResourceLoader(ResourceLoaderClient* client)
    : m_render(NULL)
    , m_client(client)
    , m_cssSize(0)
{	
}

ResourceLoader::~ResourceLoader()
{
	if (NULL != m_render)
	{
	    delete m_render;
	    m_render = NULL;
	}
}

void ResourceLoader::onFileLen(LInt len)
{
    KLOG("ResourceLoader::onFileLen");	
    KDESLOG(len);
    YanLog("dataLen=%d", len);
}


void ResourceLoader::onDataReceived(const String& data)
{
	KLOG("ResourceLoader::onDataReceived");
	//m_data += data;
	KSTRLOG8(data);
	KLOG("onDataReceived end");
}

void ResourceLoader::onStatusCode(LInt statusCode)
{
	
}

void ResourceLoader::onRedirectUrl(const String& redirectUrl)
{
}

void ResourceLoader::onLoadError(LInt error)
{
	
}

void ResourceLoader::onLoadFinished(const String& data, LInt resType)
{
	KLOG("ResourceLoader::onLoadFinished()");
	switch (resType)
	{
	case HTMLDOC:
		{
		    executeDocument(data);
		}
		break;
	case CACHEJS:
		{
			executeJavaScript(data);
		}
		break;
	case CACHECSS:
		{
			executeCss(data);
		}
	    break;
	default:
		break;
	}
}

void ResourceLoader::load(const String& url, LoadType type)
{
	if (type == CACHECSS)
	{
		++m_cssSize;
	}
	ResourceHandle* handle = new ResourceHandle(this, url, type);
	m_view->network()->loadUrl(url, handle);
}

void ResourceLoader::setView(UIView* view)
{
	m_view = view;
}

UIView* ResourceLoader::view() const
{
	return m_view;
}

void ResourceLoader::executeDocument(const String& data)
{
	KLOG("ResourceLoader::executeDocument()");
	KLOG((const char*)data.GetBuffer());
	//KSTRLOG8(m_data);
	if (!m_render)
	{
		m_render = new HtmlRenderer();
	}

	m_render->renderHTML(m_view->getDocument(),
			data,
			m_view->getClientRange(),
			this);
	
	if (m_cssSize)
	{
		return;
	}

	m_render->layout();
	KLOG("m_render->layout()");

	if (m_client)
	{
		m_client->onHtmlRenderFinished();
	}

	LGraphicsContext* gc = m_view->getGraphicsContext();
	if (!gc)
	{
		return;
	}
	gc->reset();

	KLOG("paint");
	m_render->paint(NULL);

	if (m_client)
	{
	    KLOG("NULL != m_client");
	    m_client->onViewNeedToDraw();
	}
	
}

HtmlRenderer* ResourceLoader::render() const
{
	return m_render;
}

// Execute external css
void ResourceLoader::executeCss(const String& data)
{
	--m_cssSize;

	util::InputStream is(data);
	m_render->getCssParser()->parseCss(is);

	if (!m_cssSize)
	{
		m_render->layout();
		m_render->paint(NULL);
	}
}

// Execute external JS
void ResourceLoader::executeJavaScript(const String& data)
{
	compileJs((char*)data.GetBuffer());
}

void ResourceLoader::repaint(HtmlView* item)
{
	KLOG("ResourceLoader::repaint()");
	LGraphicsContext* gc = m_view->getGraphicsContext();
	if (!gc)
	{
		return;
	}

	if (NULL != item)
	{
		m_render->paint(item);
        return;
	}

	gc->reset();
	m_render->paint(NULL);

	if (NULL != m_client)
	{
	    m_client->onViewNeedToDraw();
	}
}

void ResourceLoader::loadString(const String& src)
{
    onLoadFinished(src, HTMLDOC);
}

}
