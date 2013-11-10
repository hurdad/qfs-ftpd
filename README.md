qfs-ftpd
========

C++ FTP Daemon for use with Quantcast File System (QFS)

FTP Daemon core using CFtpServer Library[http://sourceforge.net/projects/cftpserver/]

Gettting Started
========
### Requirements:

* qfs cluster installation
* qfs C++ client library

### Shared Library Requirements:
* libqfs_client
* libboost_regex (qfs dependency)
* libboost_program_options
* libconfig++ 1.4.9

Quick Start
========
```
git clone https://github.com/hurdad/qfs-ftpd.git
cd qfs-ftpd
sh autogen.sh
export CPPFLAGS="-I/path/to/qfs/include" 
export LDFLAGS="-L/path/to/qfs/lib"
export LD_LIBRARY_FLAGS=/path/to/qfs/lib
./configure
make
src/qfsconfig
```
Configuration
========

```
$ src/qfsftpd --help
Options:
  --help                                Options related to the program.
  -c [ --config ] arg (=config/R3.sample.cfg)
                                        Configuration File
```
### Sample configs:
  * **Default**     : configs/R3.sample.cfg
  * **Reed Solomon**: configs/RS.sample.cfg

```
$ cat configs/R3.sample.cfg
####################################################
# Sample config file for qfs-ftpd v0.1
# Replication Factor 3 //Default
#####################################################

QFS: //QFS Connection and Configuration
{        
    MetaServerHost 	= "127.0.0.1";
    MetaServerPort 	= 20000;
    MaxRetryPerOp 	= -1; 		//Not set
    RetryDelay 		= -1; 		//Not set
    DefaultIOTimeout = -1; 		//Not set
    WriteBufferSize = 4194304;	//4 MB Default
    SkipHoles		= false; 	//Default is false
    ReadBufferSize 	= 0; 		//Default is 0 = Optimal
    ReadAheadSize 	= -1; 		//Not Set
    Replication: 				//Normal Replication Factor = 3
    {
        NumReplicas = 3; 		//Default
    };
};

//FTP
ListeningIP 		= "127.0.0.1";  // FTP Listening Interface
ListeningPort 		= 2100; 		// By default, the FTP control port is 21
CheckPassDelay 		= 500; 			// milliseconds. Bruteforcing protection.
EnableFXP 			= true; 		// Server to Server transfers
MaxPasswordTries 	= 3;
NoLoginTimeout 		= 45; 			// Seconds
NoTransferTimeout 	= 90; 			// Seconds

//FTP Users
Users:(
	{
		Username : "admin";
		Password : "admin";
		HomePath : "/";
		Privs    : 63; // READFILE | WRITEFILE | DELETEFILE | LIST | CREATEDIR | DELETEDIR
	},
	{
		Username : "anonymous";
		Password : "";
		HomePath : "/";
		Privs    : 9; // READFILE | LIST 
	}
);

//TCP Port ranges for transfers
DataPortRange: 
{ 
	Start = 10000;
	Length = 900;
};

//TCP Socket Buffer
TransferSocketBufferSize = 65536; //64k

//Dir List Buffer Size
TransferBufferSize = 32768; //32kB

//Logging
LogDirectory 		= "logs";
EnableUserLogging 	= true; //Add & Removing Users
EnableClientLogging = true; //Client Operations
EnableServerLogging = true; //General Server 
```
Note
========
zlib compression feature CFtpServer has not been tested
