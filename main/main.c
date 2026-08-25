#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "pote.h"

static const char *TAG = "app";

void app_main(void)
{
    ESP_ERROR_CHECK(pote_init());
    ESP_LOGI(TAG, "Pote inicializado");

    while (1) {
        pote_muestra_t m;
        pote_leer(&m);
        ESP_LOGI(TAG, "raw=%4d  mV=%4d  ref=%4d  ang=%6.1f deg",
                 m.raw_senal, m.mv_senal, m.mv_ref, m.grados);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
