#include <QFile>
#include <QTextStream>
#include "snmp_oids.h"

// ------------------------------------------------------------------
SnmpOid::SnmpOid()
{
	clear();
}

// ------------------------------------------------------------------
SnmpOid::SnmpOid(const QString & oid_string, const QString & mibtxt)
{
	clear();

	QStringList slist = oid_string.split('.');

	bool ok;
	unsigned int ucw;

	int i, nc = slist.count();

	for(i = 1; i < nc; i++)
	{
		ucw = slist[i].toUInt(&ok);
		if(ok)
			m_vector.push_back(ucw);
		else
			break;
	}

	if(i != nc)
	{
		m_vector.clear();
		m_mibtxt.clear();
	}
	else
	{
		m_string = oid_string;
		m_mibtxt = mibtxt;
	}
}

// ------------------------------------------------------------------
SnmpOid::SnmpOid(const SnmpOid & other)
{
	clear();

	m_string = other.m_string;
	m_vector = other.m_vector;
	m_mibtxt = other.m_mibtxt;
}

// ------------------------------------------------------------------
SnmpOid::SnmpOid(SnmpOid & other)
{
	clear();

	m_string = other.m_string;
	m_vector = other.m_vector;
	m_mibtxt = other.m_mibtxt;
}

// ------------------------------------------------------------------
SnmpOid::SnmpOid(const QVector<oid> & oid_vector)
{
	clear();

	m_vector = oid_vector;
	m_mibtxt = QString("");

	for(QVector<oid>::const_iterator it = oid_vector.constBegin(); it != oid_vector.constEnd(); ++it)
		m_string += QString(".%1").arg(*it);
}

// ------------------------------------------------------------------
// пребразование OID из внутеннего SNMP-формата
SnmpOid::SnmpOid(const oid *name, const size_t name_length, const QString & mibtxt)
{
	clear();

	m_mibtxt = mibtxt;

	for(size_t i = 0; i < name_length; i++)
	{
		m_vector.push_back(name[i]);
		m_string += QString(".%1").arg(name[i]);
	}
}

// ------------------------------------------------------------------
void SnmpOid::clear()
{
	m_vector.clear();
	m_string.clear();
	m_mibtxt.clear();
}


// ------------------------------------------------------------------
QString SnmpOid::dump() const
{
	return isNull() ? QString("SnmpOid::Null") : mibName();
}

// ------------------------------------------------------------------
bool SnmpOid::isEmpty() const
{
	return m_vector.isEmpty();
}

// ------------------------------------------------------------------
bool SnmpOid::isNull() const
{
	return m_vector.isEmpty();
}

// ------------------------------------------------------------------
bool SnmpOid::isScalar() const
{
	return (!m_vector.isEmpty() && m_vector.last() == 0);
}

// ------------------------------------------------------------------
bool SnmpOid::isTable() const
{
	return (!m_vector.isEmpty() && m_vector.last() != 0);
}

// ------------------------------------------------------------------
bool SnmpOid::contains(const SnmpOid & soid) const
{
	bool result = false;

	QVector<oid> v = soid.toVector();

	if((v.size() > 0) && (v.size() <= m_vector.size()))
	{
		int counter = 0;

		QVector<oid>::const_iterator it1 = v.constBegin();
		QVector<oid>::const_iterator it2 = m_vector.constBegin();

		for(; it1 != v.constEnd() && it2 != m_vector.constEnd(); ++it1, ++it2)
		{
			if(*it1 == *it2)
				counter++;
		}

		if(counter == v.size())
		    result = true;
	}

	return result;
}

// ------------------------------------------------------------------
void SnmpOid::setMibName(const QString & mibtxt)
{
	m_mibtxt = mibtxt;
}

// ------------------------------------------------------------------
QString SnmpOid::mibName() const
{
	return (m_mibtxt.isEmpty() || m_mibtxt == QString("")) ? m_string : m_mibtxt;
}

// ------------------------------------------------------------------
void SnmpOid::setMibNameAndTail(const SnmpOid & soid)
{
	QString strFull = toString();
	QString strHead = soid.toString();
	QString strTail = strFull.replace(strHead, QString("")).replace('.','_');
	m_mibtxt = soid.mibName() + strTail;
}

// ------------------------------------------------------------------
QString SnmpOid::toString() const
{
	return m_string;
}

// ------------------------------------------------------------------
QVector<oid> SnmpOid::toVector() const
{
	return m_vector;
}

// ------------------------------------------------------------------
const SnmpOid & SnmpOid::operator=(const SnmpOid & other)
{
	clear();

	m_string = other.m_string;
	m_vector = other.m_vector;
	m_mibtxt = other.m_mibtxt;

//	for(QVector<oid>::const_iterator it = other.m_vector.constBegin(); it != other.m_vector.constEnd(); ++it)
//		m_vector.append(*it);

	return *this;
}

// ------------------------------------------------------------------
SnmpOid & SnmpOid::operator=(SnmpOid & other)
{
	clear();

	m_string = other.m_string;
	m_vector = other.m_vector;
	m_mibtxt = other.m_mibtxt;

//	for(QVector<oid>::const_iterator it = other.m_vector.constBegin(); it != other.m_vector.constEnd(); ++it)
//		m_vector.append(*it);

	return *this;
}

// ------------------------------------------------------------------
// сравнение для сортировки
bool SnmpOid::operator<(const SnmpOid & other) const
{
/*
	if(m_vector.size() != other.m_vector.size())
		return false;

	QVector<oid>::const_iterator it1 = m_vector.constBegin();
	QVector<oid>::const_iterator it2 = other.m_vector.constBegin();

	for( ; it1 != m_vector.constEnd(); ++it1, ++it2)
		if(*it1 != *it2)
			return false;

	return true;
*/
	const SnmpOid & othis = (const SnmpOid &) *this;
	int othis_length = othis.m_vector.size();

	const SnmpOid & oother = (const SnmpOid &) other;
	int oother_length = oother.m_vector.size();

	bool res = othis_length < oother_length;
	int nc = res ? othis_length : oother_length;

	for(int i = 0; i < nc; i++)
	{
		if(othis.m_vector[i] < oother.m_vector[i])
			return true;
		else if(othis.m_vector[i] > oother.m_vector[i])
			return false;
	}

	return res;
}

// ------------------------------------------------------------------
bool SnmpOid::operator==(const SnmpOid & other) const
{
	if(m_vector.size() != other.m_vector.size())
		return false;

	QVector<oid>::const_iterator it1 = m_vector.constBegin();
	QVector<oid>::const_iterator it2 = other.m_vector.constBegin();

	for( ; it1 != m_vector.constEnd(); ++it1, ++it2)
		if(*it1 != *it2)
			return false;

	return true;
}

// ------------------------------------------------------------------
SnmpOidList::SnmpOidList() : QList<SnmpOid>()
{
	clear();
}

// ------------------------------------------------------------------
SnmpOidList::SnmpOidList(const QStringList & list) : QList<SnmpOid>()
{
	clear();

	QList<QString>::const_iterator it;
	for(it = list.constBegin(); it != list.constEnd(); ++it)
		QList<SnmpOid>::append(SnmpOid(*it));
}

// ------------------------------------------------------------------
SnmpOidList::SnmpOidList(const SnmpOidList & list) : QList<SnmpOid>()
{
	clear();

	QList<SnmpOid>::const_iterator it;
	for(it = list.constBegin(); it != list.constEnd(); ++it)
		QList<SnmpOid>::append(SnmpOid(*it));
}

// ------------------------------------------------------------------
QStringList SnmpOidList::toStringList() const
{
	QStringList list;
	QList<SnmpOid>::const_iterator it;

	for(it = constBegin(); it != constEnd(); ++it)
		list.append((*it).toString());

	return list;
}

// ------------------------------------------------------------------
QString SnmpOidList::dump()
{
	QString str;
	QList<SnmpOid>::const_iterator it;

	for(it = constBegin(); it != constEnd(); ++it)
	{
		if(it != constBegin())
			str += QString("\n");
		str += (*it).toString();
	}

	return str;
}

// ------------------------------------------------------------------
void SnmpOidList::append(const QString & str)
{
	QStringList list = str.split(",");
	QString strOid = list.first();
	QString strTxt = (list.count() > 1) ? list.at(1).simplified() : QString("");
	append(SnmpOid(strOid, strTxt));
}

// ------------------------------------------------------------------
void SnmpOidList::append(const SnmpOid & soid)
{
	QList<SnmpOid>::append(soid);
}

// ------------------------------------------------------------------
SnmpOidMap::SnmpOidMap() : QMap<QString,SnmpOid>()
{
}

// ------------------------------------------------------------------
SnmpOidMap::SnmpOidMap(const SnmpOidMap & map) : QMap<QString,SnmpOid>()
{
	QMap<QString,SnmpOid>::const_iterator it;
	for(it = map.constBegin(); it != map.constEnd(); ++it)
	{
		QMap<QString,SnmpOid>::insert(it.key(), it.value());
	}
}

// ------------------------------------------------------------------
QString SnmpOidMap::dump()
{
	QString str;
	QMap<QString,SnmpOid>::const_iterator it;
	for(it = constBegin(); it != constEnd(); ++it)
	{
		if(it != constBegin())
			str += QString("\n");
		str += QString("%1 = %2").arg(it.key()).arg(it.value().toString());
	}
	return str;
}

// ------------------------------------------------------------------
SnmpResult::SnmpResult(const QString & string, const QVariant & value, const QDateTime & dt_updated)
{
	m_oid = SnmpOid(string);
	m_value = value;
	m_updated = dt_updated;
}

// ------------------------------------------------------------------
SnmpResult::SnmpResult(const SnmpOid & soid, const netsnmp_variable_list * vars, const QDateTime & dt_updated)
{
	m_oid = soid;
	m_value = translate(vars);
	m_updated = dt_updated;
}

// ------------------------------------------------------------------
bool SnmpResult::isNull() const
{
	return m_oid.isNull() || m_value.isNull() || m_updated.isNull();
}

// ------------------------------------------------------------------
SnmpOid SnmpResult::Oid() const
{
	return m_oid;
}

// ------------------------------------------------------------------
QVariant SnmpResult::value() const
{
	return m_value;
}

// ------------------------------------------------------------------
qint64 SnmpResult::updated(const QDateTime & dt_updated) const
{
	return m_updated.msecsTo(dt_updated);
}

// ------------------------------------------------------------------
QDateTime SnmpResult::updatedDateTime() const
{
	return m_updated;
}

// ------------------------------------------------------------------
void SnmpResult::clear()
{
	m_oid.clear();
	m_value = QVariant();
	m_updated = QDateTime();
}

// ------------------------------------------------------------------
QString SnmpResult::dump() const
{
	return QString("\"%1\": %2").arg(m_oid.dump()).arg(variantToString(m_value));
}

// ------------------------------------------------------------------
// перевод числа в сотых долях секунды в строку (для TIMETICKS)
QString SnmpResult::tmticks_toString(int iVal)
{
	QString str;
	int hsec = iVal % 100;
	int is = iVal / 100;
	int sec = is % 60;
	int im = is / 60;
	int min = im % 60;
	int ih = im / 60;
	int hour = ih % 24;
	int day = ih / 24;
	if(day)
		str += QString::number(day) + "days";
	if(hour < 10)
		str += "0";
	str += QString::number(hour) + ":";
	if(min < 10)
		str += "0";
	str += QString::number(min) + ":";
	if(sec < 10)
		str += "0";
	str += QString::number(sec) + ".";
	if(hsec < 10)
		str += "0";
	str += QString::number(hsec);
	return str;
}

// ------------------------------------------------------------------
QVariant SnmpResult::translate(const netsnmp_variable_list *vars)
{
	QVariant value;
	int iVal;
	QString wStr;
	QString sW;
	QByteArray char_str;
	QByteArray baIP;
	SnmpOid wOid;

	if(!vars)
		return QVariant::Invalid;

	switch(vars->type)
	{
		case ASN_INTEGER:
		case ASN_UNSIGNED:
		case ASN_COUNTER:
		case ASN_BOOLEAN:
				iVal = *(int*)(vars->val.integer);
				value = QVariant(iVal);
				break;

		case ASN_TIMETICKS:
				iVal = *(int*)(vars->val.integer);
				wStr = "(" + QString::number(iVal) + ") ";
				wStr += tmticks_toString(iVal);
				value = QVariant(wStr);
				break;

		case ASN_OBJECT_ID:
				wOid = SnmpOid((const oid *)vars->val.objid, vars->val_len / sizeof(oid));
				value = QVariant(wOid.toString());
				break;

		case ASN_OCTET_STR:
				char_str.resize(vars->val_len + 1);
				qstrncpy((char*)char_str.data(), (const char*)(vars->val.string), vars->val_len + 1);//+1 fix
				wStr.clear();
				sW = QString(char_str);
				if(sW.isEmpty() || vars->val_len == 6)
				{
					for(int j = 0; j < (int)vars->val_len; j++)
					{
						QString ns = (unsigned char)char_str[j] < 16 ? "0" : "";
						wStr += ns + (QString::number((unsigned char)char_str[j],16)).toUpper();
						if(j < ((int)vars->val_len - 1))
							wStr += ":";
					}
				}
				if(!sW.isEmpty() && QRegExp("[A-Za-z0-9_- ]+").exactMatch(sW))
					wStr = sW;
				value = QVariant(wStr);
				break;

		case ASN_IPADDRESS:
			baIP.resize(4);
			baIP[0] = vars->val.string[0];
			baIP[1] = vars->val.string[1];
			baIP[2] = vars->val.string[2];
			baIP[3] = vars->val.string[3];
			value = QVariant(baIP);
			break;

		default:
			value = QVariant::Invalid;
			break;
	}

	return value;
}

// ------------------------------------------------------------------
SnmpResultList::SnmpResultList() : QList<SnmpResult>()
{
}

// ------------------------------------------------------------------
SnmpResultList::SnmpResultList(const SnmpResultList & list) : QList<SnmpResult>()
{
	clear();
	operator+=(list);
}

// ------------------------------------------------------------------
SnmpResultList & SnmpResultList::operator+=(const SnmpResult & result)
{
	append(result);
	return *this;
}

// ------------------------------------------------------------------
SnmpResultList & SnmpResultList::operator+=(const SnmpResultList & list)
{
	for(SnmpResultList::const_iterator it = list.constBegin(); it != list.constEnd(); ++it)
		append(*it);
	return *this;
}

// ------------------------------------------------------------------
QString SnmpResultList::dump() const
{
	QString result;

	for(SnmpResultList::const_iterator it = constBegin(); it != constEnd(); ++it)
	{
		if(it != constBegin())
			result += QString("\n");
		result += (*it).dump();
	}

	return result;
}

// ------------------------------------------------------------------
SnmpResultMap::SnmpResultMap() : QMap<QString,SnmpResult>()
{
	resetChanged();
}

// ------------------------------------------------------------------
SnmpResultMap::SnmpResultMap(const SnmpResultMap & map) : QMap<QString,SnmpResult>()
{
	clear();
	resetChanged();
	operator+=(map);
}

// ------------------------------------------------------------------
SnmpResultMap::SnmpResultMap(const SnmpResultList & list) : QMap<QString,SnmpResult>()
{
	clear();
	resetChanged();
	operator+=(list);
}

// ------------------------------------------------------------------
SnmpResultMap & SnmpResultMap::operator+=(const SnmpResult & result)
{
	const QString key = result.Oid().toString();

	if(!contains(key))
	{
		m_changed = true;
	}
	else
	{
		const SnmpResult & val = value(key);
		if(val.value() != result.value())
		{
			m_changed = true;
		}
	}

	insert(key, result);
	return *this;
}

// ------------------------------------------------------------------
SnmpResultMap & SnmpResultMap::operator+=(const SnmpResultMap & map)
{
	for(SnmpResultMap::const_iterator it = map.constBegin(); it != map.constEnd(); ++it)
		operator+=(it.value());

	return *this;
}

// ------------------------------------------------------------------
SnmpResultMap & SnmpResultMap::operator+=(const SnmpResultList & list)
{
	for(SnmpResultList::const_iterator it = list.constBegin(); it != list.constEnd(); ++it)
		operator+=(*it);

	return *this;
}

// ------------------------------------------------------------------
QString SnmpResultMap::dump() const
{
	QString result;

	for(SnmpResultMap::const_iterator it = constBegin(); it != constEnd(); ++it)
	{
		if(it != constBegin())
			result += QString("\n");
		result += it.value().dump();
	}

	return result;
}

// ------------------------------------------------------------------
SnmpResultMap SnmpResultMap::toNamedMap()
{
	SnmpResultMap map;

	for(SnmpResultMap::const_iterator it = constBegin(); it != constEnd(); ++it)
	{
		const SnmpResult & result = it.value();
		QString name = result.Oid().mibName();

		if(name.isEmpty() || name == QString(""))
			name = result.Oid().toString();

		map.insert(name, result);
	}

	map.setChanged(isChanged());

	return map;
}

// ------------------------------------------------------------------
OID_from_mib::OID_from_mib()
{
// определить константы для сравнения (такие как enterprises) 
	oids_headers["mgmt"]		= SnmpOid(".1.3.6.1.2");
	oids_headers["mib-2"]		= SnmpOid(".1.3.6.1.2.1");
	oids_headers["private"]		= SnmpOid(".1.3.6.1.4");
	oids_headers["enterprises"]	= SnmpOid(".1.3.6.1.4.1");
}

// ------------------------------------------------------------------
// поиск base_oid_name в списке базовых OID
bool OID_from_mib::search_header(const QString & base_oid_name, SnmpOid *osw)
{
	QMap<QString, SnmpOid>::const_iterator it = oids_headers.constBegin();

	while(it != oids_headers.constEnd())
	{
		if(it.key() == base_oid_name)
		{
			*osw = it.value();
			break;
		}
		++it;
	}
	return osw->toString() != QString("") ? true : false; 
}

// ------------------------------------------------------------------
// установка заголовочного OID
int OID_from_mib::set_header(const QString & mibfname)
{
 int i,j=0,k;
// открыть, считать файл str_mibFirm, разбор по строкам
	QFile mibfile(mibfname);
//	qDebug((const char*)("mibfname "+ mibfname).data());
	if(mibfile.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&mibfile);
		QString strW = stream.readAll();
// ЯОХЯНЙ ЯРПНЙ
		sListW = strW.split("\x0a"); // !!! "\x00d\x00a" 
		mibfile.close();
		QString new_name("");
// определить IMPORTS
		int numstr = sListW.count();
		for(i=0; i<numstr; i++)
		{
			if(sListW[i].contains("IMPORTS"))
				break;
		}
		if(i==numstr)
			return 0;
// ищем строку MODULE-IDENTITY вторую
		int rep=0;
		for(k=i; k<numstr; k++)
		{
			if(sListW[k].contains("MODULE-IDENTITY"))
			{
				if(rep)
				{
					QStringList sww = sListW[k].split(QRegExp(" {1,10}"));
					new_name = sww[0]=="" ? sww[1] : sww[0];
					break;
				}
				else
					rep=1;
			}
		}
		if(k==numstr)
			return 0;
// ищем строку ::=
		for(j=k; j<sListW.count(); j++)
		{
//			qDebug("strNum %d", j);				
			if(sListW[j].contains("::="))
			{
				int nf = sListW[j].indexOf("{"); // !!! Ю ЕЯКХ МЕР
				QString sw = sListW[j].mid(nf+1);
				QStringList sww = sw.split(QRegExp(" {1,10}")); // !!! ХКХ МЕЯЙНКЭЙН
				if(sww.count()>1)
				{
// искать sww[0] в списке базовых OID
					int num = sww[0]=="" ? 1 : 0;
					SnmpOid osw;
// если есть в списке
					if(search_header(sww[num], &osw))
					{
// создать новый базовый OID
						QString nstr = osw.toString() + "." + sww[num+1];
						curr_oids_header = nstr;
						oids_headers[new_name] = SnmpOid(nstr);
					}
				}
				j++;
				break;
			}
		}
	}
	return j;
}

// ------------------------------------------------------------------
// установка заголовочного OID стандартного MIB-файла
int OID_from_mib::set_header_standart(int k)
{
	int numstr;
	lastnum = 0;
	QString new_name("");
// определить IMPORTS
	numstr = sListW.count();
	if(k==0)
	{
		for(;k<numstr; k++)
		{
			if(sListW[k].contains("IMPORTS"))
				break;
		}
		if(k==numstr)
			return 0;
	}
// ищем строку OBJECT IDENTIFIER ::=
	for(;k<numstr; k++)
	{
		if(sListW[k].contains("--"))
			continue;
		if(sListW[k].contains(QRegExp("OBJECT IDENTIFIER\\s+::="))) // n пробелов ::= !!!
		{
			QStringList sw = sListW[k].split(QRegExp(" {1,10}"));
//			sw.removeDuplicates();
			new_name = sw[0]=="" ? sw[1] : sw[0];
			SnmpOid osw;
// если new_name отсутствует в списке заголовков
			if(!search_header(new_name, &osw))
			{ // ищем имя родителя
				if(sListW[k].contains('{'))
				{
					int nf = sListW[k].indexOf("{");
					if(nf == -1)
						continue;
					QString sw = sListW[k].mid(nf+1);
					QStringList sww = sw.split(QRegExp(" {1,10}"));
//					sww.removeDuplicates();
					if(sww.count()>1)
					{
						sww[1].remove('}');
// искать sww[num] в списке базовых OID
						int num = sww[0]=="" ? 1 : 0;
						if(search_header(sww[num], &osw)) // есть
						{
// создать новый базовый OID
							QString nstr = osw.toString() + "." + sww[num+1];
							oids_headers[new_name] = SnmpOid(nstr);
							lastnum = k;
						}
					}
				}
			}
		}
		else 
		{
			QString sw = sListW[k];
			if(sListW[k].contains(QRegExp("\\w+ OBJECT-TYPE")))
				return lastnum;
		}
	}
	return lastnum;
}

// поиск OID (по тэгу OBJECT-TYPE)
// если встретился тэг OBJECT IDENTIFIER - прекращает поиск OID'ов
int OID_from_mib::oids_search(int ns)
{
	QString curr_name;
	QString curr_table;
	QString curr_table_name;
	SnmpOid osw;
	QStringList sww;
	QString sw;
	
	while(ns<sListW.count())
	{
		if(sListW[ns].contains("--"))
		{
			ns++;
			continue;
		}
		if(sListW[ns].contains("OBJECT-TYPE"))
		{
			sw = sListW[ns].trimmed();
			sww = sw.split(QRegExp(" {1,10}"));
//			sw.removeDuplicates();
			curr_name = sww[0]; // запоминаем имя параметра
			while(!sListW[++ns].contains("SYNTAX"))
			{
				if(ns>=sListW.count())
					goto EX;
			}
			sw = sListW[ns].trimmed();
			sww = sw.split(QRegExp(" {1,10}"));
			if(!sListW[ns].contains("SEQUENCE")) // параметр
			{
				while(!sListW[++ns].contains("::="))
				{
					if(ns>=sListW.count())
						goto EX;
				}
				int nf = sListW[ns].indexOf("{");
				sw = sListW[ns].mid(nf+1);
				sw = sw.trimmed();
				sww = sw.split(QRegExp(" {1,10}"));
				if(sww.count()>1)
				{
					int num = sww[0]=="" ? 2 : 1;
					sww[num].remove('}');
// формируем строку с OID параметра 
					QString shead; // = curr_oids_header.toString();
					SnmpOid osw;
// если new_name отсутствует в списке заголовков
					search_header(sww[num-1], &osw);
					shead = osw.toString();
					curr_oids_header = osw;
					QString sadd = shead + "." + sww[num] + "." + "0";
// добавляем в результирующий список
					oids_and_names[sadd] = curr_name;
				}
			}
			else // таблица
			{
				curr_table = curr_name; // имя таблицы
//				qDebug((const char*)curr_table_name.data());
				while(!sListW[++ns].contains("::="))
				{
					if(ns>=sListW.count())
						goto EX;
				}
				int nf = sListW[ns].indexOf("{");
				sw = sListW[ns].mid(nf+1);
				sw = sw.trimmed();
				sww = sw.split(QRegExp(" {1,10}"));
				if(sww.count()>1)
				{
					int num = sww[0]=="" ? 2 : 1;
					sww[num].remove('}');
					QString shead; // = curr_oids_header.toString();
					SnmpOid osw;
// если new_name отсутствует в списке заголовков
					search_header(sww[num-1], &osw);
					shead = osw.toString();
					curr_oids_header = osw;
// формируем строку с заголовком таблицы
					curr_oids_table_header = curr_oids_header.toString() + "." + sww[num] + "." + "1";
				}
				while(!sListW[++ns].contains("OBJECT-TYPE")) // имя таблицы
				{
					if(ns>=sListW.count())
						goto EX;
				}
				sw = sListW[ns].trimmed();
				sww = sw.split(QRegExp(" {1,10}"));
//				sww.removeDuplicates();
				if(sww.count()>1)
					curr_table_name = sww[0]; // имя таблицы
TABLE_BEGIN:
				while(!sListW[++ns].contains("OBJECT-TYPE")) // начало
				{
					if(ns>=sListW.count()-1)
						goto EX;
				}
				sw = sListW[ns].trimmed();
				sww = sw.split(QRegExp(" {1,10}"));
//			sw.removeDuplicates();
				curr_name = sww[0]; // запоминаем имя параметра
				int nbeg = ns-1;
				while(!sListW[++ns].contains("::=")) // параметр таблицы
				{
					if(ns>=sListW.count())
						return 0;
				}
				nf = sListW[ns].indexOf("{");
				sw = sListW[ns].mid(nf+1);
				sw = sw.trimmed();
				sww = sw.split(QRegExp(" {1,10}"));
				if(sww.count()>1)
				{
					int num = sww[0]=="" ? 1 : 0;
					sww[num+1].remove('}');
					if(sww[num]==curr_table_name)
// формируем строку с заголовком таблицы
					{
						QString sadd = curr_oids_table_header.toString() + "." + sww[num+1];
// добавляем в результирующий список
						oids_and_names[sadd] = curr_table + "." + curr_name;
						goto TABLE_BEGIN;
					}
					else // конец таблицы
						ns = nbeg;
				}
			}
		}
		else if(sListW[ns].contains("--"))
		{
			ns++;
			continue;
		}
		else if(sListW[ns].contains("OBJECT IDENTIFIER") && !sListW[ns].contains("SYNTAX"))
			return ns;
		ns++;
	}
EX:
	return 0;
}

// ------------------------------------------------------------------
void OID_from_mib::oids_create(QString str_mibfile, QString str_mibFirm, bool fl_lemz)
{
	oids_and_names.clear();
	QString sfirm;
	int ns;

// открыть, считать файл str_mibFirm, разбор по строкам
	QFile mibfile(str_mibfile);
	if (mibfile.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&mibfile);
		QString strW = stream.readAll();
// ЯОХЯНЙ ЯРПНЙ
		sListW =  strW.split("\x0a"); // !!! "\x00d\x00a" 
		mibfile.close();
	}
	else
		return;
	if(fl_lemz)
	{
		if(!str_mibFirm.isEmpty())
			set_header(str_mibFirm); // lemz
		ns = set_header(str_mibfile);
	}
	else
		ns = set_header_standart(0);

	ns = oids_search(ns+1);
	if(ns)
	{
		ns = set_header_standart(ns);
		ns = oids_search(ns+1);
	}
}

// ------------------------------------------------------------------
