import smbus
import time

class VL53L1X:
    
    I2C_DevAddr = 0x29
    
    VL53L1X_IMPLEMENTATION_VER_MAJOR                    =   1
    VL53L1X_IMPLEMENTATION_VER_MINOR                    =   0
    VL53L1X_IMPLEMENTATION_VER_SUB                      =   1
    VL53L1X_IMPLEMENTATION_VER_REVISION                 = 0000
    
    SOFT_RESET                                          =    0x0000
    VL53L1_I2C_SLAVE__DEVICE_ADDRESS                    =    0x0001
    VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND        =    0x0008
    ALGO__CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS      =    0x0016
    ALGO__CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS  =    0x0018
    ALGO__CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS  =    0x001A
    ALGO__PART_TO_PART_RANGE_OFFSET_MM                  =    0x001E
    MM_CONFIG__INNER_OFFSET_MM                          =    0x0020
    MM_CONFIG__OUTER_OFFSET_MM                          =    0x0022
    GPIO_HV_MUX__CTRL                                   =    0x0030
    GPIO__TIO_HV_STATUS                                 =    0x0031
    SYSTEM__INTERRUPT_CONFIG_GPIO                       =    0x0046
    PHASECAL_CONFIG__TIMEOUT_MACROP                     =    0x004B
    RANGE_CONFIG__TIMEOUT_MACROP_A_HI                   =    0x005E
    RANGE_CONFIG__VCSEL_PERIOD_A                        =    0x0060
    RANGE_CONFIG__VCSEL_PERIOD_B                        =    0x0063
    RANGE_CONFIG__TIMEOUT_MACROP_B_HI                   =    0x0061
    RANGE_CONFIG__TIMEOUT_MACROP_B_LO                   =    0x0062
    RANGE_CONFIG__SIGMA_THRESH                          =    0x0064
    RANGE_CONFIG__MIN_COUNT_RATE_RTN_LIMIT_MCPS         =    0x0066
    RANGE_CONFIG__VALID_PHASE_HIGH                      =    0x0069
    VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD              =    0x006C
    SYSTEM__THRESH_HIGH                                 =    0x0072
    SYSTEM__THRESH_LOW                                  =    0x0074
    SD_CONFIG__WOI_SD0                                  =    0x0078
    SD_CONFIG__INITIAL_PHASE_SD0                        =    0x007A
    ROI_CONFIG__USER_ROI_CENTRE_SPAD                    =    0x007F
    ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE       =    0x0080
    SYSTEM__SEQUENCE_CONFIG                             =    0x0081
    VL53L1_SYSTEM__GROUPED_PARAMETER_HOLD               =    0x0082
    SYSTEM__INTERRUPT_CLEAR                             =    0x0086
    SYSTEM__MODE_START                                  =    0x0087
    VL53L1_RESULT__RANGE_STATUS                         =    0x0089
    VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0       =    0x008C
    RESULT__AMBIENT_COUNT_RATE_MCPS_SD                  =    0x0090
    VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0                 = 0x0096
    VL53L1_RESULT__PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0    = 0x0098
    VL53L1_RESULT__OSC_CALIBRATE_VAL                    =    0x00DE
    VL53L1_FIRMWARE__SYSTEM_STATUS                      =    0x00E5
    VL53L1_IDENTIFICATION__MODEL_ID                     =    0x010F
    VL53L1_ROI_CONFIG__MODE_ROI_CENTRE_SPAD             =    0x013E
    
    
    VL53L1X_DEFAULT_DEVICE_ADDRESS                      =    0x52
    
    ALGO__PART_TO_PART_RANGE_OFFSET_MM                  =    0x001E
    MM_CONFIG__INNER_OFFSET_MM                          =    0x0020
    MM_CONFIG__OUTER_OFFSET_MM                          =    0x0022

    dis = 0
    dis1 = 0
    dis2 = 0

    VL51L1X_DEFAULT_CONFIGURATION = [
        0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x02, 0x08, 
        0x00, 0x08, 0x10, 0x01, 0x01, 0x00, 0x00, 0x00, 
        0x00, 0xff, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x20, 0x0b, 0x00, 0x00, 0x02, 0x0a, 0x21, 
        0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0xc8, 
        0x00, 0x00, 0x38, 0xff, 0x01, 0x00, 0x08, 0x00, 
        0x00, 0x01, 0xdb, 0x0f, 0x01, 0xf1, 0x0d, 0x01, 
        0x68, 0x00, 0x80, 0x08, 0xb8, 0x00, 0x00, 0x00, 
        0x00, 0x0f, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x0f, 0x0d, 0x0e, 0x0e, 0x00, 
        0x00, 0x02, 0xc7, 0xff, 0x9B, 0x00, 0x00, 0x00, 
        0x01, 0x00, 0x00 ]

    def __init__(self, bus):
        self.i2cbus = smbus.SMBus(bus)
        self.i2cAddr = self.I2C_DevAddr
        time.sleep(0.16)

    def begin(self):
        tmp = 0
        for Addr in range(0x2D,0x2d + len(self.VL51L1X_DEFAULT_CONFIGURATION)):
            self.writeByteData(Addr, self.VL51L1X_DEFAULT_CONFIGURATION[Addr - 0x2D])
        self.startRanging()
        while tmp == 0:
            tmp = self.checkForDataReady()
            #print(tmp)
            time.sleep(1)
        self.clearInterrupt()
        self.writeByteData(0x0087, 0x00)
        self.writeByteData(self.VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND, 0x09)
        self.writeByteData(0x0B, 0)
        return True
        
    def writeByteData(self, index, byte):
        self.i2cbus.write_i2c_block_data(self.i2cAddr, index >> 8, [index & 0xff, byte])

    def writeWordData(self, index, value):
        buffer = []
        buffer.append(index & 0xff)
        buffer.append(value >> 8)
        buffer.append(value & 0xff)
        self.i2cbus.write_i2c_block_data(self.i2cAddr, index >> 8, buffer)

    def writeWordData32(self, index, value):
        buffer = []
        buffer.append(index & 0xff)
        buffer.append(value >> 24 & 0xff)
        buffer.append(value >> 16 & 0xff)
        buffer.append(value >> 8 & 0xff)
        buffer.append(value & 0xff)
        self.i2cbus.write_i2c_block_data(self.i2cAddr, index >> 8, buffer)

    def readByteData(self, index):
        self.i2cbus.write_i2c_block_data(self.i2cAddr, index >> 8, [index & 0xff])
        return self.i2cbus.read_byte(self.i2cAddr)

    def readWordData(self, index):
        rslt1 = self.readByteData(index)
        rslt2 = self.readByteData(index + 1)
        return ((rslt1 << 8)| rslt2)
        
    def readWordData32(self, index):
        rslt1 = self.readByteData(index)
        rslt2 = self.readByteData(index + 1)
        rslt3 = self.readByteData(index + 2)
        rslt4 = self.readByteData(index + 3)
        return ((rslt1 << 24)| (rslt2 << 16)|(rslt3 << 8)| rslt4)

    def setI2CAddress(self, address):
        self.writeByteData(self.VL53L1_I2C_SLAVE__DEVICE_ADDRESS, address >> 1)
        _addr = address

    def getI2CAddress(self):
        return self._addr

    def clearInterrupt(self):
        self.writeByteData(self.SYSTEM__INTERRUPT_CLEAR, 0x01)

    def setInterruptPolarityHigh(self):
        self.setInterruptPolarity(1)

    def setInterruptPolarityLow(self):
        self.setInterruptPolarity(0)

    def setInterruptPolarity(self, NewPolarity):
        Temp = 0
        Temp = self.readByteData(self.GPIO_HV_MUX__CTRL)
        Temp = Temp & 0xEF
        self.writeByteData(self.GPIO_HV_MUX__CTRL, Temp | (not(NewPolarity & 1)) << 4)

    def getInterruptPolarity(self):
        Temp = 0
        pInterruptPolarity = 0
    
        Temp = self.readByteData(self.GPIO_HV_MUX__CTRL)
        Temp = Temp & 0x10
        pInterruptPolarity = not(Temp>>4)
        return pInterruptPolarity
        
    def startRanging(self):
        self.writeByteData(self.SYSTEM__MODE_START, 0x40)

    def stopRanging(self):
        self.writeByteData(self.SYSTEM__MODE_START, 0x00)

    def checkForDataReady(self):
        Temp =0
        IntPol = 0
        isDataReady = 0

        IntPol = self.getInterruptPolarity()
        Temp = self.readByteData(self.GPIO__TIO_HV_STATUS)
        print(IntPol)
        print("11111")
        print(Temp)
        time.sleep(0.5)
        if ((Temp & 1) == IntPol):
            return  1
        else:
            return  0

    def setTimingBudgetInMs(self, timingBudget):
        DM = 0
    
        DM = self.getDistanceMode()
        #print(DM)
        if (DM == 0):
            return 1
        elif (DM == 1):
            if (timingBudget == 15):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x01D)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0027)
            elif (timingBudget == 20):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x0051)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x006E)
            elif (timingBudget == 33):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x00D6)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x006E)
            elif (timingBudget == 50):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x1AE)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x01E8)
            elif (timingBudget == 100):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x02E1)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0388)
            elif (timingBudget == 200):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x03E1)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0496)
            elif (timingBudget == 500):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x0591)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x05C1)
            else:
                print(" ")
            
        else:
            if (timingBudget == 20):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x001E)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0022)
            elif (timingBudget == 33):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x0060)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x006E)
            elif (timingBudget == 50):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x00AD)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x00C6)
            elif (timingBudget == 100):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x01CC)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x01EA)
            elif (timingBudget == 200):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x02D9)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x02F8)
            elif (timingBudget == 500):
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x048F)
                self.writeWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x04A4)
            else:
                print(" ")

    def getTimingBudgetInMs(self):
        Temp = 0
        pTimingBudget = 0
    
        Temp = self.readWordData(self.RANGE_CONFIG__TIMEOUT_MACROP_A_HI)
        #print(Temp)
        if (Temp == 0x001D):
            pTimingBudget = 15
        elif (Temp == 0x0051 or Temp == 0x001E):
            pTimingBudget = 20
        elif (Temp == 0x00D6 or Temp == 0x0060):
            pTimingBudget = 33
        elif (Temp == 0x1AE or Temp == 0x00AD):
            pTimingBudget = 50
        elif (Temp == 0x02E1 or Temp == 0x01CC):
            pTimingBudget = 100
        elif (Temp == 0x03E1 or Temp == 0x02D9):
            pTimingBudget = 200
        elif (Temp == 0x0591 or Temp == 0x048F):
            pTimingBudget = 500
        else:
            pTimingBudget = 0
        return pTimingBudget

    def setDistanceModeLong(self):
        self.setDistanceMode(2)

    def setDistanceModeShort(self):
        self.setDistanceMode(1)

    def setDistanceMode(self, DM):
        TB = 0
    
        TB = self.getTimingBudgetInMs()
        if (DM == 1):
            self.writeByteData(self.PHASECAL_CONFIG__TIMEOUT_MACROP, 0x14)
            self.writeByteData(self.RANGE_CONFIG__VCSEL_PERIOD_A, 0x07)
            self.writeByteData(self.RANGE_CONFIG__VCSEL_PERIOD_B, 0x05)
            self.writeByteData(self.RANGE_CONFIG__VALID_PHASE_HIGH, 0x38)
            self.writeWordData(self.SD_CONFIG__WOI_SD0, 0x0705)
            self.writeWordData(self.SD_CONFIG__INITIAL_PHASE_SD0, 0x0606)
        elif (DM == 2):
            self.writeByteData(self.PHASECAL_CONFIG__TIMEOUT_MACROP, 0x0A)
            self.writeByteData(self.RANGE_CONFIG__VCSEL_PERIOD_A, 0x0F)
            self.writeByteData(self.RANGE_CONFIG__VCSEL_PERIOD_B, 0x0D)
            self.writeByteData(self.RANGE_CONFIG__VALID_PHASE_HIGH, 0xB8)
            self.writeWordData(self.SD_CONFIG__WOI_SD0, 0x0F0D)
            self.writeWordData(self.SD_CONFIG__INITIAL_PHASE_SD0, 0x0E0E)
        else:
            print(" ")
        self.setTimingBudgetInMs(TB)

    def getDistanceMode(self):
        TempDM = 0
        DM = 0
    
        TempDM = self.readByteData(self.PHASECAL_CONFIG__TIMEOUT_MACROP)
        if (TempDM == 0x14):
            DM=1
        elif(TempDM == 0x0A):
            DM=2
        return DM

    def setInterMeasurementInMs(self, InterMeasMs):
        ClockPLL = 0
    
        ClockPLL = self.readWordData(self.VL53L1_RESULT__OSC_CALIBRATE_VAL)
        ClockPLL = ClockPLL & 0x3FF
        self.writeWordData32(self.VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD, (ClockPLL * InterMeasMs * 1066 / 1000))

    def getInterMeasurementInMs(self):
        ClockPLL = 0
        pIM = 0
        tmp = 0
        tmp = self.readWordData32(self.VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD)
        pIM = tmp
        ClockPLL = self.readWordData(self.VL53L1_RESULT__OSC_CALIBRATE_VAL)
        ClockPLL = ClockPLL & 0x3FF
        pIM= pIM/(ClockPLL*1.065)
        return pIM

    def bootState(self):
        tmp = 0
    
        tmp = self.readByteData(self.VL53L1_FIRMWARE__SYSTEM_STATUS)
        return tmp

    def getDistance(self):
        tmp = 0
  
        tmp = self.readWordData(self.VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0)
        self.clearInterrupt()
        return tmp

    def getSignalPerSpad(self):
        SpNb = 1
        signal = 0
        signalRate = 0
    
        signal = self.readWordData(self.VL53L1_RESULT__PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0)
        SpNb = self.readWordData(self.VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0)
        signalRate = 2000.0 * signal / SpNb
        return signalRate

    def getAmbientPerSpad(self):
        AmbientRate = 0
        SpNb = 1
        ambPerSp = 0
    
        AmbientRate = self.readWordData(self.RESULT__AMBIENT_COUNT_RATE_MCPS_SD)
        SpNb = self.readWordData(self.VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0)
        ambPerSp=2000.0 * AmbientRate / SpNb
        return ambPerSp


    def getSignalRate(self):
        tmp = 0
    
        tmp = self.readWordData(self.VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0)
        tmp = tmp * 8
        return tmp


    def getSpadNb(self):
        tmp = 0
    
        tmp = self.readWordData(self.VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0)
        tmp = tmp >> 8
        return tmp

    def getAmbientRate(self):
        ambRate = 0
        tmp = 0
    
        tmp = self.readWordData(self.RESULT__AMBIENT_COUNT_RATE_MCPS_SD)
        ambRate = tmp*8
        return ambRate

    def getRangeStatus(self):
        rangeStatus = 0
        RgSt = 0
    
        RgSt = self.readByteData(self.VL53L1_RESULT__RANGE_STATUS)
        RgSt = RgSt&0x1F
        if (RgSt == 9):
            RgSt = 0
        elif (RgSt == 6):
            RgSt = 1
        elif (RgSt == 4):
            RgSt = 2
        elif (RgSt == 8):
            RgSt = 3
        elif (RgSt == 5):
            RgSt = 4
        elif (RgSt == 3):
            RgSt = 5
        elif (RgSt == 19):
            RgSt = 6
        elif (RgSt == 7):
            RgSt = 7
        elif (RgSt == 12):
            RgSt = 9
        elif (RgSt == 18):
            RgSt = 10
        elif (RgSt == 22):
            RgSt = 11
        elif (RgSt == 23):
            RgSt = 12
        elif (RgSt == 13):
            RgSt = 13
        else:
            RgSt = 255
        rangeStatus = RgSt
        return rangeStatus

    def setOffset(self, OffsetValue):
        Temp = (OffsetValue * 4)
        self.writeWordData(self.ALGO__PART_TO_PART_RANGE_OFFSET_MM, Temp)
        self.writeWordData(self.MM_CONFIG__INNER_OFFSET_MM, 0x0)
        self.writeWordData(self.MM_CONFIG__OUTER_OFFSET_MM, 0x0)

    def getOffset(self):
        offset = 0
        Temp = 0
    
        Temp = self.readWordData(self.ALGO__PART_TO_PART_RANGE_OFFSET_MM)
        Temp = Temp << 3
        Temp = Temp >> 5
        offset = (int16_t)(Temp)
        return offset

    def setXTalk(self, XtalkValue):
        self.writeWordData(self.ALGO__CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS, 0x0000)
        self.writeWordData(self.ALGO__CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS, 0x0000)
        self.writeWordData(self.ALGO__CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS, (XtalkValue<<9)/1000)

    def getXTalk(self):
        xtalk = 0
        tmp = 0
    
        tmp = self.readWordData(self.ALGO__CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS)
        xtalk = (tmp*1000)>>9
        return xtalk


    def setDistanceThreshold(self, ThreshLow, ThreshHigh, Window):
        Temp = 0
    
        Temp = self.readByteData(self.SYSTEM__INTERRUPT_CONFIG_GPIO)
        Temp = Temp & 0x47
    
        self.writeByteData(self.SYSTEM__INTERRUPT_CONFIG_GPIO, ((Temp | (Window & 0x07)) | 0x40))
        self.writeWordData(self.SYSTEM__THRESH_HIGH, ThreshHigh)
        self.writeWordData(self.SYSTEM__THRESH_LOW, ThreshLow)

    def getDistanceThresholdWindow(self):
        window = 0
        tmp = 0
        tmp = self.readByteData(self.SYSTEM__INTERRUPT_CONFIG_GPIO)
        window = tmp & 0x7
        return window

    def getDistanceThresholdLow(self):
        low = 0
        tmp = 0
    
        tmp = self.readWordData(self.SYSTEM__THRESH_LOW)
        low = tmp
        return low

    def getDistanceThresholdHigh(self):
        high = 0
        tmp = 0

        tmp = self.readWordData(self.SYSTEM__THRESH_HIGH)
        high = tmp
        return high

    def setROI(uX, uY):
        OpticalCenter = 0

        OpticalCenter = self.readByteData(self.VL53L1_ROI_CONFIG__MODE_ROI_CENTRE_SPAD)
        if (X > 16):
            X = 16
        if (Y > 16):
            Y = 16
        if (X > 10 or Y > 10):
            OpticalCenter = 199
        self.writeByteData(self.ROI_CONFIG__USER_ROI_CENTRE_SPAD, OpticalCenter)
        self.writeByteData(self.ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE, (Y - 1) << 4 | (X - 1))

    def getROIX(self):
        tmp = 0
        ROI_X = 0
    
        tmp = self.readByteData(self.ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE)
        ROI_X = (tmp & 0x0F) + 1
        return ROI_X

    def getROIY(self):
        tmp = 0
        ROI_Y = 0
    
        tmp = self.readByteData(self.ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE)
        ROI_Y = ((tmp & 0xF0) >> 4) + 1
        return ROI_Y

    def setSignalThreshold(uSignal):
        self.writeWordData(self.RANGE_CONFIG__MIN_COUNT_RATE_RTN_LIMIT_MCPS,Signal>>3)

    def getSignalThreshold(self):
        signal = 0
        tmp = 0
    
        tmp = self.readWordData(self.RANGE_CONFIG__MIN_COUNT_RATE_RTN_LIMIT_MCPS)
        signal = tmp <<3
        return signal

    def setSigmaThreshold(uSigma):
        if(Sigma > (0xFFFF>>2)):
            return 1
        self.writeWordData(self.RANGE_CONFIG__SIGMA_THRESH,Sigma<<2)

    def getSigmaThreshold(self):
        sigma = 0
        tmp = 0
    
        tmp = self.readWordData(self.RANGE_CONFIG__SIGMA_THRESH)
        sigma = tmp >> 2
        return sigma

    def startTemperatureUpdate(self):
        tmp = 0
        
        self.writeByteData(self.VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND,0x81)
        self.writeByteData(0x0B,0x92)
        self.startRanging()
        while(tmp==0):
            tmp = self.checkForDataReady()
            time.sleep(0.5)
        self.clearInterrupt()
        self.stopRanging()
        self.writeByteData(self.VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND, 0x09)
        self.writeByteData(0x0B, 0)

    def calibrateOffset(utargetDistInMm):
            offset = getOffset()
            i = 0
            tmp = 0
            AverageDistance = 0
            udistance = 0
        
            self.writeWordData(self.ALGO__PART_TO_PART_RANGE_OFFSET_MM, 0x0)
            self.writeWordData(self.MM_CONFIG__INNER_OFFSET_MM, 0x0)
            self.writeWordData(self.MM_CONFIG__OUTER_OFFSET_MM, 0x0)
            self.startRanging()
            for i in range(0, 50):
                while (tmp == 0):
                    tmp = self.checkForDataReady()
                    time.sleep(0.5)
                distance = self.getDistance()
                clearInterrupt()
                AverageDistance = AverageDistance + distance
            self.stopRanging()
            AverageDistance = AverageDistance / 50
            offset = targetDistInMm - AverageDistance
            self.writeWordData(self.ALGO__PART_TO_PART_RANGE_OFFSET_MM, offset*4)

    def calibrateXTalk(utargetDistInMm):
        uxTalk = getXTalk()
        i = 0
        tmp = 0
        AverageSignalRate = 0
        AverageDistance = 0
        AverageSpadNb = 0
        udistance = 0
        spadNum = 0
        usr = 0
    
        self.writeWordData(0x0016,0)
        self.startRanging()
        for i in range(0, 50):
            while (tmp == 0):
                tmp = checkForDataReady()
                time.sleep(0.5)
            sr = getSignalRate()
            distance = self.getDistance()
            self.clearInterrupt()
            AverageDistance = AverageDistance + distance
            spadNum = self.getSignalRate()
            AverageSpadNb = AverageSpadNb + spadNum
            AverageSignalRate = AverageSignalRate + sr
        self.stopRanging()
        AverageDistance = AverageDistance / 50
        AverageSpadNb = AverageSpadNb / 50
        AverageSignalRate = AverageSignalRate / 50
        xTalk = 512*(AverageSignalRate*(1-(AverageDistance/targetDistInMm)))/AverageSpadNb
        self.writeWordData(0x0016, xTalk)

    def gesture(self):
        self.setDistanceThreshold(50, 400, 3)
        gestureStatus = 0
        self.dis1 = self.dis2
        self.dis2 = self.getDistance()
        self.dis = self.dis2 - self.dis1
        time.sleep(0.01)
        if(self.dis < (-100)):
            gestureStatus = 1
        elif(self.dis > 100):
            gestureStatus = 2
        else:
            gestureStatus = 0
        return gestureStatus
