from ctypes import *
import os
self_path = os.path.dirname(__file__)
import platform

FT_ERROR = -2
FT_WARNING = -1
FT_DISCONNECTED = 0
FT_CONNECTING = 1
FT_CONNECTED = 2

FT_NONE = 0,
FT_LOWLEVEL = 1,
FT_DEBUG = 10,
FT_INFO = 50,
FT_WARNING = 100,
FT_ERR = 150,
FT_CRITICAL = 200,
FT_FATAL = 250,

libQtC = None
libQtN = None
libFT = None
onLogPrint = None
logPrintInterface = None

def debugMsg(msg):
    print msg

def initFuelTransport():

    global libQtC, libQtN, libFT, onLogPrint, logPrintInterface

    if libFT is None:
        if platform.system() == 'Darwin':
            libQtC = cdll.LoadLibrary(self_path + '/QtCore.dylib')
            libQtN = cdll.LoadLibrary(self_path + '/QtNetwork.dylib')
            libFT = cdll.LoadLibrary(self_path + '/libFuelTransport.1.0.0.dylib')

        if platform.system() == 'Windows':
            libQtC = cdll.LoadLibrary(self_path + '\\Qt5Core.dll')
            libQtN = cdll.LoadLibrary(self_path + '\\Qt5Network.dll')
            libFT = cdll.LoadLibrary(self_path + '\\FuelTransport.dll')

        if platform.system() == 'Linux':
            libQtC = cdll.LoadLibrary(self_path + '/Qt5Core.so')
            libQtN = cdll.LoadLibrary(self_path + '/Qt5Network.so')
            libFT = cdll.LoadLibrary(self_path + '/FuelTransport.so')

        # Allocation
        libFT.ft_alloc.restype = c_void_p

        # Configuration
        libFT.ft_setTestInfo.argtypes = [c_void_p]
        libFT.ft_setProductID.argtypes = [c_void_p, c_uint]
        libFT.ft_setVersion.argtypes = [c_void_p, c_uint]
        libFT.ft_setApplicationID.argtypes = [c_void_p, c_ulonglong]
        libFT.ft_setSerialNo.argtypes = [c_void_p, c_ulonglong]
        libFT.ft_setID.argtypes = [c_void_p, c_uint, c_uint, c_uint, c_ulonglong, c_ulonglong]
        libFT.ft_setName.argtypes = [c_void_p, c_char_p]
        libFT.ft_setTitle.argtypes = [c_void_p, c_char_p]
        libFT.ft_setGroup.argtypes = [c_void_p, c_char_p]
        libFT.ft_setDescription.argtypes = [c_void_p, c_char_p, c_char_p, c_char_p]
        libFT.ft_setTimeout.argtypes = [c_void_p, c_float, c_float]
        libFT.ft_setEnableTCP.argtypes = [c_void_p]
        libFT.ft_setMinimumCycleTime.argtypes = [c_void_p, c_float]
        libFT.ft_setCycleTime.argtypes = [c_void_p, c_float]

        libFT.ft_addProcessDataChannel.argtypes = [c_void_p, c_ushort, c_ushort]
        libFT.ft_setSendingPolicy.argtypes = [c_void_p, c_ushort, c_bool, c_bool, c_bool, c_float]
        libFT.ft_setSecondarySendingPolicy.argtypes = [c_void_p, c_ushort, c_bool, c_bool, c_bool, c_float]

        # Comissioning
        libFT.ft_start.argtypes = [c_void_p]
        libFT.ft_stop.argtypes = [c_void_p]
        libFT.ft_doWork.argtypes = [c_void_p]

        libFT.ft_setProcessData.argtypes = [c_void_p, c_ushort, c_void_p]
        libFT.ft_getProcessData.argtypes = [c_void_p, c_ushort, c_void_p]
        libFT.ft_sendProcessData.argtypes = [c_void_p, c_ushort, c_bool]
        libFT.ft_sendCommand.argtypes = [c_void_p, c_ushort, c_ushort, c_void_p, c_ushort, c_double]
        libFT.ft_sendNotification.argtypes = [c_void_p, c_ubyte, c_ushort, c_ushort, c_void_p, c_ushort]
        libFT.ft_sendCacheRequest.argtypes = [c_void_p, c_float, c_float, c_float, c_ushort, c_ulonglong]
        libFT.ft_sendCacheData.argtypes = [c_void_p, c_float, c_void_p, c_ushort, c_float, c_ushort]
        libFT.ft_sendCachingStartedPacket.argtypes = [c_void_p, c_ulonglong, c_float, c_float, c_float]
        libFT.ft_sendCachingProgressPacket.argtypes = [c_void_p, c_ulonglong, c_ulonglong, c_float]
        libFT.ft_sendCachingFinishedPacket.argtypes = [c_void_p, c_ulonglong, c_double]
        libFT.ft_sendCachingAbortedPacket.argtypes = [c_void_p, c_int, c_char_p, c_ushort]

        # Callback function pointers
        libFT.ft_attachLogPrintFn.argtypes = [c_void_p]
        libFT.ft_attachProcessDataChannelAddedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachProcessDataReceivedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachProcessDataRequestFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachProcessDataChangedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachCommandReceivedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachCacheRequestReceivedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachCacheDataReceivedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachCachingStartedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachCachingProgressFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachCachingFinishedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachCachingAbortedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachNotificationReceivedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachConnectionEstablishedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachWatchdogWarningFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_attachDisconnectedFn.argtypes = [c_void_p, c_void_p]
        libFT.ft_enableProcessDataChangedOnChannel.argtypes = [c_void_p, c_ushort]
        libFT.ft_disableProcessDataChangedOnChannel.argtypes = [c_void_p, c_ushort]

        # Getters
        libFT.ft_getStatus.argtypes = [c_void_p]
        libFT.ft_getStatus.restype = c_int
        libFT.ft_getSyncedTime.argtypes = [c_void_p]
        libFT.ft_getSyncedTime.restype = c_double
        libFT.ft_getTestInt.argtypes = [c_void_p]
        libFT.ft_getTestInt.restype = c_int

        # DeAlloc
        libFT.ft_dealloc.argtypes = [c_void_p]

        @CFUNCTYPE(None, c_char_p)
        def interfaceFn(log):
            if onLogPrint != None:
                onLogPrint(log)
            pass

        logPrintInterface = interfaceFn
        onLogPrint = debugMsg
        libFT.ft_attachLogPrintFn(logPrintInterface)

initFuelTransport()

class FuelTransport(object):
    obj = None

    def __init__(self):
        self.obj = libFT.ft_alloc()

    def __del__(self):
        if self.obj is not None:
            libFT.ft_stop(self.obj)
            libFT.ft_dealloc(self.obj)

    def dealloc(self):
        libFT.ft_stop(self.obj)
        libFT.ft_dealloc(self.obj)

    def setTestInfo(self):
        libFT.ft_setTestInfo(self.obj)

    def setVendorID(self, vendorid):
        libFT.ft_setVendorID(self.obj, vendorid)

    def setProductID(self, productid):
        libFT.ft_setProductID(self.obj, productid)

    def setVersion(self, version):
        libFT.ft_setVersion(self.obj, version)

    def setApplicationID(self, applicationid):
        libFT.ft_setApplicationID(self.obj, applicationid)

    def setSerialNo(self, serialno):
        libFT.ft_setSerialNo(self.obj, serialno)

    def setID(self, vendorid, productid, version, applicationid, serialno):
        libFT.ft_setID(self.obj, vendorid, productid, version, applicationid, serialno)

    def setName(self, name):
        libFT.ft_setName(self.obj, name)

    def setTitle(self, title):
        libFT.ft_setTitle(self.obj, title)

    def setGroup(self, group):
        libFT.ft_setGroup(self.obj, group)

    def setDescription(self, name, title, group):
        libFT.ft_setDescription(self.obj, name, title, group)

    def setTimeout(self, warning, critical):
        libFT.ft_setTimeout(self.obj, warning, critical)

    def setEnableTCP(self):
        libFT.ft_setEnableTCP(self.obj)

    def setMinimumCycleTime(self, cycletime):
        libFT.ft_setMinimumCycleTime(self.obj, cycletime)

    def setCycleTime(self, cycletime):
        libFT.ft_setCycleTime(self.obj, cycletime)

    def addProcessDataChannel(self, index, dataLength):
        libFT.ft_addProcessDataChannel(self.obj, index, dataLength)

    def setSendingPolicy(self, index, udp, tcp, sendOnChange, sendInterval):
        libFT.ft_setSendingPolicy(self.obj, index, udp, tcp, sendOnChange, sendInterval)

    def setSecondarySendingPolicy(self, index, udp, tcp, sendOnChange, sendInterval):
        libFT.ft_setSecondarySendingPolicy(self.obj, index, udp, tcp, sendOnChange, sendInterval)

    def start(self):
        libFT.ft_start(self.obj)

    def stop(self):
        libFT.ft_stop(self.obj)

    def doWork(self):
        libFT.ft_doWork(self.obj)

    def setProcessData(self, index, dataptr, length):
        libFT.ft_setProcessData(self.obj, index, byref(dataptr), length)

    def getProcessData(self, index, dataptr, length):
        libFT.ft_getProcessData(self.obj, index, byref(dataptr), length)

    def sendProcessData(self, index, tcp):
        libFT.ft_sendProcessData(self.obj, index, tcp)

    def sendCommand(self, commandcode, subindex, data = None, datalength = 0, targettime = 0):
        libFT.ft_sendCommand(self.obj, commandcode, subindex, data, datalength, targettime)

    def sendNotification(self, level, code, subindex, msg):
        libFT.ft_sendNotification(self.obj, level, code, subindex, msg, len(msg))

    def sendCacheRequest(self, starttime, timerange, frequency, subindex, maxSampleCount):
        libFT.ft_sendCacheRequest(self.obj, starttime, timerange, frequency, subindex, maxSampleCount)

    def sendCacheData(self, time, data, datalength, progress, subindex):
        libFT.ft_sendCacheData(self.obj, time, byref(data), datalength, progress, subindex)

    def sendCachingStarted(self, sampleCount, startTime, timeRange, timeStep):
        libFT.ft_sendCachingStartedPacket(self.obj, sampleCount, startTime, timeRange, timeStep)

    def sendCachingProgress(self, samplesSent, totalSamples, percent):
        libFT.ft_sendCachingProgressPacket(self.obj, samplesSent, totalSamples, percent)

    def sendCachingFinished(self, totalSampleCount, elapsedSeconds):
        libFT.ft_sendCachingFinishedPacket(self.obj, totalSampleCount, elapsedSeconds)

    def sendCachingAborted(self, abortCode, msg):
        print "Cache abort"
        libFT.ft_sendCachingAbortedPacket(self.obj, abortCode, msg, len(msg))

    def attachLogPrintFn(self, func):
        @CFUNCTYPE(None, c_char_p)
        def interfaceFn(log):
            if self.onLogPrint != None:
                self.onLogPrint(log)
            pass

        self.logPrintInterface = interfaceFn
        self.onLogPrint = func

        if func is None:
            libFT.ft_attachLogPrintFn(self.obj, None)
        else:
            libFT.ft_attachLogPrintFn(self.obj, self.logPrintInterface)

    def PrDataChAddedEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_ushort)
        def interfaceFn(caller, channel):
            if self.onProcessDataChannelAdded != None:
                self.onProcessDataChannelAdded(caller, channel)
            pass

        self.processDataChannelAddedEventInterface = interfaceFn
        self.onProcessDataChannelAdded = func

        if func is None:
            libFT.ft_attachProcessDataChannelAddedFn(self.obj, None)
        else:
            libFT.ft_attachProcessDataChannelAddedFn(self.obj, self.processDataChannelAddedEventInterface)

    def PrDataRecvEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_ushort)
        def interfaceFn(caller, channel):
            if self.onProcessDataReceived != None:
                self.onProcessDataReceived(caller, channel)
            pass

        self.processDataReceivedEventInterface = interfaceFn
        self.onProcessDataReceived = func

        if func is None:
            libFT.ft_attachProcessDataReceivedFn(self.obj, None)
        else:
            libFT.ft_attachProcessDataReceivedFn(self.obj, self.processDataReceivedEventInterface)

    def PrDataChangedEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_ushort)
        def interfaceFn(caller, channel):
            if self.onProcessDataChanged != None:
                self.onProcessDataChanged(caller, channel)
            pass

        self.processDataChangedEventInterface = interfaceFn
        self.onProcessDataChanged = func

        if func is None:
            libFT.ft_attachProcessDataChangedFn(self.obj, None)
        else:
            libFT.ft_attachProcessDataChangedFn(self.obj, self.processDataChangedEventInterface)

    def enPrDataChgdOnCh(self, channel):
        libFT.ft_enableProcessDataChangedOnChannel(self.obj, channel)

    def disPrDataChgdOnCh(self, channel):
        libFT.ft_disableProcessDataChangedOnChannel(self.obj, channel)

    def PrDataReqEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_ushort)
        def interfaceFn(caller, channel):
            if self.onProcessDataRequest != None:
                self.onProcessDataRequest(caller, channel)
            pass

        self.processDataRequestEventInterface = interfaceFn
        self.onProcessDataRequest = func

        if func is None:
            libFT.ft_attachProcessDataRequestFn(self.obj, None)
        else:
            libFT.ft_attachProcessDataRequestFn(self.obj, self.processDataRequestEventInterface)

    def CmdRecvEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_ushort, c_ushort, c_char_p, c_ushort, c_double, c_double)
        def interfaceFn(caller, commandcode, subindex, data, datalength, dispatchtime, targettime):
            if self.onCommandReceived != None:
                self.onCommandReceived(caller, commandcode, subindex, data, datalength, dispatchtime, targettime)
            pass

        self.commandReceivedEventInterface = interfaceFn
        self.onCommandReceived = func

        if func is None:
            libFT.ft_attachCommandReceivedFn(self.obj, None)
        else:
            libFT.ft_attachCommandReceivedFn(self.obj, self.commandReceivedEventInterface)

    def CacheReqEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_float, c_float, c_float, c_ushort, c_ulonglong)
        def interfaceFn(caller, startTime, timeRange, frequency, subindex, maxsamplecount):
            if self.onCacheRequestReceived != None:
                self.onCacheRequestReceived(caller, startTime, timeRange, frequency, subindex, maxsamplecount)
            pass

        self.cacheRequestReceivedEventInterface = interfaceFn
        self.onCacheRequestReceived = func

        if func is None:
            libFT.ft_attachCacheRequestReceivedFn(self.obj, None)
        else:
            libFT.ft_attachCacheRequestReceivedFn(self.obj, self.cacheRequestReceivedEventInterface)

    def CacheDataRecvEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_float, c_float, c_char_p, c_ushort, c_ushort)
        def interfaceFn(caller, time, progress, data, datalength, subindex):
            if self.onCacheDataReceived != None:
                self.onCacheDataReceived(caller, time, progress, data, datalength, subindex)
            pass

        self.cacheDataReceivedEventInterface = interfaceFn
        self.onCacheDataReceived = func

        if func is None:
            libFT.ft_attachCacheDataReceivedFn(self.obj, None)
        else:
            libFT.ft_attachCacheDataReceivedFn(self.obj, self.cacheDataReceivedEventInterface)

    def CachingStartedEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_ulonglong, c_float, c_float, c_float)
        def interfaceFn(caller, sampleCount, startTime, timeRange, timeStep):
            if self.onCachingStarted != None:
                self.onCachingStarted(caller, sampleCount, startTime, timeRange, timeStep)
            pass

        self.cachingStartedEventInterface = interfaceFn
        self.onCachingStarted = func

        if func is None:
            libFT.ft_attachCachingStartedFn(self.obj, None)
        else:
            libFT.ft_attachCachingStartedFn(self.obj, self.cachingStartedEventInterface)

    def CachingProgressEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_ulonglong, c_ulonglong, c_float)
        def interfaceFn(caller, samplesSent, totalSamples, percent):
            if self.onCachingProgress != None:
                self.onCachingProgress(caller, samplesSent, totalSamples, percent)
            pass

        self.cachingProgressEventInterface = interfaceFn
        self.onCachingProgress = func

        if func is None:
            libFT.ft_attachCachingProgressFn(self.obj, None)
        else:
            libFT.ft_attachCachingProgressFn(self.obj, self.cachingProgressEventInterface)

    def CachingFinishedEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_ulonglong, c_double)
        def interfaceFn(caller, totalSampleCount, elapsedSeconds):
            if self.onCachingFinished != None:
                self.onCachingFinished(caller, totalSampleCount, elapsedSeconds)
            pass

        self.cachingFinishedEventInterface = interfaceFn
        self.onCachingFinished = func

        if func is None:
            libFT.ft_attachCachingFinishedFn(self.obj, None)
        else:
            libFT.ft_attachCachingFinishedFn(self.obj, self.cachingFinishedEventInterface)

    def CachingAbortedEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_int, c_char_p, c_ushort)
        def interfaceFn(caller, abortCode, msg, msglength):
            if self.onCachingAborted != None:
                self.onCachingAborted(caller, abortCode, msg, msglength)
            pass

        self.cachingAbortedEventInterface = interfaceFn
        self.onCachingAborted = func

        if func is None:
            libFT.ft_attachCachingAbortedFn(self.obj, None)
        else:
            libFT.ft_attachCachingAbortedFn(self.obj, self.cachingAbortedEventInterface)

    def NotifiRecvEvFn(self, func):
        @CFUNCTYPE(None, c_void_p, c_ubyte, c_ushort, c_ushort, c_char_p, c_ushort, c_double)
        def interfaceFn(caller, level, code, subindex, msg, msglength, dispatchtime):
            if self.onNotificationReceived != None:
                self.onNotificationReceived(caller, level, code, subindex, msg, msglength, dispatchtime)
            pass

        self.notificationReceivedEventInterface = interfaceFn
        self.onNotificationReceived = func

        if func is None:
            libFT.ft_attachNotificationReceivedFn(self.obj, None)
        else:
            libFT.ft_attachNotificationReceivedFn(self.obj, self.notificationReceivedEventInterface)


    def ConnEstEvFn(self, func):
        @CFUNCTYPE(None, c_void_p)
        def interfaceFn(caller):
            if self.onConnectionEstablished != None:
                self.onConnectionEstablished(caller)
            pass

        self.connectionEstablishedEventInterface = interfaceFn
        self.onConnectionEstablished = func

        if func is None:
            libFT.ft_attachConnectionEstablishedFn(self.obj, None)
        else:
            libFT.ft_attachConnectionEstablishedFn(self.obj, self.connectionEstablishedEventInterface)


    def WatchdogWarningEvFn(self, func):
        @CFUNCTYPE(None, c_void_p)
        def interfaceFn(caller):
            if self.onWatchdogWarning != None:
                self.onWatchdogWarning(caller)
            pass

        self.watchdogWarningEventInterface = interfaceFn
        self.onWatchdogWarning = func

        if func is None:
            libFT.ft_attachWatchdogWarningFn(self.obj, None)
        else:
            libFT.ft_attachWatchdogWarningFn(self.obj, self.watchdogWarningEventInterface)


    def DisconnEvFn(self, func):
        @CFUNCTYPE(None, c_void_p)
        def interfaceFn(caller):
            if self.onDisconnected != None:
                self.onDisconnected(caller)
            pass

        self.disconnectedEventInterface = interfaceFn
        self.onDisconnected = func

        if func is None:
            libFT.ft_attachDisconnectedFn(self.obj, None)
        else:
            libFT.ft_attachDisconnectedFn(self.obj, self.disconnectedEventInterface)

    def getSyncedTime(self):
        return libFT.ft_getSyncedTime(self.obj)

    def getStatus(self):
        return libFT.ft_getStatus(self.obj)

    def getTestInt(self):
        return libFT.ft_getTestInt()

    def toUnsignedShort(self, data):
        return cast(data, POINTER(c_ushort))[0]

    def toShort(self, data):
        return cast(data, POINTER(c_short))[0]

    def toInt(self, data):
        return cast(data, POINTER(c_int))[0]

    def toUnsignedInt(self, data):
        return cast(data, POINTER(c_uint))[0]