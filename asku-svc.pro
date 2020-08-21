CONFIG += asku-console net-snmp coretemp
TARGET = asku-svc
DEFINES += APPNAME=\\\"$(TARGET)\\\"

include (../asku.pri)

unix {
	target.files += $${TARGET}
	target.path = $$[QT_INSTALL_BINS]

	icons.files += ../install/*.png
	icons.path = /usr/share/$${TARGET}

	INSTALLS += target icons

	net-snmp {
		exists( /usr/bin/net-snmp-config )
		{
			DEFINES += NET_SNMP_LIB
			LIBS += $$system( net-snmp-config --netsnmp-libs )
		}
	}

	coretemp {
		exists( /usr/bin/sensors )
		{
			DEFINES += LM_SENSORS_LIB
			LIBS += -lsensors
		}
	}
}

HEADERS += ../common/global.h \
	../common/application.h \
	../common/module.h \
	../common/tcpnetwork.h \
	../common/udpnetwork.h \
	../common/logger.h \
	../common/protocol.h \
	../common/parser.h \
	../common/connection.h \
	../common/xmlfile.h \
	../common/jsonfile.h \
	../common/stateset.h \
	../common/rgdvset.h \
	../common/alarmreset.h \
	../common/messageset.h \
	../common/sectortable.h \
	globalvar.h \
	svcapplication.h \
	svcmodule.h \
	datafile.h \
	viewer.h \
	algorithm.h \
	avtomatica.h \
	control.h \
	control_raf.h \
	modbus_packet.h \
	modbus_service.h \
	modbus_device.h \
	snmp_oids.h \
	snmp_service.h \
	snmp_device.h \
	canalasku.h \
	canalasku_defines.h \
	canalasku_struct.h \
	canalasku_codec.h \
	canalasku_data.h \
	canalasku_phase.h \
	canalasku_thread.h \
	coretemp.h \
	coretemp_thread.h \
	coretemp_service.h \
	dasd.h \
	dasd_interface.h \
	dasd_registers.h \
	dasd_tables.h \
	dasd_device.h \
	dasd_service.h \
	dasd_thread.h \
	drive.h \
	drive_struct.h \
	drive_thread.h \
	drive_service.h \
	drive_vector.h \
	coolers.h \
	coolers_struct.h \
	coolers_thread.h \
	coolers_service.h \
	coolers_vesper.h \
	poi.h \
	poi_struct.h \
	poi_thread.h \
	poi_service.h \
	powermeter.h \
	pos.h \
	pos_struct.h \
	pos_thread.h \
	pos_service.h \
	ups.h \
	ups_struct.h \
	ups_thread.h \
	ups_modbus_service.h \
	ups_modbus_pww_struct.h \
	ups_modbus_pww_device.h \
	ups_snmp_service.h \
	ups_snmp_apc_struct.h \
	ups_snmp_pww_struct.h \
	ups_snmp_apc_device.h \
	ups_snmp_pww_device.h \
	des.h \
	des_struct.h \
	des_thread.h \
	des_service.h \
	des_deif.h \
	des_deif_dg.h \
	des_deif_mains.h \
	voi.h \
	voi_struct.h \
	voi_thread.h \
	voi_service.h \
	vospd.h \
	vospd_struct.h \
	vospd_parser.h \
	vospd_thread.h \
	vospd_service.h \
	vrl.h \
	vrl_struct.h \
	vrl_thread.h \
	vrl_service.h

SOURCES += ../common/global.cpp \
	../common/application.cpp \
	../common/module.cpp \
	../common/tcpnetwork.cpp \
	../common/udpnetwork.cpp \
	../common/logger.cpp \
	../common/protocol.cpp \
	../common/parser.cpp \
	../common/connection.cpp \
	../common/xmlfile.cpp \
	../common/jsonfile.cpp \
	../common/stateset.cpp \
	../common/rgdvset.cpp \
	../common/alarmreset.cpp \
	../common/messageset.cpp \
	../common/sectortable.cpp \
	globalvar.cpp \
	main.cpp \
	svcapplication.cpp \
	svcmodule.cpp \
	datafile.cpp \
	viewer.cpp \
	algorithm.cpp \
	algorithm_drv.cpp \
	algorithm_elk.cpp \
	algorithm_poi.cpp \
	algorithm_prd.cpp \
	algorithm_prm.cpp \
	algorithm_proc.cpp \
	algorithm_sotr.cpp \
	algorithm_msg.cpp \
	algorithm_vrl.cpp \
	avtomatica.cpp \
	control.cpp \
	control_messages.cpp \
	control_commands.cpp \
	control_raf.cpp \
	modbus_packet.cpp \
	modbus_service.cpp \
	modbus_device.cpp \
	snmp_oids.cpp \
	snmp_service.cpp \
	snmp_device.cpp \
	canalasku.cpp \
	canalasku_state.cpp \
	canalasku_commands.cpp \
	canalasku_phase.cpp \
	canalasku_codec.cpp \
	canalasku_data.cpp \
	canalasku_thread.cpp \
	coretemp.cpp \
	coretemp_thread.cpp \
	coretemp_service.cpp \
	dasd.cpp \
	dasd_tables.cpp \
	dasd_device.cpp \
	dasd_service.cpp \
	dasd_thread.cpp \
	drive.cpp \
	drive_thread.cpp \
	drive_service.cpp \
	drive_vector.cpp \
	drive_algorithm.cpp \
	coolers.cpp \
	coolers_thread.cpp \
	coolers_service.cpp \
	coolers_vesper.cpp \
	coolers_algorithm.cpp \
	poi.cpp \
	poi_thread.cpp \
	poi_service.cpp \
	pos.cpp \
	pos_thread.cpp \
	pos_service.cpp \
	powermeter.cpp \
	ups.cpp \
	ups_thread.cpp \
	ups_modbus_service.cpp \
	ups_modbus_pww_device.cpp \
	ups_modbus_pww_algorithm.cpp \
	ups_snmp_service.cpp \
	ups_snmp_apc_device.cpp \
	ups_snmp_pww_device.cpp \
	ups_snmp_pww_algorithm.cpp \
	des.cpp \
	des_thread.cpp \
	des_service.cpp \
	des_deif_dg.cpp \
	des_deif_mains.cpp \
	des_algorithm.cpp \
	voi.cpp \
	voi_thread.cpp \
	voi_service.cpp \
	vospd.cpp \
	vospd_thread.cpp \
	vospd_service.cpp \
	vospd_parser.cpp \
	vospd_algorithm.cpp \
	vrl.cpp \
	vrl_thread.cpp \
	vrl_service.cpp \
	vrl_algorithm.cpp
