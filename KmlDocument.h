#ifndef KML_DOCUMENT
#define KML_DOCUMENT


#include <map>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include "KmlAbstractItem.h"
#include "KmlStyle.h"

namespace Kml
{
class Document
{
	public:
		Document(const std::string &name, const std::string &description = "<![CDATA[]]>")
		{
			m_name = name;
			m_description = description;

			// default styles
			Style paddleGreenDot, paddleRedDot, blueLine5;
			paddleGreenDot.rawContent = "<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/green-dot.png</href></Icon></IconStyle>";
			paddleRedDot.rawContent   = "<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/red-dot.png</href></Icon></IconStyle>";
			blueLine5.rawContent      = "<LineStyle><color>73FF0000</color><width>5</width></LineStyle><PolyStyle><fill>1</fill><outline>1</outline></PolyStyle>";
			m_styles.insert({"paddleGreenDot", paddleGreenDot});
			m_styles.insert({"paddleRedDot", paddleRedDot});
			m_styles.insert({"blueLine5", blueLine5});
		};

		Document(const Document &other) = delete;
		Document(Document &&other) = delete;
		Document& operator=(const Document &other) = delete;
		Document& operator=(Document &&other) = delete;
		~Document() = default;


		void setName(const std::string &name) {m_name = name;};
		std::string name() const {return m_name;};

		void setDescription(const std::string &description) {m_description = description;};
		std::string description() const {return m_description;};

		void setExpanded(bool expanded) {m_expanded = expanded;};
		bool isExpanded() const {return m_expanded;};

		void setVisible(bool bVisible) {m_isVisible = bVisible;};
		bool isVisible() const {return m_isVisible;};

		void addStyle(const std::string &styleUrl, const Style &style) {m_styles.insert({styleUrl,style});};
		void addItem(std::unique_ptr<AbstractItem>&& item) {m_kmlItems.push_back(std::move(item));};


		std::string toString() const
		{
			std::string str = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str += "<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\">\n";
			str += "\t<Document>\n";
			str += "\t\t<name>" + m_name + "</name>\n";
			str += "\t\t<description>" + m_description + "</description>\n";
			str += "\t\t<open>" + std::string{m_expanded ? "1" : "0"} + "</open>\n";
			str += "\t\t<visible>" + std::string{m_isVisible ? "1" : "0"} + "</visible>\n";

			for (const auto& [id, style] : m_styles) {str += style.toString(2,id);}
			for (const std::unique_ptr<AbstractItem> &item : m_kmlItems) {str += item->toString(2);}

			str += "\t</Document>\n";
			str += "</kml>\n";
			return str;
		};

		bool write(const std::string &filePath)
		{
			std::ofstream file{filePath};
			if (file.fail()) {return false;}
			file << this->toString();
			file.close();
			return true;
		};
		
		
	private:
		std::string m_name;
		std::string m_description;
		bool m_expanded = false;
		bool m_isVisible = true;
		std::map<std::string,Style> m_styles; // the key is the id (or url), the value is the xml content
		std::vector<std::unique_ptr<AbstractItem>> m_kmlItems;
};
}


#endif

