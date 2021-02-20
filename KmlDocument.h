#ifndef KML_DOCUMENT
#define KML_DOCUMENT


#include <map>
#include <vector>
#include <string>
#include <memory>
#include "KmlAbstractItem.h"
#include "KmlStyle.h"


namespace Kml
{
class Document
{
	public:
		Document(const std::string &name, const std::string &description = "<![CDATA[]]>");
		Document(const Document &other) = delete;
		Document(Document &&other) = delete;
		Document& operator=(const Document &other) = delete;
		Document& operator=(Document &&other) = delete;
		~Document() = default;


		Document& setName(const std::string &name);
		std::string name() const;

		Document& setDescription(const std::string &description);
		std::string description() const;

		Document& setExpanded(bool expanded);
		bool isExpanded() const;

		Document& setVisible(bool bVisible);
		bool isVisible() const;

		Document& addStyle(const std::string &styleUrl, const Style &style);
		Document& addItem(std::unique_ptr<AbstractItem>&& item);

		std::string headerToString() const;
		std::string bodyToString() const;
		std::string footerToString() const;
		std::string toString() const;

		bool write(const std::string &filePath);


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

