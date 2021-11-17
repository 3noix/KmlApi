#ifndef KML_ABSTRACT_ITEM
#define KML_ABSTRACT_ITEM


#include <string>


namespace Kml
{
class AbstractItem
{
	public:
		AbstractItem(const std::string &name);
		AbstractItem(const AbstractItem &other) = default;
		AbstractItem(AbstractItem &&other) = default;
		AbstractItem& operator=(const AbstractItem &other) = default;
		AbstractItem& operator=(AbstractItem &&other) = default;
		virtual ~AbstractItem() = default;


		virtual std::string toString(std::size_t tabs = 0) const = 0;

		AbstractItem& setName(const std::string &name);
		std::string name() const;

		AbstractItem& setDescription(const std::string &description);
		std::string description() const;

		AbstractItem& setStyleUrl(const std::string &styleUrl);
		std::string styleUrl() const;

		AbstractItem& setVisible(bool bVisible);
		bool isVisible() const;
		
		
	private:
		std::string m_name;
		std::string m_description = "<![CDATA[]]>";
		std::string m_styleUrl;
		bool m_isVisible = true;
};
}


#endif

