#ifndef KML_FOLDER
#define KML_FOLDER


#include "KmlAbstractItem.h"
#include <vector>
#include <memory>


namespace Kml
{
class Folder : public AbstractItem
{
	public:
		Folder(const std::string &name) : AbstractItem{name} {};
		Folder(const Folder &other) = default;
		Folder(Folder &&other) = default;
		Folder& operator=(const Folder &other) = default;
		Folder& operator=(Folder &&other) = default;
		virtual ~Folder() = default;


		void setExpanded(bool expanded) {m_expanded = expanded;};
		bool isExpanded() const {return m_expanded;};

		void addItem(std::unique_ptr<AbstractItem>&& item) {m_childItems.push_back(std::move(item));};
		
		virtual std::string toString(std::size_t tabs = 0) const override final
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
		};


	private:
		bool m_expanded = false;
		std::vector<std::unique_ptr<AbstractItem>> m_childItems;
};
}


#endif

