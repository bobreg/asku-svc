#include "globalvar.h"
#include "svcapplication.h"

//-----------------------------------------------------------------------------
AskuSvcApplication::AskuSvcApplication(int & argc, char** argv) 
	: AskuApplication(argc, argv)
{
	svcModule = NULL;
	m_gprOverride = -1;

	if(argc > 1)
	{
		QString sargv(argv[1]);
		if(sargv == "-gpr1")
			m_gprOverride = IDGPR1;
		if(sargv == "-gpr2")
			m_gprOverride = IDGPR2;
	}

	if(!m_appDoubleCopy && m_testDoubleCopy && m_gprOverride < 0)
		return;

	setApplicationVersion("0.8.0.18 (19.09.2019)");
	loadSettings();

	svcModule = new AskuSvcModule(this, IDGPR());
}

//-----------------------------------------------------------------------------
AskuSvcApplication::~AskuSvcApplication()
{
	if(svcModule != NULL)
	{
		delete svcModule;
		svcModule = NULL;
	}
}

//-----------------------------------------------------------------------------
bool AskuSvcApplication::readSettings(QSettings &m_settings)
{
	bool data_error = false;

	m_settings.beginGroup("/setup");
		m_setup.main.id = m_settings.value("/id", 255).toUInt();
		if(m_setup.main.id == 255)
		{
			qDebug("%s: error in settings data",qPrintable(m_appName));
			data_error = true;
			m_setup.main.id = 0;
		}
		m_setup.main.mobile = m_settings.value("/mobile", false).toBool();
		m_setup.main.litera = m_settings.value("/litera", LITERA_A).toUInt();
		m_setup.main.main = false;
	m_settings.endGroup();

	if(m_gprOverride != -1)
		m_setup.main.id = m_gprOverride;

	LogInfo("Settings GPR%d", IDGPR() + 1);

	m_settings.beginGroup("/gpr1");
		m_setup.gpr1.ip = QHostAddress(m_settings.value("/ip", "192.0.1.5").toString());
		m_setup.gpr1.port = m_settings.value("/port", 5555).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/gpr2");
		m_setup.gpr2.ip = QHostAddress(m_settings.value("/ip", "192.0.1.6").toString());
		m_setup.gpr2.port = m_settings.value("/port", 5555).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/poi");
		m_setup.poi.ip = QHostAddress(m_settings.value("/ip", "127.0.0.1").toString());
		m_setup.poi.port = m_settings.value("/port", 17024).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/vrl1");
		m_setup.vrl1.ip = QHostAddress(m_settings.value("/ip", "192.0.1.3").toString());
		m_setup.vrl1.port = m_settings.value("/port", 16928).toUInt();
		m_setup.vrl1.port_listen = m_settings.value("/port_listen", 16928).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/vrl2");
		m_setup.vrl2.ip = QHostAddress(m_settings.value("/ip", "192.0.1.4").toString());
		m_setup.vrl2.port = m_settings.value("/port", 16928).toUInt();
		m_setup.vrl2.port_listen = m_settings.value("/port_listen", 16928).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/com1");
		m_setup.com1.ip = QHostAddress(m_settings.value("/ip", "192.0.1.13").toString());
	m_settings.endGroup();

	m_settings.beginGroup("/com2");
		m_setup.com2.ip = QHostAddress(m_settings.value("/ip", "192.0.1.11").toString());
	m_settings.endGroup();

	m_settings.beginGroup("/asku");
		m_setup.asku.port1 = m_settings.value("/port1", 24575).toUInt();
		m_setup.asku.port2 = m_settings.value("/port2", 24575).toUInt();
		m_setup.asku.log   = m_settings.value("/log", 0).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/drive");
		m_setup.drive.port1    = m_settings.value("/port1", 24579).toUInt();
		m_setup.drive.port2    = m_settings.value("/port2", 24579).toUInt();
		m_setup.drive.address1 = m_settings.value("/address1", 1).toUInt();
		m_setup.drive.address2 = m_settings.value("/address2", 2).toUInt();
		m_setup.drive.speed1   = m_settings.value("/speed1", 36.0).toDouble();
		m_setup.drive.speed2   = m_settings.value("/speed2", 72.0).toDouble();
	m_settings.endGroup();

	m_settings.beginGroup("/coolers");
		m_setup.coolers.port1     = m_settings.value("/port1", 24577).toUInt();
		m_setup.coolers.port2     = m_settings.value("/port2", 24577).toUInt();
		m_setup.coolers.address1  = m_settings.value("/address1", 1).toUInt();
		m_setup.coolers.address2  = m_settings.value("/address2", 2).toUInt();
		m_setup.coolers.address3  = m_settings.value("/address3", 3).toUInt();
		m_setup.coolers.address4  = m_settings.value("/address4", 4).toUInt();
		m_setup.coolers.frequency = m_settings.value("/frequency", 50.0).toDouble();
	m_settings.endGroup();

	m_settings.beginGroup("/ups");
		m_setup.ups.type           = m_settings.value("/type", 4).toUInt();
		m_setup.ups.ip1            = QHostAddress(m_settings.value("/ip1", "192.0.1.60").toString());
		m_setup.ups.ip2            = QHostAddress(m_settings.value("/ip2", "192.0.1.61").toString());
		m_setup.ups.port           = m_settings.value("/port", 24581).toUInt();
		m_setup.ups.address        = m_settings.value("/address", 29).toUInt();
		m_setup.ups.snmp_community = m_settings.value("/snmp_community", "public").toString();
		m_setup.ups.snmp_version   = m_settings.value("/snmp_version", 1).toUInt();
		m_setup.ups.snmp_timeout   = m_settings.value("/snmp_timeout", 1000).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/des");
		m_setup.des.ip             = QHostAddress(m_settings.value("/ip", "192.0.1.80").toString());
		m_setup.des.port           = m_settings.value("/port", 25000).toUInt();
		m_setup.des.mains_address1 = m_settings.value("/mains_address1", 17).toUInt();
		m_setup.des.mains_address2 = m_settings.value("/mains_address2", 18).toUInt();
		m_setup.des.dg_address1    = m_settings.value("/dg_address1", 1).toUInt();
		m_setup.des.dg_address2    = m_settings.value("/dg_address2", 2).toUInt();
		m_setup.des.dg_address3    = m_settings.value("/dg_address3", 3).toUInt();
		m_setup.des.dg_address4    = m_settings.value("/dg_address4", 4).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/pwm");
		m_setup.pwm.pwrFail = m_settings.value("/fail", 50000).toUInt();
		m_setup.pwm.pwrLow  = m_settings.value("/low" , 55000).toUInt();
		m_setup.pwm.pwrGate = m_settings.value("/gate", 1000).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/phase");
		m_setup.phase.fileEtalon  = m_settings.value("etalon", "etalon.phf").toString();
		m_setup.phase.fileCurrent = m_settings.value("current", "current.phf").toString();
	m_settings.endGroup();

	m_settings.beginGroup("/koeff_poi");
		m_setup.koeffPoi.kshAvar  = m_settings.value("/kshAvar",  4.0).toDouble();
		m_setup.koeffPoi.kshError = m_settings.value("/kshError", 2.0).toDouble();
		m_setup.koeffPoi.kshNorma = m_settings.value("/kshNorma", 1.0).toDouble();
		m_setup.koeffPoi.psNorma  = m_settings.value("/psNorma", 40.0).toDouble();
		m_setup.koeffPoi.kpNorma  = m_settings.value("/kpNorma", 30.0).toDouble();
	m_settings.endGroup();

	m_settings.beginGroup("/voi");
		m_setup.voi.ip       = QHostAddress(m_settings.value("/ip", "127.0.0.1").toString());
		m_setup.voi.port_in  = m_settings.value("/port_in", 0x4001).toUInt();
		m_setup.voi.port_out = m_settings.value("/port_out", 0x4000).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/n106");
		m_setup.n106.ip       = QHostAddress(m_settings.value("/ip", "192.0.1.21").toString());
		m_setup.n106.port_in  = m_settings.value("/port_in", 0x4001).toUInt();
		m_setup.n106.port_out = m_settings.value("/port_out", 0x4000).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/pos");
		m_setup.pos.ip = QHostAddress(m_settings.value("/ip", "192.0.1.100").toString());
		m_setup.pos.port = m_settings.value("/port", 11223).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/skrps");
		m_setup.skrps.skr_azimuth = m_settings.value("/skr_az", 0).toUInt();
		m_setup.skrps.ps_azimuth  = m_settings.value("/ps_az", 33).toUInt();
		m_setup.skrps.skr_strobe  = m_settings.value("/skr_strobe", 1).toUInt();
		m_setup.skrps.ps_strobe   = m_settings.value("/ps_strobe", 1).toUInt();
		m_setup.skrps.period      = m_settings.value("/period", 0).toUInt();
		m_setup.skrps.offset      = m_settings.value("/offset", 0).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/path");
		m_setup.path.tables = m_settings.value("/tables", "/opt/amcs-observer/tables").toString();
		m_setup.path.log    = m_settings.value("/log",    "/opt/amcs-observer/log_files").toString();
		m_setup.path.phase  = m_settings.value("/phase",  "/opt/amcs-observer/phase").toString();
	m_settings.endGroup();

	m_settings.beginGroup("/viewer");
		m_setup.viewer.days = m_settings.value("/days", 365).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/module");
		m_setup.module.fileMode       = m_settings.value("/fileMode",    "mode.xml").toString();
		m_setup.module.fileRipch      = m_settings.value("/fileRipch",   "ripch.xml").toString();
		m_setup.module.fileSwitch     = m_settings.value("/fileSwitch",  "switch.xml").toString();
		m_setup.module.fileDisable    = m_settings.value("/fileDisable", "disable.xml").toString();
		m_setup.module.fileNchm       = m_settings.value("/fileNchm",    "v4_pha.tab").toString();
		m_setup.module.lir1_offset    = m_settings.value("/lir1_offset", 0).toUInt();
		m_setup.module.lir2_offset    = m_settings.value("/lir2_offset", 0).toUInt();
		m_setup.module.freq_deviation = m_settings.value("/freq_deviation", 5368709).toUInt();
		m_setup.module.lastMode       = m_settings.value("/lastMode", 0).toUInt();
	m_settings.endGroup();

	m_settings.beginGroup("/vospd");
		m_setup.vospd.type            = m_settings.value("/type", 1).toUInt();
		m_setup.vospd.ip1             = QHostAddress(m_settings.value("/ip1", "192.0.1.110").toString());
		m_setup.vospd.ip2             = QHostAddress(m_settings.value("/ip2", "192.0.1.111").toString());
		m_setup.vospd.port            = m_settings.value("/port", 24587).toUInt();
	m_settings.endGroup();

	return (data_error || (m_settings.status() != QSettings::NoError));
}

//-----------------------------------------------------------------------------
bool AskuSvcApplication::writeSettings(QSettings &m_settings)
{
	m_settings.beginGroup("/setup");
		m_settings.setValue("/id", m_setup.main.id);
		m_settings.setValue("/mobile", m_setup.main.mobile);
		m_settings.setValue("/litera", m_setup.main.litera);
	m_settings.endGroup();

	m_settings.beginGroup("/gpr1");
		m_settings.setValue("/ip", m_setup.gpr1.ip.toString());
		m_settings.setValue("/port", m_setup.gpr1.port);
	m_settings.endGroup();

	m_settings.beginGroup("/gpr2");
		m_settings.setValue("/ip", m_setup.gpr2.ip.toString());
		m_settings.setValue("/port", m_setup.gpr2.port);
	m_settings.endGroup();

	m_settings.beginGroup("/poi");
		m_settings.setValue("/ip", m_setup.poi.ip.toString());
		m_settings.setValue("/port", m_setup.poi.port);
	m_settings.endGroup();

	m_settings.beginGroup("/vrl1");
		m_settings.setValue("/ip", m_setup.vrl1.ip.toString());
		m_settings.setValue("/port", m_setup.vrl1.port);
		m_settings.setValue("/port_listen", m_setup.vrl1.port_listen);
	m_settings.endGroup();

	m_settings.beginGroup("/vrl2");
		m_settings.setValue("/ip", m_setup.vrl2.ip.toString());
		m_settings.setValue("/port", m_setup.vrl2.port);
		m_settings.setValue("/port_listen", m_setup.vrl2.port_listen);
	m_settings.endGroup();

	m_settings.beginGroup("/com1");
		m_settings.setValue("/ip",    m_setup.com1.ip.toString());
	m_settings.endGroup();

	m_settings.beginGroup("/com2");
		m_settings.setValue("/ip",    m_setup.com2.ip.toString());
	m_settings.endGroup();

	m_settings.beginGroup("/voi");
		m_settings.setValue("/ip",       m_setup.voi.ip.toString());
		m_settings.setValue("/port_in",  m_setup.voi.port_in);
		m_settings.setValue("/port_out", m_setup.voi.port_out);
	m_settings.endGroup();

	m_settings.beginGroup("/n106");
		m_settings.setValue("/ip",       m_setup.n106.ip.toString());
		m_settings.setValue("/port_in",  m_setup.n106.port_in);
		m_settings.setValue("/port_out", m_setup.n106.port_out);
	m_settings.endGroup();

	m_settings.beginGroup("/asku");
		m_settings.setValue("/port1", m_setup.asku.port1);
		m_settings.setValue("/port2", m_setup.asku.port2);
		m_settings.setValue("/log",   m_setup.asku.log);
	m_settings.endGroup();

	m_settings.beginGroup("/drive");
		m_settings.setValue("/port1",    m_setup.drive.port1);
		m_settings.setValue("/port2",    m_setup.drive.port2);
		m_settings.setValue("/address1", m_setup.drive.address1);
		m_settings.setValue("/address2", m_setup.drive.address2);
		m_settings.setValue("/speed1",   m_setup.drive.speed1);
		m_settings.setValue("/speed2",   m_setup.drive.speed2);
	m_settings.endGroup();

	m_settings.beginGroup("/coolers");
		m_settings.setValue("/port1",     m_setup.coolers.port1);
		m_settings.setValue("/port2",     m_setup.coolers.port2);
		m_settings.setValue("/address1",  m_setup.coolers.address1);
		m_settings.setValue("/address2",  m_setup.coolers.address2);
		m_settings.setValue("/address3",  m_setup.coolers.address3);
		m_settings.setValue("/address4",  m_setup.coolers.address4);
		m_settings.setValue("/frequency", m_setup.coolers.frequency);
	m_settings.endGroup();

	m_settings.beginGroup("/ups");
		m_settings.setValue("/type",           m_setup.ups.type);
		m_settings.setValue("/ip1",            m_setup.ups.ip1.toString());
		m_settings.setValue("/ip2",            m_setup.ups.ip2.toString());
		m_settings.setValue("/port",           m_setup.ups.port);
		m_settings.setValue("/address",        m_setup.ups.address);
		m_settings.setValue("/snmp_community", m_setup.ups.snmp_community);
		m_settings.setValue("/snmp_version",   m_setup.ups.snmp_version);
		m_settings.setValue("/snmp_timeout",   m_setup.ups.snmp_timeout);
	m_settings.endGroup();

	m_settings.beginGroup("/des");
		m_settings.setValue("/ip",             m_setup.des.ip.toString());
		m_settings.setValue("/port",           m_setup.des.port);
		m_settings.setValue("/mains_address1", m_setup.des.mains_address1);
		m_settings.setValue("/mains_address2", m_setup.des.mains_address2);
		m_settings.setValue("/dg_address1",    m_setup.des.dg_address1);
		m_settings.setValue("/dg_address2",    m_setup.des.dg_address2);
		m_settings.setValue("/dg_address3",    m_setup.des.dg_address3);
		m_settings.setValue("/dg_address4",    m_setup.des.dg_address4);
	m_settings.endGroup();

	m_settings.beginGroup("/pwm");
		m_settings.setValue("/fail", m_setup.pwm.pwrFail);
		m_settings.setValue("/low",  m_setup.pwm.pwrLow);
		m_settings.setValue("/gate", m_setup.pwm.pwrGate);
	m_settings.endGroup();

	m_settings.beginGroup("/pos");
		m_settings.setValue("/ip", m_setup.pos.ip.toString());
		m_settings.setValue("/port", m_setup.pos.port);
	m_settings.endGroup();

	m_settings.beginGroup("/phase");
		m_settings.setValue("/etalon",  m_setup.phase.fileEtalon);
		m_settings.setValue("/current", m_setup.phase.fileCurrent);
	m_settings.endGroup();

	m_settings.beginGroup("/koeff_poi");
		m_settings.setValue("/kshAvar",  m_setup.koeffPoi.kshAvar);
		m_settings.setValue("/kshError", m_setup.koeffPoi.kshError);
		m_settings.setValue("/kshNorma", m_setup.koeffPoi.kshNorma);
		m_settings.setValue("/psNorma",  m_setup.koeffPoi.psNorma);
		m_settings.setValue("/kpNorma",  m_setup.koeffPoi.kpNorma);
	m_settings.endGroup();

	m_settings.beginGroup("/skrps");
		m_settings.setValue("/skr_az",     m_setup.skrps.skr_azimuth);
		m_settings.setValue("/ps_az",      m_setup.skrps.ps_azimuth);
		m_settings.setValue("/skr_strobe", m_setup.skrps.skr_strobe);
		m_settings.setValue("/ps_strobe",  m_setup.skrps.ps_strobe);
		m_settings.setValue("/period",     m_setup.skrps.period);
		m_settings.setValue("/offset",     m_setup.skrps.offset);
	m_settings.endGroup();

	m_settings.beginGroup("/path");
		m_settings.setValue("/tables", m_setup.path.tables);
		m_settings.setValue("/log",    m_setup.path.log);
		m_settings.setValue("/phase",  m_setup.path.phase);
	m_settings.endGroup();

	m_settings.beginGroup("/viewer");
		m_settings.setValue("/days",    m_setup.viewer.days);
	m_settings.endGroup();

	m_settings.beginGroup("/module");
		m_settings.setValue("/fileMode",       m_setup.module.fileMode);
		m_settings.setValue("/fileSwitch",     m_setup.module.fileSwitch);
		m_settings.setValue("/fileRipch",      m_setup.module.fileRipch);
		m_settings.setValue("/fileDisable",    m_setup.module.fileDisable);
		m_settings.setValue("/fileNchm",       m_setup.module.fileNchm);
		m_settings.setValue("/lir1_offset",    m_setup.module.lir1_offset);
		m_settings.setValue("/lir2_offset",    m_setup.module.lir2_offset);
		m_settings.setValue("/freq_deviation", m_setup.module.freq_deviation);
		m_settings.setValue("/lastMode",       m_setup.module.lastMode);
	m_settings.endGroup();

	m_settings.beginGroup("/vospd");
		m_settings.setValue("/type",           m_setup.vospd.type);
		m_settings.setValue("/ip1",            m_setup.vospd.ip1.toString());
		m_settings.setValue("/ip2",            m_setup.vospd.ip2.toString());
		m_settings.setValue("/port",           m_setup.vospd.port);
	m_settings.endGroup();

	return (m_settings.status() != QSettings::NoError);
}

//-----------------------------------------------------------------------------
