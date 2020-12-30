#ifndef KML_FOLDER
#define KML_FOLDER


#include "AbstractKmlItem.h"
#include <vector>
#include <memory>


class KmlFolder : public AbstractKmlItem
{
	public:
		KmlFolder(const QString &name) : AbstractKmlItem{name} {};
		KmlFolder(const KmlFolder &other) = default;
		KmlFolder(KmlFolder &&other) = default;
		KmlFolder& operator=(const KmlFolder &other) = default;
		KmlFolder& operator=(KmlFolder &&other) = default;
		virtual ~KmlFolder() = default;


		void setExpanded(bool expanded);
		bool isExpanded() const;

		void addItem(std::unique_ptr<AbstractKmlItem>&& item) {m_childItems.push_back(std::move(item));};
		
		virtual QString toString(int tabs = 0) const override final
		{
			QString prefix{tabs,'\t'};
			QString str;
			str += prefix + "<Folder>\n";
			str += prefix + "\t<name>" + this->name() + "</name>\n";
			str += prefix + "\t<description>" + this->description() + "</description>\n";
			str += prefix + "\t<styleUrl>" + this->styleUrl() + "</styleUrl>\n";
			str += prefix + "\t<visible>" + (this->isVisible() ? "1" : "0") + "</visible>\n";
			str += prefix + "\t<open>" + (m_expanded ? "1" : "0") + "</open>\n";
			for (const std::unique_ptr<AbstractKmlItem> &item : m_childItems) {str += item->toString(tabs+1);}
			str += prefix + "</Folder>\n";
			return str;
		};


	private:
		bool m_expanded = false;
		std::vector<std::unique_ptr<AbstractKmlItem>> m_childItems;
};


#endif

