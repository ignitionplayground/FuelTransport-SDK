#include "fuel_api.h"

#ifdef _WIN64
    HINSTANCE qCoreDynLib;
    HINSTANCE qNetworkDynLib;
    HINSTANCE FuelTransportDynLib;

    //Allocation
    __ft_alloc ft_alloc;

    //Configuration
    __ft_setTestInfo ft_setTestInfo;

    __ft_setVendorID ft_setVendorID;
    __ft_setProductID ft_setProductID;
    __ft_setVersion ft_setVersion;
    __ft_setApplicationID ft_setApplicationID;
    __ft_setSerialNo ft_setSerialNo;
    __ft_setID ft_setID;

    __ft_setName ft_setName;
    __ft_setTitle ft_setTitle;
    __ft_setGroup ft_setGroup;
    __ft_setDescription ft_setDescription;

    __ft_setTimeout ft_setTimeout;
    __ft_setEnableTCP ft_setEnableTCP;
    __ft_setMinimumCycleTime ft_setMinimumCycleTime;
    __ft_setCycleTime ft_setCycleTime;

    __ft_addProcessDataChannel ft_addProcessDataChannel;
    __ft_setSendingPolicy ft_setSendingPolicy;
    __ft_setSecondarySendingPolicy ft_setSecondarySendingPolicy;


    //Comissioning
    __ft_start ft_start;
    __ft_stop ft_stop;
    __ft_doWork ft_doWork;

    __ft_setProcessData ft_setProcessData;
    __ft_getProcessData ft_getProcessData;
    __ft_sendProcessData ft_sendProcessData;

    __ft_sendCommand ft_sendCommand;
    __ft_sendNotification ft_sendNotification;

    __ft_sendCacheRequest ft_sendCacheRequest;
    __ft_sendCacheData ft_sendCacheData;
    __ft_sendCachingStartedPacket ft_sendCachingStartedPacket;
    __ft_sendCachingProgressPacket ft_sendCachingProgressPacket;
    __ft_sendCachingFinishedPacket ft_sendCachingFinishedPacket;
    __ft_sendCachingAbortedPacket ft_sendCachingAbortedPacket;


    //Callback functions
    __ft_attachLogPrintFn ft_attachLogPrintFn;
    __ft_attachProcessDataChannelAddedFn ft_attachProcessDataChannelAddedFn;
    __ft_attachProcessDataReceivedFn ft_attachProcessDataReceivedFn;
    __ft_attachProcessDataRequestFn ft_attachProcessDataRequestFn;
    __ft_attachProcessDataChangedFn ft_attachProcessDataChangedFn;

    __ft_enableProcessDataChangedOnChannel ft_enableProcessDataChangedOnChannel;
    __ft_disableProcessDataChangedOnChannel ft_disableProcessDataChangedOnChannel;

    __ft_attachCommandReceivedFn ft_attachCommandReceivedFn;
    __ft_attachCacheRequestReceivedFn ft_attachCacheRequestReceivedFn;
    __ft_attachCacheDataReceivedFn ft_attachCacheDataReceivedFn;
    __ft_attachCachingStartedFn ft_attachCachingStartedFn;
    __ft_attachCachingProgressFn ft_attachCachingProgressFn;
    __ft_attachCachingFinishedFn ft_attachCachingFinishedFn;
    __ft_attachCachingAbortedFn ft_attachCachingAbortedFn;
    __ft_attachNotificationReceivedFn ft_attachNotificationReceivedFn;
    __ft_attachConnectionEstablishedFn ft_attachConnectionEstablishedFn;
    __ft_attachWatchdogWarningFn ft_attachWatchdogWarningFn;
    __ft_attachDisconnectedFn ft_attachDisconnectedFn;

    //Getters
    __ft_getSyncedTime ft_getSyncedTime;
    __ft_getStatus ft_getStatus;
    __ft_getTestInt ft_getTestInt;

    //Deallocation
    __ft_dealloc ft_dealloc;

    unsigned long ft_load(){

        //Load Modules
        qCoreDynLib = LoadLibrary(TEXT("Qt5Core.dll"));
		if (qCoreDynLib == nullptr) {
            return GetLastError();
		}
        qNetworkDynLib = LoadLibrary(TEXT("Qt5Network.dll"));
		if (qNetworkDynLib == nullptr) {
            return GetLastError();
		}
        FuelTransportDynLib = LoadLibrary(TEXT("FuelTransportSharedLib.dll"));
		if (FuelTransportDynLib == nullptr) {
            return GetLastError();
		}

        //Allocation
        ft_alloc = reinterpret_cast<__ft_alloc>(GetProcAddress(FuelTransportDynLib, "ft_alloc"));
        if (!ft_alloc) {
            return GetLastError();
        }

        //Configuration functions
        ft_setTestInfo = reinterpret_cast<__ft_setTestInfo>(GetProcAddress(FuelTransportDynLib, "ft_setTestInfo"));
        if (!ft_setTestInfo) {
            return GetLastError();
        }

        ft_setVendorID = reinterpret_cast<__ft_setVendorID>(GetProcAddress(FuelTransportDynLib, "ft_setVendorID"));
        if (!ft_setVendorID) {
            return GetLastError();
        }

        ft_setProductID = reinterpret_cast<__ft_setProductID>(GetProcAddress(FuelTransportDynLib, "ft_setProductID"));
        if (!ft_setProductID) {
            return GetLastError();
        }

        ft_setVersion = reinterpret_cast<__ft_setVersion>(GetProcAddress(FuelTransportDynLib, "ft_setVersion"));
        if (!ft_setVersion) {
            return GetLastError();
        }

        ft_setApplicationID = reinterpret_cast<__ft_setApplicationID>(GetProcAddress(FuelTransportDynLib, "ft_setApplicationID"));
        if (!ft_setApplicationID) {
            return GetLastError();
        }

        ft_setSerialNo = reinterpret_cast<__ft_setSerialNo>(GetProcAddress(FuelTransportDynLib, "ft_setSerialNo"));
        if (!ft_setSerialNo) {
            return GetLastError();
        }

        ft_setID = reinterpret_cast<__ft_setID>(GetProcAddress(FuelTransportDynLib, "ft_setID"));
        if (!ft_setID) {
            return GetLastError();
        }

        ft_setName = reinterpret_cast<__ft_setName>(GetProcAddress(FuelTransportDynLib, "ft_setName"));
        if (!ft_setName) {
            return GetLastError();
        }

        ft_setTitle = reinterpret_cast<__ft_setTitle>(GetProcAddress(FuelTransportDynLib, "ft_setTitle"));
        if (!ft_setTitle) {
            return GetLastError();
        }

        ft_setGroup = reinterpret_cast<__ft_setGroup>(GetProcAddress(FuelTransportDynLib, "ft_setGroup"));
        if (!ft_setGroup) {
            return GetLastError();
        }

        ft_setDescription = reinterpret_cast<__ft_setDescription>(GetProcAddress(FuelTransportDynLib, "ft_setDescription"));
        if (!ft_setDescription) {
            return GetLastError();
        }

        ft_setTimeout = reinterpret_cast<__ft_setTimeout>(GetProcAddress(FuelTransportDynLib, "ft_setTimeout"));
        if (!ft_setTimeout) {
            return GetLastError();
        }

        ft_setEnableTCP = reinterpret_cast<__ft_setEnableTCP>(GetProcAddress(FuelTransportDynLib, "ft_setEnableTCP"));
        if (!ft_setEnableTCP) {
            return GetLastError();
        }

        ft_setMinimumCycleTime = reinterpret_cast<__ft_setMinimumCycleTime>(GetProcAddress(FuelTransportDynLib, "ft_setMinimumCycleTime"));
        if (!ft_setMinimumCycleTime) {
            return GetLastError();
        }

        ft_setCycleTime = reinterpret_cast<__ft_setCycleTime>(GetProcAddress(FuelTransportDynLib, "ft_setCycleTime"));
        if (!ft_setCycleTime) {
            return GetLastError();
        }

        ft_addProcessDataChannel = reinterpret_cast<__ft_addProcessDataChannel>(GetProcAddress(FuelTransportDynLib, "ft_addProcessDataChannel"));
        if (!ft_addProcessDataChannel) {
            return GetLastError();
        }

        ft_setSendingPolicy = reinterpret_cast<__ft_setSendingPolicy>(GetProcAddress(FuelTransportDynLib, "ft_setSendingPolicy"));
        if (!ft_setSendingPolicy) {
            return GetLastError();
        }

        ft_setSecondarySendingPolicy = reinterpret_cast<__ft_setSecondarySendingPolicy>(GetProcAddress(FuelTransportDynLib, "ft_setSecondarySendingPolicy"));
        if (!ft_setSecondarySendingPolicy) {
            return GetLastError();
        }


        //Comissioning
        ft_start = reinterpret_cast<__ft_start>(GetProcAddress(FuelTransportDynLib, "ft_start"));
        if (!ft_start) {
            return GetLastError();
        }

        ft_stop = reinterpret_cast<__ft_stop>(GetProcAddress(FuelTransportDynLib, "ft_stop"));
        if (!ft_stop) {
            return GetLastError();
        }

        ft_doWork = reinterpret_cast<__ft_doWork>(GetProcAddress(FuelTransportDynLib, "ft_doWork"));
        if (!ft_doWork) {
            return GetLastError();
        }

        ft_setProcessData = reinterpret_cast<__ft_setProcessData>(GetProcAddress(FuelTransportDynLib, "ft_setProcessData"));
        if (!ft_setProcessData) {
            return GetLastError();
        }

        ft_getProcessData = reinterpret_cast<__ft_getProcessData>(GetProcAddress(FuelTransportDynLib, "ft_getProcessData"));
        if (!ft_getProcessData) {
            return GetLastError();
        }

        ft_sendProcessData = reinterpret_cast<__ft_sendProcessData>(GetProcAddress(FuelTransportDynLib, "ft_sendProcessData"));
        if (!ft_sendProcessData) {
            return GetLastError();
        }

        ft_sendCommand = reinterpret_cast<__ft_sendCommand>(GetProcAddress(FuelTransportDynLib, "ft_sendCommand"));
        if (!ft_sendCommand) {
            return GetLastError();
        }

        ft_sendNotification = reinterpret_cast<__ft_sendNotification>(GetProcAddress(FuelTransportDynLib, "ft_sendNotification"));
        if (!ft_sendNotification) {
            return GetLastError();
        }

        ft_sendCacheRequest = reinterpret_cast<__ft_sendCacheRequest>(GetProcAddress(FuelTransportDynLib, "ft_sendCacheRequest"));
        if (!ft_sendCacheRequest) {
            return GetLastError();
        }

        ft_sendCacheData = reinterpret_cast<__ft_sendCacheData>(GetProcAddress(FuelTransportDynLib, "ft_sendCacheData"));
        if (!ft_sendCacheData) {
            return GetLastError();
        }

        ft_sendCachingStartedPacket = reinterpret_cast<__ft_sendCachingStartedPacket>(GetProcAddress(FuelTransportDynLib, "ft_sendCachingStartedPacket"));
        if (!ft_sendCachingStartedPacket) {
            return GetLastError();
        }

        ft_sendCachingProgressPacket = reinterpret_cast<__ft_sendCachingProgressPacket>(GetProcAddress(FuelTransportDynLib, "ft_sendCachingProgressPacket"));
        if (!ft_sendCachingProgressPacket) {
            return GetLastError();
        }

        ft_sendCachingFinishedPacket = reinterpret_cast<__ft_sendCachingFinishedPacket>(GetProcAddress(FuelTransportDynLib, "ft_sendCachingFinishedPacket"));
        if (!ft_sendCachingFinishedPacket) {
            return GetLastError();
        }

        ft_sendCachingAbortedPacket = reinterpret_cast<__ft_sendCachingAbortedPacket>(GetProcAddress(FuelTransportDynLib, "ft_sendCachingAbortedPacket"));
        if (!ft_sendCachingAbortedPacket) {
            return GetLastError();
        }

        //Callback function pointers
        ft_attachLogPrintFn = reinterpret_cast<__ft_attachLogPrintFn>(GetProcAddress(FuelTransportDynLib, "ft_attachLogPrintFn"));
        if (!ft_attachLogPrintFn) {
            return GetLastError();
        }


        ft_attachProcessDataChannelAddedFn = reinterpret_cast<__ft_attachProcessDataChannelAddedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachProcessDataChannelAddedFn"));
        if (!ft_attachProcessDataChannelAddedFn) {
            return GetLastError();
        }

        ft_attachProcessDataReceivedFn = reinterpret_cast<__ft_attachProcessDataReceivedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachProcessDataReceivedFn"));
        if (!ft_attachProcessDataReceivedFn) {
            return GetLastError();
        }

        ft_attachProcessDataRequestFn = reinterpret_cast<__ft_attachProcessDataRequestFn>(GetProcAddress(FuelTransportDynLib, "ft_attachProcessDataRequestFn"));
        if (!ft_attachProcessDataRequestFn) {
            return GetLastError();
        }

        ft_attachProcessDataChangedFn = reinterpret_cast<__ft_attachProcessDataChangedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachProcessDataChangedFn"));
        if (!ft_attachProcessDataChangedFn) {
            return GetLastError();
        }

        ft_enableProcessDataChangedOnChannel = reinterpret_cast<__ft_enableProcessDataChangedOnChannel>(GetProcAddress(FuelTransportDynLib, "ft_enableProcessDataChangedOnChannel"));
        if (!ft_enableProcessDataChangedOnChannel) {
            return GetLastError();
        }

        ft_disableProcessDataChangedOnChannel = reinterpret_cast<__ft_disableProcessDataChangedOnChannel>(GetProcAddress(FuelTransportDynLib, "ft_disableProcessDataChangedOnChannel"));
        if (!ft_disableProcessDataChangedOnChannel) {
            return GetLastError();
        }


        ft_attachCommandReceivedFn = reinterpret_cast<__ft_attachCommandReceivedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachCommandReceivedFn"));
        if (!ft_attachCommandReceivedFn) {
            return GetLastError();
        }

        ft_attachNotificationReceivedFn = reinterpret_cast<__ft_attachNotificationReceivedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachNotificationReceivedFn"));
        if (!ft_attachNotificationReceivedFn) {
            return GetLastError();
        }


        ft_attachCacheRequestReceivedFn = reinterpret_cast<__ft_attachCacheRequestReceivedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachCacheRequestReceivedFn"));
        if (!ft_attachCacheRequestReceivedFn) {
            return GetLastError();
        }

        ft_attachCacheDataReceivedFn = reinterpret_cast<__ft_attachCacheDataReceivedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachCacheDataReceivedFn"));
        if (!ft_attachCacheDataReceivedFn) {
            return GetLastError();
        }

        ft_attachCachingStartedFn = reinterpret_cast<__ft_attachCachingStartedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachCachingStartedFn"));
        if (!ft_attachCachingStartedFn) {
            return GetLastError();
        }

        ft_attachCachingProgressFn = reinterpret_cast<__ft_attachCachingProgressFn>(GetProcAddress(FuelTransportDynLib, "ft_attachCachingProgressFn"));
        if (!ft_attachCachingProgressFn) {
            return GetLastError();
        }

        ft_attachCachingFinishedFn = reinterpret_cast<__ft_attachCachingFinishedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachCachingFinishedFn"));
        if (!ft_attachCachingFinishedFn) {
            return GetLastError();
        }

        ft_attachCachingAbortedFn = reinterpret_cast<__ft_attachCachingAbortedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachCachingAbortedFn"));
        if (!ft_attachCachingAbortedFn) {
            return GetLastError();
        }

        ft_attachConnectionEstablishedFn = reinterpret_cast<__ft_attachConnectionEstablishedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachConnectionEstablishedFn"));
        if (!ft_attachConnectionEstablishedFn) {
            return GetLastError();
        }

        ft_attachWatchdogWarningFn = reinterpret_cast<__ft_attachWatchdogWarningFn>(GetProcAddress(FuelTransportDynLib, "ft_attachWatchdogWarningFn"));
        if (!ft_attachWatchdogWarningFn) {
            return GetLastError();
        }

        ft_attachDisconnectedFn = reinterpret_cast<__ft_attachDisconnectedFn>(GetProcAddress(FuelTransportDynLib, "ft_attachDisconnectedFn"));
        if (!ft_attachDisconnectedFn) {
            return GetLastError();
        }


        //Getters
        ft_getSyncedTime = reinterpret_cast<__ft_getSyncedTime>(GetProcAddress(FuelTransportDynLib, "ft_getSyncedTime"));
        if (!ft_getSyncedTime) {
            return GetLastError();
        }

        ft_getStatus = reinterpret_cast<__ft_getStatus>(GetProcAddress(FuelTransportDynLib, "ft_getStatus"));
        if (!ft_getStatus) {
            return GetLastError();
        }

        ft_getTestInt = reinterpret_cast<__ft_getTestInt>(GetProcAddress(FuelTransportDynLib, "ft_getTestInt"));
        if (!ft_getTestInt) {
            return GetLastError();
        }


        //Deallocation
        ft_dealloc = reinterpret_cast<__ft_dealloc>(GetProcAddress(FuelTransportDynLib, "ft_dealloc"));
        if (!ft_dealloc) {
            return GetLastError();
        }

        return 0;
    }

    unsigned long ft_unload(void * obj) {
        if (obj != nullptr){
            ft_stop(obj);
            ft_dealloc(obj);
        }

        if(qCoreDynLib != nullptr)
            FreeLibrary(qCoreDynLib);

        if(qNetworkDynLib != nullptr)
            FreeLibrary(qNetworkDynLib);

        if(FuelTransportDynLib != nullptr)
            FreeLibrary(FuelTransportDynLib);

        return 0;
	}

#endif

#ifdef __MACH__
#endif

#ifdef __linux__
#endif
