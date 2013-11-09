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

	server.QFSMetaServerHost = "127.0.0.1"; //QFS Cluster Metaserver Hostname
	server.QFSMetaServerPort = 20000; // QFS Cluster Meteaserver Port
	server.QFSRootPath = "/";  //QFS FTP Root Path
	server.QFSMaxRetryPerOp = -1; //count
	server.QFSRetryDelay = -1; //nsec
	server.QFSDefaultIOTimeout = -1; //nsec
	server.QFSReplicationStripeSize = 0;
	server.QFSReplicationNumStripes = 0;
	server.QFSReplicationNumRecoveryStripes = 0;
	server.QFSReplicationNumReplicas = 3;
	server.QFSSkipHoles = false; //Default False
	server.QFSReadBufferSize = 0; //Optimal
	server.QFSWriteBufferSize = 4 << 20; //4Mb Default
	server.QFSReadAheadBufferSize = -1; //Not Set

	server.CheckPassDelay = 500; // milliseconds. Bruteforcing protection.
	server.DataPortRange.usStart = 100; // TCP Ports [100;999].
	server.DataPortRange.usLen = 900;
	server.EnableFXP = true;
	server.MaxPasswordTries = 3;
	server.NoLoginTimeout = 0; // No timeout.
	server.NoTransferTimeout = 0; // No timeout.
	server.TransferSocketBufferSize = 64 * 1024; //64kB
	server.TransferBufferSize = 32 * 1024; //32kB
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
		std::cerr << "Error while reading config file: " << configFile << std::endl;
		exit (EXIT_FAILURE);
	} catch (const ParseException &pex) {
		std::cerr << "Configuration parse error at " << pex.getFile() << ":" << pex.getLine()
				<< " - " << pex.getError() << std::endl;
		exit (EXIT_FAILURE);
	}

	//
	// Parse Config
	//

	//QFS
	cfg.lookupValue("QFS.MetaServerHost", server.QFSMetaServerHost);
	int QFSMetaServerPort = server.QFSMetaServerPort;
	cfg.lookupValue("QFS.MetaServerPort", QFSMetaServerPort);
	server.QFSMetaServerPort = QFSMetaServerPort;
	cfg.lookupValue("QFS.RootPath", server.QFSRootPath);

	cfg.lookupValue("QFS.MaxRetryPerOp", server.QFSMaxRetryPerOp);
	cfg.lookupValue("QFS.RetryDelay", server.QFSRetryDelay);
	cfg.lookupValue("QFS.QFSDefaultIOTimeout", server.QFSDefaultIOTimeout);

	cfg.lookupValue("QFS.Replication.StripeSize", server.QFSReplicationStripeSize);
	cfg.lookupValue("QFS.Replication.NumStripes", server.QFSReplicationNumStripes);
	cfg.lookupValue("QFS.Replication.NumRecoveryStripes", server.QFSReplicationNumRecoveryStripes);
	cfg.lookupValue("QFS.Replication.NumReplicas", server.QFSReplicationNumReplicas);

	cfg.lookupValue("QFS.SkipHoles", server.QFSSkipHoles);
	cfg.lookupValue("QFS.ReadBufferSize", server.QFSReadBufferSize);
	cfg.lookupValue("QFS.WriteBufferSize", server.QFSWriteBufferSize);
	cfg.lookupValue("QFS.ReadAheadBufferSize", server.QFSReadAheadBufferSize);

	//FTP
	cfg.lookupValue("ListeningIP", server.ListeningIP);
	int ListeningPort = server.ListeningPort;
	cfg.lookupValue("ListeningPort", ListeningPort);
	server.ListeningPort = ListeningPort;

	int Start = server.DataPortRange.usStart;
	int Len = server.DataPortRange.usLen;
	cfg.lookupValue("DataPortRange.Start", Start);
	cfg.lookupValue("DataPortRange.Len", Len);
	server.DataPortRange.usStart = Start;
	server.DataPortRange.usLen = Len;

	cfg.lookupValue("EnableFXP", server.EnableFXP);
	cfg.lookupValue("MaxPasswordTries", server.MaxPasswordTries);

	int NoLoginTimeout = server.NoLoginTimeout;
	int NoTransferTimeout = server.NoTransferTimeout;
	cfg.lookupValue("NoLoginTimeout", NoLoginTimeout);
	cfg.lookupValue("NoTransferTimeout", NoTransferTimeout);
	server.NoLoginTimeout = NoLoginTimeout;
	server.NoTransferTimeout = NoTransferTimeout;

	cfg.lookupValue("TransferBufferSize", server.TransferBufferSize);
	cfg.lookupValue("TransferSocketBufferSize", server.TransferSocketBufferSize);

	cfg.lookupValue("LogDirectory", server.LogDirectory);
	cfg.lookupValue("EnableUserLogging", server.EnableUserLogging);
	cfg.lookupValue("EnableClientLogging", server.EnableClientLogging);
	cfg.lookupValue("EnableServerLogging", server.EnableServerLogging);

}

}
#endif /* CONFIG_HPP_ */
