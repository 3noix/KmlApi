#include "KmlDocument.h"
#include <fstream>


namespace Kml
{
Document::Document(const std::string &name, const std::string &description)
{
	m_name = name;
	m_description = description;

	// default styles
	Style paddleGreenDot, paddleRedDot, blueLine5;
	paddleGreenDot.rawStyle().setContent("<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/green-dot.png</href></Icon></IconStyle>");
	paddleRedDot.rawStyle().setContent("<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/red-dot.png</href></Icon></IconStyle>");
	blueLine5.rawStyle().setContent("<LineStyle><color>73FF0000</color><width>5</width></LineStyle><PolyStyle><fill>1</fill><outline>1</outline></PolyStyle>");
	this->addStyle("paddleGreenDot", paddleGreenDot);
	this->addStyle("paddleRedDot", paddleRedDot);
	this->addStyle("blueLine5", blueLine5);
}

Document& Document::setName(const std::string &name)
{
	m_name = name;
	return *this;
}

std::string Document::name() const
{
	return m_name;
}

Document& Document::setDescription(const std::string &description)
{
	m_description = description;
	return *this;
}

std::string Document::description() const
{
	return m_description;
}

Document& Document::setExpanded(bool expanded)
{
	m_expanded = expanded;
	return *this;
}

bool Document::isExpanded() const
{
	return m_expanded;
}

Document& Document::setVisible(bool bVisible)
{
	m_isVisible = bVisible;
	return *this;
}

bool Document::isVisible() const
{
	return m_isVisible;
}

Document& Document::addStyle(const std::string &styleUrl, const Style &style)
{
	m_styles.insert({styleUrl,style});
	return *this;
}

Document& Document::addItem(std::unique_ptr<AbstractItem>&& item)
{
	m_kmlItems.push_back(std::move(item));
	return *this;
}


std::string Document::headerToString() const
{
	std::string str = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	str += "<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\">\n";
	str += "\t<Document>\n";
	str += "\t\t<name>" + m_name + "</name>\n";
	str += "\t\t<description>" + m_description + "</description>\n";
	str += "\t\t<open>" + std::string{m_expanded ? "1" : "0"} + "</open>\n";
	str += "\t\t<visible>" + std::string{m_isVisible ? "1" : "0"} + "</visible>\n";

	for (const auto& [id, style] : m_styles) {str += style.toString(2,id);}
	return str;
}

std::string Document::bodyToString() const
{
	std::string str;
	for (const std::unique_ptr<AbstractItem> &item : m_kmlItems) {str += item->toString(2);}
	return str;
}

std::string Document::footerToString() const
{
	return std::string{"\t</Document>\n</kml>\n"};
}

std::string Document::toString() const
{
	return headerToString() + bodyToString() + footerToString();
}

bool Document::write(const std::string &filePath)
{
	std::ofstream file{filePath};
	if (file.fail()) {return false;}
	file << this->toString();
	file.close();
	return true;
}
}

