#ifndef __SNMP_OIDS_H__
#define __SNMP_OIDS_H__

// ------------------------------------------------------------------

#include <qglobal.h>

#include <QVariant>
#include <QVector>
#include <QList>
#include <QMap>
#include <QStringList>
#include <QDateTime>

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/utilities.h>
#include <net-snmp/net-snmp-includes.h>

#include "globalvar.h"

// ------------------------------------------------------------------
// OID
class SnmpOid
{
protected:
	QVector<oid> m_vector;
	QString m_string;
	QString m_mibtxt;

public:
	SnmpOid();
	SnmpOid(const QString & oid_string, const QString & mibtxt = QString(""));
	SnmpOid(const QVector<oid> & oid_vector);
	SnmpOid(SnmpOid & other);
	SnmpOid(const SnmpOid & other);
	SnmpOid(const oid *name, const size_t name_length, const QString & mibtxt = QString(""));

	const SnmpOid & operator=(const SnmpOid & other);
	SnmpOid & operator=(SnmpOid & other);

	QString dump() const;

	bool isNull() const;
	bool isEmpty() const;
	bool isScalar() const;
	bool isTable() const;

	void setMibName(const QString & oid_name);
	QString mibName() const;
	void setMibNameAndTail(const SnmpOid & soid);

	bool contains(const SnmpOid & soid) const;

	QString toString() const;
	QVector<oid> toVector() const;

	void clear();

	bool operator<(const SnmpOid & other) const;
	bool operator==(const SnmpOid & other) const;
};

// ------------------------------------------------------------------
// OID List
class SnmpOidList : public QList<SnmpOid>
{
public:
	SnmpOidList();
	SnmpOidList(const QStringList & list);
	SnmpOidList(const SnmpOidList & list);

	QStringList toStringList() const;

	void append(const QString & str);
	void append(const SnmpOid & soid);

	QString dump();
};

// ------------------------------------------------------------------
// OID Map
class SnmpOidMap : public QMap<QString,SnmpOid>
{
public:
	SnmpOidMap();
	SnmpOidMap(const SnmpOidMap & map);

	QString dump();
};

// ------------------------------------------------------------------
// Result
class SnmpResult
{
protected:
	SnmpOid m_oid;
	QVariant m_value;
	QDateTime m_updated;

public:
	SnmpResult(const QString & string = QString(), const QVariant & value = QVariant(), const QDateTime & dt_updated = QDateTime::currentDateTime());
	SnmpResult(const SnmpOid & soid, const netsnmp_variable_list * vars = NULL, const QDateTime & dt_updated = QDateTime::currentDateTime());

	QString dump() const;

	bool isNull() const;
	SnmpOid Oid() const;
	QVariant value() const;
	qint64 updated(const QDateTime & dt_updated = QDateTime::currentDateTime()) const;
	QDateTime updatedDateTime() const;

	void clear();

	static QVariant translate(const netsnmp_variable_list *vars);
	static QString tmticks_toString(int iVal);
};

// ------------------------------------------------------------------
// Result List
class SnmpResultList : public QList<SnmpResult>
{
public:
	SnmpResultList();
	SnmpResultList(const SnmpResultList & list);

	SnmpResultList & operator+=(const SnmpResult & result);
	SnmpResultList & operator+=(const SnmpResultList & list);

	QString dump() const;
};

// ------------------------------------------------------------------
// Result Map
class SnmpResultMap : public QMap<QString,SnmpResult>
{
	bool m_changed;

public:
	SnmpResultMap();
	SnmpResultMap(const SnmpResultMap & map);
	SnmpResultMap(const SnmpResultList & list);

	SnmpResultMap & operator+=(const SnmpResult & result);
	SnmpResultMap & operator+=(const SnmpResultMap & map);
	SnmpResultMap & operator+=(const SnmpResultList & list);

	QString dump() const;

	void resetChanged() {
		m_changed = false;
	}

	void setChanged(bool changed) {
		m_changed = changed;
	}

	bool isChanged() const {
		return m_changed;
	}

	SnmpResultMap toNamedMap();
};

// ------------------------------------------------------------------
// класс, реализующий образование списка OID из заданного MIB-файла 
class OID_from_mib
{
protected:
	QStringList sListW;
	int lastnum;

// результат
	QMap<QString, QString> oids_and_names;

// часть OID'а до параметров MIB-файла
	QMap<QString, SnmpOid> oids_headers;

// заголовок для параметров str_mibfile
	SnmpOid curr_oids_header;
	SnmpOid curr_oids_table_header;

public:
	OID_from_mib();

// поиск base_oid_name в списке базовых OID 
	bool search_header(const QString & base_oid_name, SnmpOid *osw);

//установка заголовочного OID 
	int set_header(const QString & mibfname);

//установка заголовочного OID стандартного MIB-файла 
	int set_header_standart(int k);

// поиск OID (по тэгу OBJECT-TYPE)
// если встретился тэг OBJECT IDENTIFIER - прекращает поиск OID'ов 
	int oids_search(int ns);

	void oids_create(QString str_mibfile, QString str_mibFirm = QString(), bool fl_lemz = true);
};

// ------------------------------------------------------------------

#endif // __SNMP_OIDS_H__
