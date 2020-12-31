#ifndef ABSTRACT_KML_ITEM
#define ABSTRACT_KML_ITEM


#include <QString>
#include "AltitudeMode.h"


class AbstractKmlItem
{
	public:
		AbstractKmlItem(const QString &name) {m_name = name;};
		AbstractKmlItem(const AbstractKmlItem &other) = default;
		AbstractKmlItem(AbstractKmlItem &&other) = default;
		AbstractKmlItem& operator=(const AbstractKmlItem &other) = default;
		AbstractKmlItem& operator=(AbstractKmlItem &&other) = default;
		virtual ~AbstractKmlItem() = default;


		virtual QString toString(int tabs = 0) const = 0;

		void setName(const QString &name) {m_name = name;};
		QString name() const {return m_name;};

		void setDescription(const QString &description) {m_description = description;};
		QString description() const {return m_description;};

		void setStyleUrl(const QString &styleUrl) {m_styleUrl = styleUrl;};
		QString styleUrl() const {return m_styleUrl;};

		void setVisible(bool bVisible) {m_isVisible = bVisible;};
		bool isVisible() const {return m_isVisible;};


	protected:
		static QString altitudeModeToStr(AltitudeMode am)
		{
			if (am == AltitudeMode::Absolute)           {return "<altitudeMode>absolute</altitudeMode>";}
			if (am == AltitudeMode::ClampToGround)      {return "<altitudeMode>clampToGround</altitudeMode>";}
			if (am == AltitudeMode::ClampToSeaFloor)    {return "<gx:altitudeMode>clampToSeaFloor</gx:altitudeMode>";}
			if (am == AltitudeMode::RelativeToGround)   {return "<altitudeMode>relativeToGround</altitudeMode>";}
			if (am == AltitudeMode::RelativeToSeaFloor) {return "<gx:altitudeMode>relativeToSeaFloor</gx:altitudeMode>";}
			return "<altitudeMode>absolute</altitudeMode>";
		};
		
		
	private:
		QString m_name;
		QString m_description = "<![CDATA[]]>";
		QString m_styleUrl;
		bool m_isVisible = true;
};


#endif

