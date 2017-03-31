#include "WidgetFactory.h"

class Button : public Widget
{
    //  ...
};

namespace
{
    static std::unique_ptr<Widget> CreateButton()
    {
        return std::make_unique<Button>();
    }

    static WidgetFactoryNode node("Button", CreateButton);
}
