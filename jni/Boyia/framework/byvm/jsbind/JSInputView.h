#ifndef JSInputView_h
#define JSInputView_h

#include "JSView.h"

namespace boyia {
class JSInputView : public JSView {
public:
	JSInputView(yanbo::HtmlView* item);

	void setText(const String& text);
};
}
#endif
