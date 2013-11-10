#ifndef MAIN_H_
#define MAIN_H_

struct User {
	std::string Username;
	std::string Password;
	std::string HomePath;
	unsigned char Privs;
};

struct config {

	std::string ListeningIP;
	unsigned short int ListeningPort;
	struct {
		unsigned short int usLen, usStart;
	} DataPortRange;

	unsigned int MaxPasswordTries;
	unsigned int CheckPassDelay;
	unsigned long int NoTransferTimeout, NoLoginTimeout;
	unsigned int TransferBufferSize, TransferSocketBufferSize;

#ifdef CFTPSERVER_ENABLE_ZLIB
	bool EnableZlib;
#endif

	bool EnableFXP;

	std::string QFSMetaServerHost;
	int QFSMetaServerPort;
	std::string QFSRootPath;
	int QFSMaxRetryPerOp;
	int QFSRetryDelay;
	int QFSDefaultIOTimeout;
	int QFSReplicationStripeSize;
	int QFSReplicationNumStripes;
	int QFSReplicationNumRecoveryStripes;
	int QFSReplicationNumReplicas;
	bool QFSSkipHoles;
	int QFSReadBufferSize;
	int QFSWriteBufferSize;
	int QFSReadAheadBufferSize;

	std::vector<User> Users;

	std::string LogDirectory;
	bool EnableUserLogging;
	bool EnableClientLogging;
	bool EnableServerLogging;

};

#endif /* MAIN_H_ */
