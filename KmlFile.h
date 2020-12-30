#ifndef KML_FILE
#define KML_FILE


#include <map>
#include <vector>
#include <memory>
#include <QString>
#include <QFile>
#include "AbstractKmlItem.h"


class KmlFile
{
	public:
		KmlFile(const QString &name, const QString &description = "<![CDATA[]]>")
		{
			m_name = name;
			m_description = description;
			m_styles.insert({"paddleGreenDot","<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/green-dot.png</href></Icon></IconStyle>"});
			m_styles.insert({"paddleRedDot","<IconStyle><Icon><href>http://maps.gstatic.com/mapfiles/ms2/micons/red-dot.png</href></Icon></IconStyle>"});
			m_styles.insert({"blueLine5","<LineStyle><color>73FF0000</color><width>5</width></LineStyle>"});
		};

		KmlFile(const KmlFile &other) = delete;
		KmlFile(KmlFile &&other) = delete;
		KmlFile& operator=(const KmlFile &other) = delete;
		KmlFile& operator=(KmlFile &&other) = delete;
		~KmlFile() = default;


		void setName(const QString &name) {m_name = name;};
		QString name() const {return m_name;};

		void setDescription(const QString &description) {m_description = description;};
		QString description() const {return m_description;};

		void addStyle(const QString &styleUrl, const QString &styleContent) {m_styles.insert({styleUrl,styleContent});};
		void addItem(std::unique_ptr<AbstractKmlItem>&& item) {m_kmlItems.push_back(std::move(item));};


		QString toString() const
		{
			QString str = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			str += "<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\">\n";
			str += "\t<Document>\n";
			str += "\t\t<name>" + m_name + "</name>\n";
			str += "\t\t<description>" + m_description + "</description>\n";

			for (const auto& [id, content] : m_styles) {str += "\t\t<Style id=\"" + id + "\">" + content + "</Style>\n";}
			for (const std::unique_ptr<AbstractKmlItem> &item : m_kmlItems) {str += item->toString(2);}

			str += "\t</Document>\n";
			str += "</kml>\n";
			return str;
		};

		bool write(const QString &filePath)
		{
			QFile file{filePath};
			if (!file.open(QIODevice::WriteOnly)) {return false;}
			file.write(this->toString().toUtf8());
			file.close();
			return true;
		};
		
		
	private:
		QString m_name;
		QString m_description;
		std::map<QString,QString> m_styles; // the key is the id (or url), the value is the xml content
		std::vector<std::unique_ptr<AbstractKmlItem>> m_kmlItems;
};


#endif

