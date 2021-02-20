#include "KmlStyle.h"


namespace Kml
{
std::string Style::toString(std::size_t tabs, const std::string &id) const
{
	std::string prefix(tabs,'\t');
	std::string str;
	str += prefix + "<Style id=\"" + id + "\">\n";

	if (m_rawStyle)
	{
		str += prefix + "\t" + m_rawStyle->content() + "\n";
	}
	else
	{
		if (m_iconStyle)    {str += m_iconStyle->toString(tabs+1);}
		if (m_labelStyle)   {str += m_labelStyle->toString(tabs+1);}
		if (m_lineStyle)    {str += m_lineStyle->toString(tabs+1);}
		if (m_polyStyle)    {str += m_polyStyle->toString(tabs+1);}
		if (m_balloonStyle) {str += m_balloonStyle->toString(tabs+1);}
	}

	str += prefix + "</Style>\n";
	return str;
}

RawStyle& Style::rawStyle()
{
	if (!m_rawStyle) {m_rawStyle.emplace(*this);}
	return m_rawStyle.value();
}

IconStyle& Style::iconStyle()
{
	if (!m_iconStyle) {m_iconStyle.emplace(*this);}
	return m_iconStyle.value();
}

LabelStyle& Style::labelStyle()
{
	if (!m_labelStyle) {m_labelStyle.emplace(*this);}
	return m_labelStyle.value();
}

LineStyle& Style::lineStyle()
{
	if (!m_lineStyle) {m_lineStyle.emplace(*this);}
	return m_lineStyle.value();
}

PolyStyle& Style::polyStyle()
{
	if (!m_polyStyle) {m_polyStyle.emplace(*this);}
	return m_polyStyle.value();
}

BalloonStyle& Style::balloonStyle()
{
	if (!m_balloonStyle) {m_balloonStyle.emplace(*this);}
	return m_balloonStyle.value();
}
}

