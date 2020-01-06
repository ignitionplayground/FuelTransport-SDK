#pragma once
#include "fuel_functionprototypes.h"

#define FT_ERROR -2
#define FT_WARNING -1
#define FT_DISCONNECTED 0
#define FT_CONNECTING 1
#define FT_CONNECTED 2

#ifdef _WIN64
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <tchar.h>
    #define __FPTRTYPE __stdcall*
    #define __DLHANDLE HINSTANCE
#endif

#if defined(__linux__) || defined(__APPLE__)
    #define __FPTRTYPE
    #define __DLHANDLE void *
#endif


    //Allocation
    typedef void*(__FPTRTYPE __ft_alloc)();

    //Configuration
    typedef void(__FPTRTYPE __ft_setTestInfo)(void * obj);

    typedef void(__FPTRTYPE __ft_setVendorID)(void * obj, unsigned int vendorid);
    typedef void(__FPTRTYPE __ft_setProductID)(void * obj, unsigned int productid);
    typedef void(__FPTRTYPE __ft_setVersion)(void * obj, unsigned int version);
    typedef void(__FPTRTYPE __ft_setApplicationID)(void * obj, unsigned long long applicationid);
    typedef void(__FPTRTYPE __ft_setSerialNo)(void * obj, unsigned long long serialno);
    typedef void(__FPTRTYPE __ft_setID)(void * obj,
                                       unsigned int vendorid,
                                       unsigned int productid,
                                       unsigned int version,
                                       unsigned long long applicationid,
                                       unsigned long long serialno);

    typedef void(__FPTRTYPE __ft_setName)(void * obj, char * name);
    typedef void(__FPTRTYPE __ft_setTitle)(void * obj, char * title);
    typedef void(__FPTRTYPE __ft_setGroup)(void * obj, char * group);
    typedef void(__FPTRTYPE __ft_setDescription)(void * obj, char * name, char * title, char * group);

    typedef void(__FPTRTYPE __ft_setTimeout)(void * obj, float warningTimeout, float criticalTimeout);
    typedef void(__FPTRTYPE __ft_setEnableTCP)(void * obj);
    typedef void(__FPTRTYPE __ft_setMinimumCycleTime)(void * obj, float cycleTime);
    typedef void(__FPTRTYPE __ft_setCycleTime)(void * obj, float cycleTime);

    typedef void(__FPTRTYPE __ft_addProcessDataChannel)(void * obj, unsigned short index, unsigned short dataLength);
    typedef void(__FPTRTYPE __ft_setSendingPolicy)(void * obj, unsigned short index, bool udp, bool tcp, bool sendOnChange, float sendInterval);
    typedef void(__FPTRTYPE __ft_setSecondarySendingPolicy)(void * obj, unsigned short index, bool udp, bool tcp, bool sendOnChange, float sendInterval);


    //Comissioning
    typedef void(__FPTRTYPE __ft_start)(void * obj);
    typedef void(__FPTRTYPE __ft_stop)(void * obj);
    typedef void(__FPTRTYPE __ft_doWork)(void * obj);

    typedef void(__FPTRTYPE __ft_setProcessData)(void * obj, unsigned short index, void * data);
    typedef void(__FPTRTYPE __ft_getProcessData)(void * obj, unsigned short index, void * data);
    typedef void(__FPTRTYPE __ft_sendProcessData)(void * obj, unsigned short index);

    typedef void (__FPTRTYPE __ft_sendCommand)(void * obj, unsigned short code, unsigned short subindex, void * data, unsigned short datalength, double targetTime);
    typedef void (__FPTRTYPE __ft_sendNotification)(void * obj, unsigned char level, unsigned short code, unsigned short subindex, char * msg, unsigned short msglength);
    typedef void (__FPTRTYPE __ft_sendCacheRequest)(void * obj, float startTime, float timeRange, float frequency, unsigned short subindex, unsigned long long maxSampleCount);
    typedef void (__FPTRTYPE __ft_sendCacheData)(void * obj, float time, float progress, void * data, unsigned short datalength, unsigned short subindex);
    typedef void (__FPTRTYPE __ft_sendCachingStartedPacket)(void * obj, unsigned long long sampleCount, float startTime, float timeRange, float timeStep);
    typedef void (__FPTRTYPE __ft_sendCachingProgressPacket)(void * obj, unsigned long long samplesSent, unsigned long long totalSamples, float percent);
    typedef void (__FPTRTYPE __ft_sendCachingFinishedPacket)(void * obj, unsigned long long totalSampleCount, double elapsedSeconds);
    typedef void (__FPTRTYPE __ft_sendCachingAbortedPacket)(void * obj, int abortCode, char *message, unsigned short msglength);


    //Callback functions
    typedef void (__FPTRTYPE __ft_attachLogPrintFn)(fnLogPrint_t fptr);
    typedef void (__FPTRTYPE __ft_attachProcessDataChannelAddedFn)(void * obj, fnProcessDataChannelAdded_t fptr);
    typedef void (__FPTRTYPE __ft_attachProcessDataReceivedFn)(void * obj, fnProcessDataReceived_t fptr);
    typedef void (__FPTRTYPE __ft_attachProcessDataRequestFn)(void * obj, fnProcessDataRequest_t fptr);
    typedef void (__FPTRTYPE __ft_attachProcessDataChangedFn)(void * obj, unsigned short channel, fnProcessDataChanged_t fptr);

    typedef void (__FPTRTYPE __ft_enableProcessDataChangedOnChannel)(void * obj, unsigned short channel);
    typedef void (__FPTRTYPE __ft_disableProcessDataChangedOnChannel)(void * obj, unsigned short channel);

    typedef void (__FPTRTYPE __ft_attachCommandReceivedFn)(void * obj, fnCommandReceived_t fptr);
    typedef void (__FPTRTYPE __ft_attachNotificationReceivedFn)(void * obj, fnNotificationReceived_t fptr);
    typedef void (__FPTRTYPE __ft_attachCacheRequestReceivedFn)(void * obj, fnCacheRequestReceived_t fptr);
    typedef void (__FPTRTYPE __ft_attachCacheDataReceivedFn)(void * obj, fnCacheDataReceived_t fptr);
    typedef void (__FPTRTYPE __ft_attachCachingStartedFn)(void * obj, fnCachingStarted_t fptr);
    typedef void (__FPTRTYPE __ft_attachCachingProgressFn)(void * obj, fnCachingProgress_t fptr);
    typedef void (__FPTRTYPE __ft_attachCachingFinishedFn)(void * obj, fnCachingFinished_t fptr);
    typedef void (__FPTRTYPE __ft_attachCachingAbortedFn)(void * obj, fnCachingAborted_t fptr);
    typedef void (__FPTRTYPE __ft_attachConnectionEstablishedFn)(void * obj, fnConnectionEstablished_t fptr);
    typedef void (__FPTRTYPE __ft_attachWatchdogWarningFn)(void * obj, fnWatchdogWarning_t fptr);
    typedef void (__FPTRTYPE __ft_attachDisconnectedFn)(void * obj, fnDisconnected_t fptr);

    //Getters
    typedef double (__FPTRTYPE __ft_getSyncedTime)(void * obj);
    typedef int (__FPTRTYPE __ft_getStatus)(void * obj);
    typedef int(__FPTRTYPE __ft_getTestInt)();

    //Deallocation
    typedef void(__FPTRTYPE __ft_dealloc)(void * obj);

    extern __DLHANDLE qCoreDynLib;
    extern __DLHANDLE qNetworkDynLib;
    extern __DLHANDLE FuelTransportDynLib;

    //Allocation
    extern __ft_alloc ft_alloc;

    //Configuration
    extern __ft_setTestInfo ft_setTestInfo;

    extern __ft_setVendorID ft_setVendorID;
    extern __ft_setProductID ft_setProductID;
    extern __ft_setVersion ft_setVersion;
    extern __ft_setApplicationID ft_setApplicationID;
    extern __ft_setSerialNo ft_setSerialNo;
    extern __ft_setID ft_setID;

    extern __ft_setName ft_setName;
    extern __ft_setTitle ft_setTitle;
    extern __ft_setGroup ft_setGroup;
    extern __ft_setDescription ft_setDescription;

    extern __ft_setTimeout ft_setTimeout;
    extern __ft_setEnableTCP ft_setEnableTCP;
    extern __ft_setMinimumCycleTime ft_setMinimumCycleTime;
    extern __ft_setCycleTime ft_setCycleTime;

    extern __ft_addProcessDataChannel ft_addProcessDataChannel;
    extern __ft_setSendingPolicy ft_setSendingPolicy;
    extern __ft_setSecondarySendingPolicy ft_setSecondarySendingPolicy;


    //Comissioning
    extern __ft_start ft_start;
    extern __ft_stop ft_stop;
    extern __ft_doWork ft_doWork;

    extern __ft_setProcessData ft_setProcessData;
    extern __ft_getProcessData ft_getProcessData;
    extern __ft_sendProcessData ft_sendProcessData;

    extern __ft_sendCommand ft_sendCommand;
    extern __ft_sendNotification ft_sendNotification;

    extern __ft_sendCacheRequest ft_sendCacheRequest;
    extern __ft_sendCacheData ft_sendCacheData;
    extern __ft_sendCachingStartedPacket ft_sendCachingStartedPacket;
    extern __ft_sendCachingProgressPacket ft_sendCachingProgressPacket;
    extern __ft_sendCachingFinishedPacket ft_sendCachingFinishedPacket;
    extern __ft_sendCachingAbortedPacket ft_sendCachingAbortedPacket;

    //Callback functions
    extern __ft_attachLogPrintFn ft_attachLogPrintFn;
    extern __ft_attachProcessDataChannelAddedFn ft_attachProcessDataChannelAddedFn;
    extern __ft_attachProcessDataReceivedFn ft_attachProcessDataReceivedFn;
    extern __ft_attachProcessDataRequestFn ft_attachProcessDataRequestFn;
    extern __ft_attachProcessDataChangedFn ft_attachProcessDataChangedFn;
    extern __ft_enableProcessDataChangedOnChannel ft_enableProcessDataChangedOnChannel;
    extern __ft_disableProcessDataChangedOnChannel ft_disableProcessDataChangedOnChannel;
    extern __ft_attachCommandReceivedFn ft_attachCommandReceivedFn;
    extern __ft_attachCacheRequestReceivedFn ft_attachCacheRequestReceivedFn;
    extern __ft_attachCacheDataReceivedFn ft_attachCacheDataReceivedFn;
    extern __ft_attachCachingStartedFn ft_attachCachingStartedFn;
    extern __ft_attachCachingProgressFn ft_attachCachingProgressFn;
    extern __ft_attachCachingFinishedFn ft_attachCachingFinishedFn;
    extern __ft_attachCachingAbortedFn ft_attachCachingAbortedFn;
    extern __ft_attachNotificationReceivedFn ft_attachNotificationReceivedFn;
    extern __ft_attachConnectionEstablishedFn ft_attachConnectionEstablishedFn;
    extern __ft_attachWatchdogWarningFn ft_attachWatchdogWarningFn;
    extern __ft_attachDisconnectedFn ft_attachDisconnectedFn;

    //Getters
    extern __ft_getSyncedTime ft_getSyncedTime;
    extern __ft_getStatus ft_getStatus;
    extern __ft_getTestInt ft_getTestInt;

    //Deallocation
    extern __ft_dealloc ft_dealloc;
