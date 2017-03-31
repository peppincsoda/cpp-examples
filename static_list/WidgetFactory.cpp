#include "WidgetFactory.h"

std::unique_ptr<Widget> CreateWidget(const std::string& class_name)
{
    for (StaticList<WidgetFactoryNode>* node = StaticList<WidgetFactoryNode>::first();
        node != nullptr;
        node = node->next())
    {
        WidgetFactoryNode* factory_node = static_cast<WidgetFactoryNode*>(node);
        if (factory_node->class_name() == class_name)
        {
            return factory_node->CreateWidget();
        }
    }

    return nullptr;
}
