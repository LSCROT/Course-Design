#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"
#include "AD.h"

int main(void)
{
	uint16_t AD0;	//定义AD值变量
	float temperature,a,b,r,N1,N2,N3,N4;
	
	/*模块初始化*/
	Buzzer_Init();			//蜂鸣器初始化
	LightSensor_Init();		//光敏传感器初始化
	OLED_Init();		//OLED初始化
	AD_Init();					//AD初始化
	
	/*OLED显示*/	
	OLED_ShowString(1, 3, "Terminal");	//1行3列显示字符串HelloWorld!

	OLED_ShowString(2, 1, "Temperature:");
	
	while (1)
	{
		if (LightSensor_Get() == 1)		//如果当前光敏输出1
		{
			Buzzer_ON();				//蜂鸣器开启
		}
		else							//否则
		{
			Buzzer_OFF();				//蜂鸣器关闭
		}
		
		AD0 = AD_GetValue();	//单次启动ADC，转换通道0
		a=(float)(AD0 * 3.3)/ 4095; 
		b=3.3-a;
		r=(a/b)*10;//内阻测量
		N1 = (10-r)/2500;
		N2 = 1/298.15 - N1;
		N3 = 1/N2;
		N4 = N3-273.15;//开尔文转摄氏度
		temperature=N4/5;
		OLED_ShowNum(3, 3, temperature, 4);				//显示通道0的转换结果AD0
		Delay_ms(100);			//延时100ms，手动增加一些转换的间隔时间
	}
}
