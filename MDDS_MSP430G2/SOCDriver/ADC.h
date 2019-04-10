/*
 * ADC.h
 *
 *  Created on: 2019年2月8日
 *      Author: asdf2
 */

#ifndef SOCDRIVER_ADC_H_
#define SOCDRIVER_ADC_H_
//ADC参考源设置
enum e_ADCReference{

//VR+ = VCC and VR- = VSS
    VCC_GND,
//VR+ = VREF+ and VR- = VSS
    VREF_GND,
//VR+ = VeREF+ and VR- = VSS. Devices with VeREF+ only.
    VEREF_GND,
//VR+ = Buffered VeREF+ and VR- = VSS. Devices with VeREF+ pin only.
    BufferedVREF_GND,
//VR+ = VCC and VR- = VREF-/ VeREF-. Devices with VeREF- pin only.
    VCC_VREF,
//VR+ = VREF+ and VR- = VREF-/ VeREF-. Devices with VeREF+/- pins only.
    VREF_VREF,
//VR+ = VeREF+ and VR- = VREF-/ VeREF-. Devices with VeREF+/- pins only.
    VEREF_VREF,
//VR+ = Buffered VeREF+ and VR- = VREF-/ VeREF-. Devices with VeREF+/- pins only.
    BufferedVREF_VREF
};
//ADC采样速率
enum e_ADCSamplingTime{
    //00 4 × ADC10CLKs
    ADCCLK4,
    //01 8 × ADC10CLKs
    ADCCLK8,
    //10 16 × ADC10CLKs
    ADCCLK16,
    //11 64 × ADC10CLKs
    ADCCLK64,

};
//ADC最大采样速率，调整功耗用
enum e_ADCSamplingRate{
    //0 Reference buffer supports up to ~200 ksps
    ADC200KSPS,
    //1 Reference buffer supports up to ~50 ksps
    ADC50KSPS
};
//参考电源值
enum e_ADCVRef
{
    //1.5V
    ADC1500MV,
    //2.5V
    ADC2500MV
};
//ADC时钟源选择
enum e_ADCClkSource
{
    ADC_OSC,
    ADC_ACLK,
    ADC_MCLK,
    ADC_SMCLK
};
//ADC初始化
void ADCInit();
//ADC启动
//参数：
//  const INT8S *pSequence：转换序列指针，指向数组，数组为转换通道，-1代表数组结束
//  INT16U *dat：指向存放转换结果的指针
//返回：
//  BL：指示转换是否完成
//注意：这个函数几乎包含了所有功能，可以反复调用以查询，若返回1，则在下一次调用时再次启动转换
BL ADCStart(const INT8S *pSequence,INT16U *dat);


#endif /* SOCDRIVER_ADC_H_ */
