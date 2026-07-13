#include "motor.h"

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
extern SPI_HandleTypeDef hspi1;

extern uint8_t rxData[2];

void motor_Init(uint8_t enable,uint8_t num) //电机工作模式
{
        if(enable) //正常工作
        {
            if(num==1) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);  //86
            if(num==2) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);  //57
            if(num==3) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //57_2
        }else     //低功耗
        {
            if(num==1) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
            if(num==2) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
            if(num==3) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
        }
}
void motor_enable(uint8_t enable,uint8_t num)  //电机使能/禁用
{
    if(enable) //正常工作
        {
            if(num==1) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);  //86
            if(num==2) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);  //57
            if(num==3) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET); //57_2
            if(num==4) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); //42
        }else 
        {
            if(num==1) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
            if(num==2) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            if(num==3) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
            if(num==4) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); 
        }
   
}
void motor_DIR(uint8_t dir,uint8_t num)  //电机转向
{
    if(dir) //正转
        {
            if(num==1) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);  //86
            if(num==2) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);  //57_2
            if(num==3) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); //57_2
            if(num==4) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); //42
        }else     //反转
        {
            if(num==1) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
            if(num==2) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
            if(num==3) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
            if(num==4) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); //42
        }
}

void motor_pwm_set(uint8_t num,int duty)  //PWM设置
{
    if(num==4){HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    __HAL_TIM_SET_AUTORELOAD(&htim4,duty);
    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,duty/2);
}
    else if(num==3){
	  // 1. 先设置频率和占空比
    __HAL_TIM_SET_AUTORELOAD(&htim1, duty);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, duty / 2);
    // 2. 再开启输出（CH3 + CH3N 都要开）
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);        // 开启 CH3
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);     // 开启 CH3N
    }
    else if(num==2){
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    __HAL_TIM_SET_AUTORELOAD(&htim2,duty);
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,duty/2);
    }
    else if(num==1){
    __HAL_TIM_SET_AUTORELOAD(&htim5,duty);
    __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,duty/2);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
    }
}

void NCS_ENABLE(uint8_t enable)  //NCS使能/禁用
{
    if(enable==3) //正常工作
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);  //NCS_57_2
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
    }else if(enable==2)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);  
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);  //NCS_57
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
    }else if(enable==1)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);  
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);  //NCS_86
    }else{
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);  
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
    }
   
}
  // 写寄存器
void DRV8462_WriteReg(uint8_t Enable,uint8_t addr, uint8_t data)
{
      uint16_t txData = ((uint16_t)addr << 8) | data;  // 命令 + 数据
      uint16_t rxBuffer;

      NCS_ENABLE(Enable);
      HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&txData, (uint8_t*)&rxBuffer, 1, HAL_MAX_DELAY);
	 // 等 SCLK 稳定后再拉高 CS（DRV8462 需要最后一位锁存时间）
      for(volatile int i = 0; i < 10; i++);  // 约 100ns @ 72MHz
      NCS_ENABLE(0);
      HAL_Delay(1);   // 帧间隔
}

void MySPI_SwapByte(uint8_t Enable)
{
	uint16_t txData[1]={0x4000};     //0x4000 读故障寄存器
	
    NCS_ENABLE(Enable);
    HAL_SPI_TransmitReceive(&hspi1, (uint8_t *)txData, (uint8_t*)rxData, 1,HAL_MAX_DELAY);
	 // 等 SCLK 稳定后再拉高 CS（DRV8462 需要最后一位锁存时间）
      for(volatile int i = 0; i < 10; i++);  // 约 100ns @ 72MHz
    NCS_ENABLE(0);
	
    HAL_Delay(1);                // 保证帧间 nSCS ≥ 500ns
	
}
