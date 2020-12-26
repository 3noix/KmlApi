#ifndef SPECIAL_POINT
#define SPECIAL_POINT


#include <QString>
#include "AltitudeMode.h"
#include "Point.h"


class SpecialPoint
{
	public:
		SpecialPoint(const QString &name, const Point &p, AltitudeMode altMode = AltitudeMode::Absolute)
		{
			m_name = name;
			m_point = p;
			m_altMode = altMode;
		};

		SpecialPoint(const SpecialPoint &other) = default;
		SpecialPoint(SpecialPoint &&other) = default;
		SpecialPoint& operator=(const SpecialPoint &other) = default;
		SpecialPoint& operator=(SpecialPoint &&other) = default;
		~SpecialPoint() = default;
		

		void setName(const QString &name) {m_name = name;};
		QString name() const {return m_name;};

		void setPoint(const Point &p) {m_point = p;};
		const Point& point() const {return m_point;};

		void setDescription(const QString &description) {m_description = description;};
		QString description() const {return m_description;};

		void setStyleUrl(const QString &styleUrl) {m_styleUrl = styleUrl;};
		QString styleUrl() const {return m_styleUrl;};

		void setAltitudeMode(AltitudeMode am) {m_altMode = am;};
		AltitudeMode altitudeMode() const {return m_altMode;};


	private:
		QString m_name;
		Point m_point;
		QString m_description = "<![CDATA[]]>";
		QString m_styleUrl;
		AltitudeMode m_altMode = AltitudeMode::Absolute;
		friend class KmlFile;
};


#endif

