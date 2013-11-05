#ifndef MAIN_H_
#define MAIN_H_

struct config {

        std::string ListeningIP;
        unsigned short int ListeningPort;
        std::string QFSMetaserverHost;
        unsigned short int QFSMetaserverPort;
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
        std::string LogDirectory;
        bool EnableUserLogging;
        bool EnableClientLogging;
        bool EnableServerLogging;
};

#endif /* MAIN_H_ */
