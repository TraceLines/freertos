/*
 * @Author: king jing
 * @Date: 2022-11-23 10:31:35
 * @LastEditTime: 2022-11-23 16:27:24
 * @Description: Do not edit
 */

/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
/*外设文件*/
#include "bsp_usart.h"
// --------------页面级变量声明--------------------
#define mainDELAY_LOOP_COUNT 100000
static int task1FlagRun = 0;
static int task2FlagRun = 0;
static int task3FlagRun = 0;

// --------------函数声明--------------------
static void BSP_Init(void);

static void vtask1(void);
static void vtask2(void);
static void vtask3(void);
// --------------任务句柄--------------------
static TaskHandle_t task1_handle;
static TaskHandle_t task2_handle;
static TaskHandle_t task3_handle;

// 队列句柄
static QueueHandle_t xQueueCalcHandle;
int main(void)
{
  BaseType_t xReturn = pdPASS;
  /* 开发板硬件初始化 */
  BSP_Init();
  printf("test,uart test!");

  // 创建任务
  xReturn = xTaskCreate((TaskFunction_t)vtask1, "task1", 100, NULL, 1, &task1_handle);
  xReturn = xTaskCreate((TaskFunction_t)vtask2, "task2", 100, NULL, 1, &task2_handle);
  xReturn = xTaskCreate((TaskFunction_t)vtask3, "task3", 100, NULL, 1, &task3_handle);
  // 队列创建
  xQueueCalcHandle = xQueueCreate(5, sizeof(int));

  /* 启动任务调度 */
  if (pdPASS == xReturn)
    vTaskStartScheduler(); /* 启动任务，开启调度 */
  else
    return -1;
  printf("test,uart test!999999999999\n");
  while (1)
  {
  }
}

//---------------------------- 任务函数-------------------------
void vtask1(void)
{
  while (1)

  {
    printf("1");
    task1FlagRun = 1;
    task2FlagRun = 0;
    task3FlagRun = 0;
    // for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++)
    // {
    // }
  }
}

void vtask2(void)
{
  while (1)
  {
    printf("2");
    task1FlagRun = 0;
    task2FlagRun = 1;
    task3FlagRun = 0;
  }
}

void vtask3(void)
{
  while (1)
  {
    printf("3");
    task1FlagRun = 0;
    task2FlagRun = 0;
    task3FlagRun = 1;
  }
}

void BSP_Init(void)
{
  /*
   * STM32中断优先级分组为4，即4bit都用来表示抢占优先级，范围为：0~15
   * 优先级分组只需要分组一次即可，以后如果有其他的任务需要用到中断，
   * 都统一用这个优先级分组，千万不要再分组，切忌。
   */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  /* LED 初始化 */
  // LED_GPIO_Config();

  /* 串口初始化	*/
  USART_Config();

  /* 按键初始化	*/
  // Key_GPIO_Config();
}
