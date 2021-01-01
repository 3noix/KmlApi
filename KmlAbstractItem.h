#ifndef KML_ABSTRACT_ITEM
#define KML_ABSTRACT_ITEM


#include <QString>
#include "KmlAltitudeMode.h"


namespace Kml
{
class AbstractItem
{
	public:
		AbstractItem(const QString &name) {m_name = name;};
		AbstractItem(const AbstractItem &other) = default;
		AbstractItem(AbstractItem &&other) = default;
		AbstractItem& operator=(const AbstractItem &other) = default;
		AbstractItem& operator=(AbstractItem &&other) = default;
		virtual ~AbstractItem() = default;


		virtual QString toString(int tabs = 0) const = 0;

		void setName(const QString &name) {m_name = name;};
		QString name() const {return m_name;};

		void setDescription(const QString &description) {m_description = description;};
		QString description() const {return m_description;};

		void setStyleUrl(const QString &styleUrl) {m_styleUrl = styleUrl;};
		QString styleUrl() const {return m_styleUrl;};

		void setVisible(bool bVisible) {m_isVisible = bVisible;};
		bool isVisible() const {return m_isVisible;};
		
		
	private:
		QString m_name;
		QString m_description = "<![CDATA[]]>";
		QString m_styleUrl;
		bool m_isVisible = true;
};
}


#endif

