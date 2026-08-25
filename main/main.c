#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "pote.h"
#include "as5600.h"

static const char *TAG = "app";

void app_main(void)
{
    ESP_ERROR_CHECK(pote_init());
    ESP_LOGI(TAG, "Pote inicializado");

    if (as5600_init() != ESP_OK) {
        ESP_LOGE(TAG, "Fallo la inicializacion del AS5600");
        return;
    }

    as5600_escanear_bus();

    while (1) {
        as5600_muestra_t a;
        if (as5600_leer(&a) == ESP_OK) {
            ESP_LOGI(TAG,
                     "AS5600  raw=%4u (%6.2f deg)  angle=%4u (%6.2f deg)  "
                     "MD=%d ML=%d MH=%d  agc=%3u  mag=%4u",
                     a.raw_angle, a.grados_raw, a.angle, a.grados,
                     a.md, a.ml, a.mh, a.agc, a.magnitud);
        } else {
            ESP_LOGW(TAG, "AS5600  lectura fallida");
        }

        pote_muestra_t p;
        pote_leer(&p);
        ESP_LOGI(TAG, "Pote    raw=%4d  mV=%4d  ref=%4d  ang=%6.1f deg",
                 p.raw_senal, p.mv_senal, p.mv_ref, p.grados);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
