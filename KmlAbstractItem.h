#ifndef KML_ABSTRACT_ITEM
#define KML_ABSTRACT_ITEM


#include <string>


namespace Kml
{
class AbstractItem
{
	public:
		AbstractItem(const std::string &name) {m_name = name;};
		AbstractItem(const AbstractItem &other) = default;
		AbstractItem(AbstractItem &&other) = default;
		AbstractItem& operator=(const AbstractItem &other) = default;
		AbstractItem& operator=(AbstractItem &&other) = default;
		virtual ~AbstractItem() = default;


		virtual std::string toString(std::size_t tabs = 0) const = 0;

		void setName(const std::string &name) {m_name = name;};
		std::string name() const {return m_name;};

		void setDescription(const std::string &description) {m_description = description;};
		std::string description() const {return m_description;};

		void setStyleUrl(const std::string &styleUrl) {m_styleUrl = styleUrl;};
		std::string styleUrl() const {return m_styleUrl;};

		void setVisible(bool bVisible) {m_isVisible = bVisible;};
		bool isVisible() const {return m_isVisible;};
		
		
	private:
		std::string m_name;
		std::string m_description = "<![CDATA[]]>";
		std::string m_styleUrl;
		bool m_isVisible = true;
};
}


#endif

