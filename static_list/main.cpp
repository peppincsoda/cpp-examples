#include "WidgetFactory.h"

int main()
{
    std::unique_ptr<Widget> widget = CreateWidget("Button");

    return 0;
}
