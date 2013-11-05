#ifndef CONFIG_HPP_
#define CONFIG_HPP_
#include "libconfig.h++"
#include <iostream>
#include <string>

namespace ftpd_server {

using namespace std;
using namespace libconfig;


config server;

void InitServerConfig() {

	server.ListeningIP = "0.0.0.0"; // FTP Listening Interface
	server.ListeningPort = 2100; // By default, the FTP control port is 21
	server.QFSMetaserverHost = "localhost"; //QFS Cluster's Metaserver Hostname
	server.QFSMetaserverPort = 20000; // QFS Cluster Meteaserver Port
	server.CheckPassDelay = 500; // milliseconds. Bruteforcing protection.
	server.DataPortRange.usStart = 100; // TCP Ports [100;999].
	server.DataPortRange.usLen = 900;
	server.EnableFXP = true;
	server.MaxPasswordTries = 3;
	server.NoLoginTimeout = 0; // No timeout.
	server.NoTransferTimeout = 0; // No timeout.
	server.TransferBufferSize = 32 * 1024;
	server.TransferSocketBufferSize = 64 * 1024;
	server.LogDirectory = "logs";
	server.EnableUserLogging = false;
	server.EnableClientLogging = true;
	server.EnableServerLogging = true;

}

void LoadServerConfig(const char * configFile) {
	Config cfg;

	// Read the file. If there is an error, report it and exit.
	try {
		cfg.readFile(configFile);
	} catch (const FileIOException &fioex) {
		std::cerr << "Error while reading config file: " << configFile
				<< std::endl;
		exit (EXIT_FAILURE);
	} catch (const ParseException &pex) {
		std::cerr << "Configuration parse error at " << pex.getFile() << ":"
				<< pex.getLine() << " - " << pex.getError() << std::endl;
		exit (EXIT_FAILURE);
	}

	//
	// Parse Config
	//
	string ListeningIP = server.ListeningIP;
	cfg.lookupValue("ListeningIP", ListeningIP);
	server.ListeningIP = ListeningIP;
	int ListeningPort = server.ListeningPort;
	cfg.lookupValue("ListeningPort", ListeningPort);
	server.ListeningPort = ListeningPort;

	string QFSMetaserverHost = server.QFSMetaserverHost;
	cfg.lookupValue("QFSMetaserverHost", QFSMetaserverHost);
	server.QFSMetaserverHost = QFSMetaserverHost;
	int QFSMetaserverPort = server.QFSMetaserverPort;
	cfg.lookupValue("QFSMetaserverPort", QFSMetaserverPort);
	server.QFSMetaserverPort = QFSMetaserverPort;

	int Start = server.DataPortRange.usStart;
	int Len = server.DataPortRange.usLen;
	cfg.lookupValue("DataPortRange.Start", Start);
	cfg.lookupValue("DataPortRange.Len", Len);
	server.DataPortRange.usStart = Start;
	server.DataPortRange.usLen = Len;

	bool EnableFXP = server.EnableFXP;
	cfg.lookupValue("EnableFXP", EnableFXP);
	server.EnableFXP = EnableFXP;

	unsigned int MaxPasswordTries = server.MaxPasswordTries;
	cfg.lookupValue("MaxPasswordTries", MaxPasswordTries);
	server.MaxPasswordTries = MaxPasswordTries;

	int NoLoginTimeout = server.NoLoginTimeout;
	int NoTransferTimeout = server.NoTransferTimeout;
	cfg.lookupValue("NoLoginTimeout", NoLoginTimeout);
	cfg.lookupValue("NoTransferTimeout", NoTransferTimeout);
	server.NoLoginTimeout = NoLoginTimeout;
	server.NoTransferTimeout = NoTransferTimeout;

	cfg.lookupValue("TransferBufferSize", server.TransferBufferSize);
	cfg.lookupValue("TransferSocketBufferSize",
			server.TransferSocketBufferSize);

	cfg.lookupValue("LogDirectory", server.LogDirectory);
	cfg.lookupValue("EnableUserLogging", server.EnableUserLogging);
	cfg.lookupValue("EnableClientLogging", server.EnableClientLogging);
	cfg.lookupValue("EnableServerLogging", server.EnableServerLogging);

}

}
#endif /* CONFIG_HPP_ */
