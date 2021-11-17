#include "KmlFolder.h"


namespace Kml
{
Folder::Folder(const std::string &name) : AbstractItem{name}
{
}

Folder& Folder::setExpanded(bool expanded)
{
	m_expanded = expanded;
	return *this;
}

bool Folder::isExpanded() const
{
	return m_expanded;
}

Folder& Folder::addItem(std::unique_ptr<AbstractItem>&& item)
{
	m_childItems.push_back(std::move(item));
	return *this;
}

std::string Folder::toString(std::size_t tabs) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<Folder>\n";
	str += prefix + "\t<name>" + this->name() + "</name>\n";
	str += prefix + "\t<description>" + this->description() + "</description>\n";
	str += prefix + "\t<styleUrl>" + this->styleUrl() + "</styleUrl>\n";
	str += prefix + "\t<visible>" + (this->isVisible() ? "1" : "0") + "</visible>\n";
	str += prefix + "\t<open>" + (m_expanded ? "1" : "0") + "</open>\n";
	for (const std::unique_ptr<AbstractItem> &item : m_childItems) {str += item->toString(tabs+1);}
	str += prefix + "</Folder>\n";
	return str;
}
}

