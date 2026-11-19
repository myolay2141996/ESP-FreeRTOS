#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"

gpio_num_t led = GPIO_NUM_5;
gpio_num_t button=GPIO_NUM_12;

SemaphoreHandle_t Switch_state;

void pin_configuration()
{
    gpio_config_t output = {
        .pin_bit_mask = (1ULL << led),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&output);

    gpio_config_t input = {
        .pin_bit_mask = (1ULL << button),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&input);
}

void Button(void *pvParameters)
{
  bool current=0;
  bool last=0;
  while(1){
    current = gpio_get_level(button);
    if(current&&!last){
      xSemaphoreGive(Switch_state);
    }
    last=current;
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void led_function(void *pvParameters)
{
    bool led_state = false;
    while(1)
    {
      if(xSemaphoreTake(Switch_state, portMAX_DELAY))
        {
            led_state = !led_state;
            gpio_set_level(led, led_state);
      }
    }
}

void app_main(void)
{
  pin_configuration();
  Switch_state = xSemaphoreCreateBinary();
  if (Switch_state == NULL)
    {
        printf("Semaphore Create Failed!\n");
        return;
    }
  xTaskCreate(Button,"OnOffButton",2048,NULL,10,NULL);
  xTaskCreate(led_function,"led",2048,NULL,5,NULL);  
} 

     