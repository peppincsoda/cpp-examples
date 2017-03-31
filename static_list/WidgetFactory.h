#ifndef _WIDGET_FACTORY_H_
#define _WIDGET_FACTORY_H_

#include <string>
#include <memory>

#include "StaticList.h"

class Widget
{
public:
    virtual ~Widget() {}
};

class WidgetFactoryNode : public StaticList<WidgetFactoryNode>
{
public:
    WidgetFactoryNode(const std::string& class_name, std::unique_ptr<Widget> (*create_fn)())
        : class_name_(class_name)
        , create_fn_(create_fn)
    {
    }

    const std::string& class_name() const { return class_name_; }
    std::unique_ptr<Widget> CreateWidget() const { return (*create_fn_)(); }

private:
    std::string class_name_;
    std::unique_ptr<Widget> (*create_fn_)();
};

// Factory function traversing all the registered nodes.

std::unique_ptr<Widget> CreateWidget(const std::string& class_name);

#endif // _WIDGET_FACTORY_H_
