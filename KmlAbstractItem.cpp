#include "KmlAbstractItem.h"


namespace Kml
{
AbstractItem::AbstractItem(const std::string &name)
{
	m_name = name;
}

AbstractItem& AbstractItem::setName(const std::string &name)
{
	m_name = name;
	return *this;
}

std::string AbstractItem::name() const
{
	return m_name;
}

AbstractItem& AbstractItem::setDescription(const std::string &description)
{
	m_description = description;
	return *this;
}

std::string AbstractItem::description() const
{
	return m_description;
}

AbstractItem& AbstractItem::setStyleUrl(const std::string &styleUrl)
{
	m_styleUrl = styleUrl;
	return *this;
}

std::string AbstractItem::styleUrl() const
{
	return m_styleUrl;
}

AbstractItem& AbstractItem::setVisible(bool bVisible)
{
	m_isVisible = bVisible;
	return *this;
}

bool AbstractItem::isVisible() const
{
	return m_isVisible;
}
}

