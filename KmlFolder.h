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
		Folder(const std::string &name);
		Folder(const Folder &other) = default;
		Folder(Folder &&other) = default;
		Folder& operator=(const Folder &other) = default;
		Folder& operator=(Folder &&other) = default;
		virtual ~Folder() = default;


		Folder& setExpanded(bool expanded);
		bool isExpanded() const;

		Folder& addItem(std::unique_ptr<AbstractItem>&& item);
		
		virtual std::string toString(std::size_t tabs = 0) const override final;


	private:
		bool m_expanded = false;
		std::vector<std::unique_ptr<AbstractItem>> m_childItems;
};
}


#endif

