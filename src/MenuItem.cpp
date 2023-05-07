#include "MenuItem.h"

int MenuItem::index()
{
    return m_index;
}
bool MenuItem::highlighted()
{
    return m_highlighted;
}
void MenuItem::setHighlight(const bool &h)
{
    if (m_highlighted != h)
	m_highlighted = h;
}
std::string MenuItem::label()
{
    return m_label;
}
void MenuItem::setLabel(const std::string l)
{
    m_label = l;
}
