#include "DFRobot_VL53L1X.h"

const uint8_t VL51L1X_DEFAULT_CONFIGURATION[] = {
0x00, /* 0x2d : set bit 2 and 5 to 1 for fast plus mode (1MHz I2C), else don't touch */
0x00, /* 0x2e : bit 0 if I2C pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
0x00, /* 0x2f : bit 0 if GPIO pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
0x01, /* 0x30 : set bit 4 to 0 for active high interrupt and 1 for active low (bits 3:0 must be 0x1), use SetInterruptPolarity() */
0x02, /* 0x31 : bit 1 = interrupt depending on the polarity, use CheckForDataReady() */
0x00, /* 0x32 : not user-modifiable */
0x02, /* 0x33 : not user-modifiable */
0x08, /* 0x34 : not user-modifiable */
0x00, /* 0x35 : not user-modifiable */
0x08, /* 0x36 : not user-modifiable */
0x10, /* 0x37 : not user-modifiable */
0x01, /* 0x38 : not user-modifiable */
0x01, /* 0x39 : not user-modifiable */
0x00, /* 0x3a : not user-modifiable */
0x00, /* 0x3b : not user-modifiable */
0x00, /* 0x3c : not user-modifiable */
0x00, /* 0x3d : not user-modifiable */
0xff, /* 0x3e : not user-modifiable */
0x00, /* 0x3f : not user-modifiable */
0x0F, /* 0x40 : not user-modifiable */
0x00, /* 0x41 : not user-modifiable */
0x00, /* 0x42 : not user-modifiable */
0x00, /* 0x43 : not user-modifiable */
0x00, /* 0x44 : not user-modifiable */
0x00, /* 0x45 : not user-modifiable */
0x20, /* 0x46 : interrupt configuration 0->level low detection, 1-> level high, 2-> Out of window, 3->In window, 0x20-> New sample ready , TBC */
0x0b, /* 0x47 : not user-modifiable */
0x00, /* 0x48 : not user-modifiable */
0x00, /* 0x49 : not user-modifiable */
0x02, /* 0x4a : not user-modifiable */
0x0a, /* 0x4b : not user-modifiable */
0x21, /* 0x4c : not user-modifiable */
0x00, /* 0x4d : not user-modifiable */
0x00, /* 0x4e : not user-modifiable */
0x05, /* 0x4f : not user-modifiable */
0x00, /* 0x50 : not user-modifiable */
0x00, /* 0x51 : not user-modifiable */
0x00, /* 0x52 : not user-modifiable */
0x00, /* 0x53 : not user-modifiable */
0xc8, /* 0x54 : not user-modifiable */
0x00, /* 0x55 : not user-modifiable */
0x00, /* 0x56 : not user-modifiable */
0x38, /* 0x57 : not user-modifiable */
0xff, /* 0x58 : not user-modifiable */
0x01, /* 0x59 : not user-modifiable */
0x00, /* 0x5a : not user-modifiable */
0x08, /* 0x5b : not user-modifiable */
0x00, /* 0x5c : not user-modifiable */
0x00, /* 0x5d : not user-modifiable */
0x01, /* 0x5e : not user-modifiable */
0xdb, /* 0x5f : not user-modifiable */
0x0f, /* 0x60 : not user-modifiable */
0x01, /* 0x61 : not user-modifiable */
0xf1, /* 0x62 : not user-modifiable */
0x0d, /* 0x63 : not user-modifiable */
0x01, /* 0x64 : Sigma threshold MSB (mm in 14.2 format for MSB+LSB), use SetSigmaThreshold(), default value 90 mm  */
0x68, /* 0x65 : Sigma threshold LSB */
0x00, /* 0x66 : Min count Rate MSB (MCPS in 9.7 format for MSB+LSB), use SetSignalThreshold() */
0x80, /* 0x67 : Min count Rate LSB */
0x08, /* 0x68 : not user-modifiable */
0xb8, /* 0x69 : not user-modifiable */
0x00, /* 0x6a : not user-modifiable */
0x00, /* 0x6b : not user-modifiable */
0x00, /* 0x6c : interMeasurement period MSB, 32 bits register, use SetIntermeasurementInMs() */
0x00, /* 0x6d : interMeasurement period */
0x0f, /* 0x6e : interMeasurement period */
0x89, /* 0x6f : interMeasurement period LSB */
0x00, /* 0x70 : not user-modifiable */
0x00, /* 0x71 : not user-modifiable */
0x00, /* 0x72 : distance threshold high MSB (in mm, MSB+LSB), use SetD:tanceThreshold() */
0x00, /* 0x73 : distance threshold high LSB */
0x00, /* 0x74 : distance threshold low MSB ( in mm, MSB+LSB), use SetD:tanceThreshold() */
0x00, /* 0x75 : distance threshold low LSB */
0x00, /* 0x76 : not user-modifiable */
0x01, /* 0x77 : not user-modifiable */
0x0f, /* 0x78 : not user-modifiable */
0x0d, /* 0x79 : not user-modifiable */
0x0e, /* 0x7a : not user-modifiable */
0x0e, /* 0x7b : not user-modifiable */
0x00, /* 0x7c : not user-modifiable */
0x00, /* 0x7d : not user-modifiable */
0x02, /* 0x7e : not user-modifiable */
0xc7, /* 0x7f : ROI center, use SetROI() */
0xff, /* 0x80 : XY ROI (X=Width, Y=Height), use SetROI() */
0x9B, /* 0x81 : not user-modifiable */
0x00, /* 0x82 : not user-modifiable */
0x00, /* 0x83 : not user-modifiable */
0x00, /* 0x84 : not user-modifiable */
0x01, /* 0x85 : not user-modifiable */
0x00, /* 0x86 : clear interrupt, use ClearInterrupt() */
0x00  /* 0x87 : start ranging, use StartRanging() or StopRanging(), If you want an automatic start after VL53L1X_init() call, put 0x40 in location 0x87 */
};

bool DFRobot_VL53L1X::begin()
{
    lastOperateStatus = eVL53L1X_InitError;
    uint8_t Addr = 0x00, tmp = 0;

    for (Addr = 0x2D; Addr <= 0x87; Addr++){
        writeByteData(Addr, VL51L1X_DEFAULT_CONFIGURATION[Addr - 0x2D]);
    }
    startRanging();
    while(tmp==0){
        tmp = checkForDataReady();
        //Serial.println(tmp);
        delay(500);
    }
    tmp  = 0;
    clearInterrupt();
    stopRanging();
    writeByteData(VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND, 0x09); /* two bounds VHV */
    writeByteData(0x0B, 0);
    lastOperateStatus = eVL53L1X_ok;
    return true;
}
/*
void DFRobot_VL53L1X::setI2CAddress(uint8_t address)
{
    writeByteData(VL53L1_I2C_SLAVE__DEVICE_ADDRESS, address >> 1);
    _addr = address;
}

int DFRobot_VL53L1X::getI2CAddress()
{
    return _addr;
}
*/
void DFRobot_VL53L1X::clearInterrupt()
{
    writeByteData(SYSTEM__INTERRUPT_CLEAR, 0x01);
    //Serial.println("111111");
}

void DFRobot_VL53L1X::setInterruptPolarityHigh()
{
    setInterruptPolarity(1);
}

void DFRobot_VL53L1X::setInterruptPolarityLow()
{
    setInterruptPolarity(0);
}

void DFRobot_VL53L1X::setInterruptPolarity(uint8_t NewPolarity){
    uint8_t Temp;

    readByteData(GPIO_HV_MUX__CTRL, &Temp);
    Temp = Temp & 0xEF;
    writeByteData(GPIO_HV_MUX__CTRL, Temp | (!(NewPolarity & 1)) << 4);
}

/**
 * This function gets the interrupt polarity\n
 * 1=active high (default), 0=active low
 */

uint8_t DFRobot_VL53L1X::getInterruptPolarity()
{
    uint8_t Temp;
    uint8_t pInterruptPolarity;

    readByteData(GPIO_HV_MUX__CTRL, &Temp);
    //Serial.println(Temp);
    Temp = Temp & 0x10;
    pInterruptPolarity = !(Temp>>4);
    return pInterruptPolarity;
}

void DFRobot_VL53L1X::startRanging()
{
    writeByteData(SYSTEM__MODE_START, 0x40);
}

void DFRobot_VL53L1X::stopRanging()
{
    writeByteData(SYSTEM__MODE_START, 0x00);
}

bool DFRobot_VL53L1X::checkForDataReady()
{
    uint8_t Temp;
    uint8_t IntPol;
    uint8_t isDataReady;

    IntPol = getInterruptPolarity();
    //Serial.println(IntPol);
    readByteData(GPIO__TIO_HV_STATUS, &Temp);
    //Serial.println(Temp);
    delay(1);
    if ((Temp & 1) == IntPol)
        return  1;
    else
        return  0;
}

void DFRobot_VL53L1X::setTimingBudgetInMs(eTimingBudget timingBudget)
{
    uint16_t DM;

    DM = getDistanceMode();
    if (DM == 0)
        return;
    else if (DM == 1) {    /* Short DistanceMode */
        switch (timingBudget) {
        case 15: /* only available in short distance mode */
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x01D);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0027);
            break;
        case 20:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x0051);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x006E);
            break;
        case 33:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x00D6);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x006E);
            break;
        case 50:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x1AE);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x01E8);
            break;
        case 100:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x02E1);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0388);
            break;
        case 200:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x03E1);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0496);
            break;
        case 500:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x0591);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x05C1);
            break;
        default:
            break;
        }
    } else {
        switch (timingBudget) {
        case 20:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x001E);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0022);
            break;
        case 33:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x0060);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x006E);
            break;
        case 50:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x00AD);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x00C6);
            break;
        case 100:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x01CC);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x01EA);
            break;
        case 200:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x02D9);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x02F8);
            break;
        case 500:
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x048F);
            writeWordData(RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x04A4);
            break;
        default:
            break;
        }
    }
}

eTimingBudget DFRobot_VL53L1X::getTimingBudgetInMs()
{
    uint16_t Temp;
    eTimingBudget pTimingBudget;

    readWordData(RANGE_CONFIG__TIMEOUT_MACROP_A_HI, &Temp);
    switch (Temp) {
        case 0x0051 :
        case 0x001E :
            pTimingBudget = eBudget_20ms;
            break;
        case 0x00D6 :
        case 0x0060 :
            pTimingBudget = eBudget_33ms;
            break;
        case 0x1AE :
        case 0x00AD :
            pTimingBudget = eBudget_50ms;
            break;
        case 0x02E1 :
        case 0x01CC :
            pTimingBudget = eBudget_100ms;
            break;
        case 0x03E1 :
        case 0x02D9 :
            pTimingBudget = eBudget_200ms;
            break;
        case 0x0591 :
        case 0x048F :
            pTimingBudget = eBudget_500ms;
            break;
        default:
            pTimingBudget = eBudget_20ms;
            break;
    }
    return pTimingBudget;
}

void DFRobot_VL53L1X::setDistanceModeLong()
{
    setDistanceMode(2);
}

void DFRobot_VL53L1X::setDistanceModeShort()
{
    setDistanceMode(1);
}

void DFRobot_VL53L1X::setDistanceMode(uint16_t DM)
{
    eTimingBudget TB;

    TB = getTimingBudgetInMs();
    switch (DM) {
    case 1:
        writeByteData(PHASECAL_CONFIG__TIMEOUT_MACROP, 0x14);
        writeByteData(RANGE_CONFIG__VCSEL_PERIOD_A, 0x07);
        writeByteData(RANGE_CONFIG__VCSEL_PERIOD_B, 0x05);
        writeByteData(RANGE_CONFIG__VALID_PHASE_HIGH, 0x38);
        writeWordData(SD_CONFIG__WOI_SD0, 0x0705);
        writeWordData(SD_CONFIG__INITIAL_PHASE_SD0, 0x0606);
        break;
    case 2:
        writeByteData(PHASECAL_CONFIG__TIMEOUT_MACROP, 0x0A);
        writeByteData(RANGE_CONFIG__VCSEL_PERIOD_A, 0x0F);
        writeByteData(RANGE_CONFIG__VCSEL_PERIOD_B, 0x0D);
        writeByteData(RANGE_CONFIG__VALID_PHASE_HIGH, 0xB8);
        writeWordData(SD_CONFIG__WOI_SD0, 0x0F0D);
        writeWordData(SD_CONFIG__INITIAL_PHASE_SD0, 0x0E0E);
        break;
    default:
        break;
    }
    setTimingBudgetInMs(TB);
}

uint8_t DFRobot_VL53L1X::getDistanceMode()
{
    uint8_t TempDM;
    uint16_t DM;

    readByteData(PHASECAL_CONFIG__TIMEOUT_MACROP, &TempDM);
    if (TempDM == 0x14)
        DM=1;
    if(TempDM == 0x0A)
        DM=2;
    return DM;
}

void DFRobot_VL53L1X::setInterMeasurementInMs(uint16_t InterMeasMs)
{
    uint16_t ClockPLL;

    readWordData(VL53L1_RESULT__OSC_CALIBRATE_VAL, &ClockPLL);
    ClockPLL = ClockPLL & 0x3FF;
    writeWordData32(VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD, (uint32_t)(ClockPLL * InterMeasMs * 1.075));

}

uint16_t DFRobot_VL53L1X::getInterMeasurementInMs()
{
    uint16_t ClockPLL;
    uint16_t pIM;
    uint32_t tmp;
    

    readWordData32(VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD, &tmp);
    pIM = (uint16_t)tmp;
    readWordData(VL53L1_RESULT__OSC_CALIBRATE_VAL, &ClockPLL);
    ClockPLL = ClockPLL & 0x3FF;
    pIM= (uint16_t)(pIM/(ClockPLL*1.073));
    return pIM;
}

uint16_t DFRobot_VL53L1X::getDistance()
{
    uint16_t tmp;

    readWordData(VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0, &tmp);
    clearInterrupt();
    return tmp;
}
/*
uint16_t DFRobot_VL53L1X::getSignalPerSpad()
{
    uint16_t SpNb=1, signal;
    uint16_t signalRate;

    readWordData(VL53L1_RESULT__PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0, &signal);
    readWordData(VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0, &SpNb);
    signalRate = (uint16_t) (2000.0 * signal / SpNb);
    return signalRate;
}

uint16_t DFRobot_VL53L1X::getAmbientPerSpad()
{
    uint16_t AmbientRate, SpNb=1;
    uint16_t ambPerSp;

    readWordData(RESULT__AMBIENT_COUNT_RATE_MCPS_SD, &AmbientRate);
    readWordData(VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0, &SpNb);
    ambPerSp=(uint16_t) (2000.0 * AmbientRate / SpNb);
    return ambPerSp;
}
*/
uint16_t DFRobot_VL53L1X::getSignalRate()
{
    uint16_t tmp;

    readWordData(VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0, &tmp);
    tmp = tmp * 8;
    return tmp;
}

/*
uint16_t DFRobot_VL53L1X::getSpadNb()
{
    uint16_t tmp;

    readWordData(VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0, &tmp);
    tmp = tmp >> 8;
    return tmp;
}

uint16_t DFRobot_VL53L1X::getAmbientRate()
{
    uint16_t ambRate;
    uint16_t tmp;

    readWordData(RESULT__AMBIENT_COUNT_RATE_MCPS_SD, &tmp);
    ambRate = tmp*8;
    return ambRate;
}

uint8_t DFRobot_VL53L1X::getRangeStatus()
{
    uint8_t rangeStatus;
    uint8_t RgSt;

    readByteData(VL53L1_RESULT__RANGE_STATUS, &RgSt);
    RgSt = RgSt&0x1F;
    switch (RgSt) {
    case 9:
        RgSt = 0;
        break;
    case 6:
        RgSt = 1;
        break;
    case 4:
        RgSt = 2;
        break;
    case 8:
        RgSt = 3;
        break;
    case 5:
        RgSt = 4;
        break;
    case 3:
        RgSt = 5;
        break;
    case 19:
        RgSt = 6;
        break;
    case 7:
        RgSt = 7;
        break;
    case 12:
        RgSt = 9;
        break;
    case 18:
        RgSt = 10;
        break;
    case 22:
        RgSt = 11;
        break;
    case 23:
        RgSt = 12;
        break;
    case 13:
        RgSt = 13;
        break;
    default:
        RgSt = 255;
        break;
    }
    rangeStatus = RgSt;
    return rangeStatus;
}
*/
void DFRobot_VL53L1X::setOffset(int16_t OffsetValue)
{
    int16_t Temp;

    Temp = (OffsetValue*4);
    writeWordData(ALGO__PART_TO_PART_RANGE_OFFSET_MM, (uint16_t)Temp);
    writeWordData(MM_CONFIG__INNER_OFFSET_MM, 0x0);
    writeWordData(MM_CONFIG__OUTER_OFFSET_MM, 0x0);
}

int16_t DFRobot_VL53L1X::getOffset()
{
    int16_t offset;
    uint16_t Temp;

    readWordData(ALGO__PART_TO_PART_RANGE_OFFSET_MM, &Temp);
    Temp = Temp << 3;
    Temp = Temp >> 5;
    offset = (int16_t)(Temp);
    return offset;
}

void DFRobot_VL53L1X::setXTalk(uint16_t XtalkValue)
{
    writeWordData(ALGO__CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS, 0x0000);
    writeWordData(ALGO__CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS, 0x0000);
    writeWordData(ALGO__CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS, (XtalkValue<<9)/1000);
}

uint16_t DFRobot_VL53L1X::getXTalk()
{
    uint16_t xtalk;
    uint16_t tmp;

    readWordData(ALGO__CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS, &tmp);
    xtalk = (tmp*1000)>>9;
    return xtalk;
}

void DFRobot_VL53L1X::setDistanceThreshold(uint16_t ThreshLow, uint16_t ThreshHigh, eWindows Window)
{
    uint8_t Temp = 0;

    readByteData(SYSTEM__INTERRUPT_CONFIG_GPIO, &Temp);
    Temp = Temp & 0x47;

    //writeByteData(SYSTEM__INTERRUPT_CONFIG_GPIO, ((Temp | (Window & 0x07)) | 0x40));
    writeByteData(SYSTEM__INTERRUPT_CONFIG_GPIO, (Temp | (Window & 0x07)));
    writeWordData(SYSTEM__THRESH_HIGH, ThreshHigh);
    writeWordData(SYSTEM__THRESH_LOW, ThreshLow);
}

eWindows DFRobot_VL53L1X::getDistanceThresholdWindow()
{
    eWindows window;
    uint8_t tmp;
    readByteData(SYSTEM__INTERRUPT_CONFIG_GPIO, &tmp);
    window = (eWindows)(tmp & 0x7);
    return window;
}
uint16_t DFRobot_VL53L1X::getDistanceThresholdLow()
{
    uint16_t low;
    uint16_t tmp;

    readWordData(SYSTEM__THRESH_LOW, &tmp);
    low = tmp;
    return low;
}

uint16_t DFRobot_VL53L1X::getDistanceThresholdHigh()
{
    uint16_t high;
    uint16_t tmp;

    readWordData(SYSTEM__THRESH_HIGH, &tmp);
    high = tmp;
    return high;
}
/*
void DFRobot_VL53L1X::setROI(uint16_t X, uint16_t Y)
{
    uint8_t OpticalCenter;

    readByteData(VL53L1_ROI_CONFIG__MODE_ROI_CENTRE_SPAD, &OpticalCenter);
    if (X > 16)
        X = 16;
    if (Y > 16)
        Y = 16;
    if (X > 10 || Y > 10){
        OpticalCenter = 199;
    }
    writeByteData(ROI_CONFIG__USER_ROI_CENTRE_SPAD, OpticalCenter);
    writeByteData(ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE, (Y - 1) << 4 | (X - 1));
}

uint16_t DFRobot_VL53L1X::getROIX()
{
    uint8_t tmp;
    uint16_t ROI_X;

    readByteData(ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE, &tmp);
    ROI_X = ((uint16_t)tmp & 0x0F) + 1;
    return ROI_X;
}

uint16_t DFRobot_VL53L1X::getROIY()
{
    uint8_t tmp;
    uint16_t ROI_Y;

    readByteData(ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE, &tmp);
    ROI_Y = (((uint16_t)tmp & 0xF0) >> 4) + 1;
    return ROI_Y;
}

void DFRobot_VL53L1X::setSignalThreshold(uint16_t Signal)
{
    writeWordData(RANGE_CONFIG__MIN_COUNT_RATE_RTN_LIMIT_MCPS,Signal>>3);
}

uint16_t DFRobot_VL53L1X::getSignalThreshold()
{
    uint16_t signal;
    uint16_t tmp;

    readWordData(RANGE_CONFIG__MIN_COUNT_RATE_RTN_LIMIT_MCPS, &tmp);
    signal = tmp <<3;
    return signal;
}

void DFRobot_VL53L1X::setSigmaThreshold(uint16_t Sigma)
{
    if(Sigma>(0xFFFF>>2)){
        return 1;
    }
    writeWordData(RANGE_CONFIG__SIGMA_THRESH,Sigma<<2);
}

uint16_t DFRobot_VL53L1X::getSigmaThreshold()
{
    uint16_t sigma;
    uint16_t tmp;

    readWordData(RANGE_CONFIG__SIGMA_THRESH, &tmp);
    sigma = tmp >> 2;
    return sigma;

}

void DFRobot_VL53L1X::startTemperatureUpdate()
{
    uint8_t tmp=0;

    writeByteData(VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND,0x81);
    writeByteData(0x0B,0x92);
    startRanging();
    while(tmp==0){
        tmp = checkForDataReady();
        delay(500);
    }
    clearInterrupt();
    stopRanging();
    writeByteData(VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND, 0x09);
    writeByteData(0x0B, 0);
}
*/
int8_t DFRobot_VL53L1X::calibrateOffset(uint16_t targetDistInMm)
{
    int16_t offset = getOffset();
    uint8_t i = 0, tmp;
    int16_t AverageDistance = 0;
    uint16_t distance;

    writeWordData(ALGO__PART_TO_PART_RANGE_OFFSET_MM, 0x0);
    writeWordData(MM_CONFIG__INNER_OFFSET_MM, 0x0);
    writeWordData(MM_CONFIG__OUTER_OFFSET_MM, 0x0);
    startRanging();    /* Enable VL53L1X sensor */
    for (i = 0; i < 50; i++) {
        while (tmp == 0){
            tmp = checkForDataReady();
            Serial.println(tmp);
            delay(500);
        }
        distance = getDistance();
        clearInterrupt();
        AverageDistance = AverageDistance + distance;
    }
    stopRanging();
    AverageDistance = AverageDistance / 50;
    offset = targetDistInMm - AverageDistance;
    writeWordData(ALGO__PART_TO_PART_RANGE_OFFSET_MM, offset*4);
    return offset;
}

int8_t DFRobot_VL53L1X::calibrateXTalk(uint16_t targetDistInMm)
{
    uint16_t xTalk = getXTalk();
    uint8_t i, tmp= 0;
    float AverageSignalRate = 0;
    float AverageDistance = 0;
    float AverageSpadNb = 0;
    uint16_t distance = 0, spadNum;
    uint16_t sr;

    writeWordData(0x0016,0);
    startRanging();
    for (i = 0; i < 50; i++) {
        while (tmp == 0){
            tmp = checkForDataReady();
            delay(500);
        }
        sr = getSignalRate();
        distance = getDistance();
        clearInterrupt();
        AverageDistance = AverageDistance + distance;
        spadNum = getSignalRate();
        AverageSpadNb = AverageSpadNb + spadNum;
        AverageSignalRate =
            AverageSignalRate + sr;
    }
    stopRanging();
    AverageDistance = AverageDistance / 50;
    AverageSpadNb = AverageSpadNb / 50;
    AverageSignalRate = AverageSignalRate / 50;
    /* Calculate Xtalk value */
    xTalk = (uint16_t)(512*(AverageSignalRate*(1-(AverageDistance/targetDistInMm)))/AverageSpadNb);
    writeWordData(0x0016, xTalk);
    return xTalk;
}
/*
uint8_t DFRobot_VL53L1X::gesture(){
    int distance[1000];
    uint16_t time;
    int16_t speed;
    int i = 0;
    time = getInterMeasurementInMs();
    Serial.println(time);
    Serial.println(i);
    while (checkForDataReady() == true){
        distance[i] = getDistance();
        if(i > 0){
            speed = (distance[i] - distance[i - 1])/time;
            if(speed > 0){
                Serial.print("Target is go away ,speed is ");
                Serial.print(speed);
                Serial.println(" m/s");
            }else{
                Serial.print("Target is get closed ,speed is ");
                Serial.print(speed);
                Serial.println(" m/s");
            }
        }
        i++;
    }
}
*/
void DFRobot_VL53L1X::writeMulti(uint16_t index, uint8_t *pdata, uint32_t count)
{
    i2CWrite(index, pdata, (uint16_t)count);
}

void DFRobot_VL53L1X::readMulti(uint16_t index, uint8_t *pdata, uint32_t count)
{
    i2CRead(index, pdata, (uint16_t)count);
}


void DFRobot_VL53L1X::writeByteData(uint16_t index, uint8_t data)
{
    i2CWrite(index, &data, 1);
}

void DFRobot_VL53L1X::writeWordData(uint16_t index, uint16_t data)
{
    uint8_t buffer[2];

    buffer[0] = data >> 8;
    buffer[1] = data & 0x00FF;
    i2CWrite(index, (uint8_t *)buffer, 2);
}

void DFRobot_VL53L1X::writeWordData32(uint16_t index, uint32_t data)
{
    uint8_t buffer[4];

    buffer[0] = (data >> 24) & 0xFF;
    buffer[1] = (data >> 16) & 0xFF;
    buffer[2] = (data >>  8) & 0xFF;
    buffer[3] = (data >>  0) & 0xFF;
    i2CWrite(index, (uint8_t *)buffer, 4);
}


void DFRobot_VL53L1X::readByteData(uint16_t index, uint8_t *data)
{
    i2CRead(index, data, 1);
}

void DFRobot_VL53L1X::readWordData(uint16_t index, uint16_t *data)
{
    uint8_t buffer[2] = {0,0};
    
    i2CRead(index, buffer, 2);

    *data = (buffer[0] << 8) + buffer[1];
}

void DFRobot_VL53L1X::readWordData32(uint16_t index, uint32_t *data)
{
   uint8_t buffer[4] = {0,0,0,0};

   i2CRead(index, buffer, 4);
   *data = (buffer[0] << 24) + (buffer[1] << 16) + (buffer[2] << 8) + buffer[3];
}

void DFRobot_VL53L1X::i2CWrite(uint16_t reg, uint8_t *pBuf, uint16_t len)
{
    lastOperateStatus = eVL53L1X_WriteRegError;
    _pWire->begin();
    _pWire->beginTransmission(addr);
    uint8_t buffer[2];
    buffer[0]=(uint8_t) reg>>8;
    buffer[1]=(uint8_t) reg&0xFF;
    _pWire->write(buffer, 2);
    for(uint16_t i = 0; i < len; i ++)
        _pWire->write(pBuf[i]);
    _pWire->endTransmission();
    lastOperateStatus = eVL53L1X_ok;
}

void DFRobot_VL53L1X::i2CRead(uint16_t reg, uint8_t *pBuf, uint16_t len)
{
    lastOperateStatus = eVL53L1X_ReadRegError;
    _pWire->begin();
    _pWire->beginTransmission(addr);
    uint8_t buffer[2];
    buffer[0]=(uint8_t) reg >> 8;
    buffer[1]=(uint8_t) reg & 0xFF;
    _pWire->write(buffer, 2);
    if(_pWire->endTransmission() != 0)
        return;
    _pWire->requestFrom(addr, (uint8_t) len);
    for(uint16_t i = 0; i < len; i ++) {
        pBuf[i] = _pWire->read();
    }
    _pWire->endTransmission();
    lastOperateStatus = eVL53L1X_ok;
}
