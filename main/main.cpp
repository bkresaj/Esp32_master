#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "gatts_server.c"
#include <mpu6050.hpp>
#include "joystick_algorithm.h"

extern "C" {
	void app_main(void);
}

void sending_task(void * pvParameters){
    float x,y;
    char acc_data[5];
    uint8_t sending_data[5];
    data_to_send_t data_to_send;
    
    MPU6050 mpu(GPIO_NUM_22, GPIO_NUM_21, I2C_NUM_0);
    mpu.acc_init();
    ble_init();
    
    while(1){
    x= -mpu.getAccX();
    y= -mpu.getAccY();

    printf("%f %f\n",x,y);

    data_to_send = joystick_algorithm(x, y);

    sprintf(acc_data, "%d%d",data_to_send.mode, data_to_send.angle);
    for(int i = 0; i < 5;i ++){
        sending_data[i]= acc_data[i];
    }
    esp_ble_gatts_send_indicate(_global_gatt_if, _global_conn_id, _global_att_handle, 5, sending_data, false);

    vTaskDelay(pdMS_TO_TICKS(200));

    }
}

extern "C" void app_main()
{   
    xTaskCreatePinnedToCore(sending_task,"sending_task",2048*4,NULL,5,NULL,0);
}

