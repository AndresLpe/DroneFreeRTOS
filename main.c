//code freeRTOS:
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "stm32f3xx_hal.h"

// Variables globales
float altura_deseada = 0.0;
int tiempo_vuelo = 0;

// Declaración de tareas
void tareaConfiguracionInicial(void *pvParameters);
void tareaControlEstabilizacion(void *pvParameters);
void tareaControlAltura(void *pvParameters);
void tareaMonitoreoSeguridad(void *pvParameters);
void tareaFinalizacion(void *pvParameters);

// Función principal
int main(void) {
    HAL_Init();
    SystemClock_Config();

    // Crear tareas
    xTaskCreate(tareaConfiguracionInicial, "ConfiguracionInicial", 128, NULL, 1, NULL);
    xTaskCreate(tareaControlEstabilizacion, "ControlEstabilizacion", 256, NULL, 2, NULL);
    xTaskCreate(tareaControlAltura, "ControlAltura", 256, NULL, 2, NULL);
    xTaskCreate(tareaMonitoreoSeguridad, "MonitoreoSeguridad", 128, NULL, 1, NULL);
    xTaskCreate(tareaFinalizacion, "Finalizacion", 128, NULL, 1, NULL);

    // Iniciar el scheduler
    vTaskStartScheduler();

    while (1) {
    }
}

// Implementación de tareas
void tareaConfiguracionInicial(void *pvParameters) {
    // Simular recepción de datos
    altura_deseada = 1.5; // Altura en metros
    tiempo_vuelo = 30;    // Tiempo en segundos

    // Espera que el botón sea presionado
    printf("Configuración inicial completada. Presione el botón para iniciar...\n");
    while (!botonPresionado()) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    printf("Botón presionado. Iniciando cuenta regresiva...\n");
    vTaskDelay(pdMS_TO_TICKS(10000)); // Espera de 10 segundos antes del vuelo

    vTaskDelete(NULL); // Finaliza la tarea
}

void tareaControlEstabilizacion(void *pvParameters) {
    while (1) {
        float pitch, roll, yaw;

        // Leer datos del sensor MPU6050
        leerMPU6050(&pitch, &roll, &yaw);

        // Aplicar control PID para estabilización
        float correccion_pitch = calcularPID(pitch, 0.0);
        float correccion_roll = calcularPID(roll, 0.0);

        // Ajustar motores
        ajustarMotores(correccion_pitch, correccion_roll);

        vTaskDelay(pdMS_TO_TICKS(10)); // Frecuencia alta
    }
}

void tareaControlAltura(void *pvParameters) {
    while (1) {
        float altura_actual = leerSensorAltura();

        // Aplicar control PID para altura
        float correccion_altura = calcularPID(altura_actual, altura_deseada);

        // Ajustar la potencia de los motores
        ajustarAltura(correccion_altura);

        vTaskDelay(pdMS_TO_TICKS(20)); // Frecuencia moderada
    }
}

void tareaMonitoreoSeguridad(void *pvParameters) {
    while (1) {
        // Verificar condiciones críticas
        if (condicionEmergencia()) {
            printf("Condición de emergencia detectada. Iniciando aterrizaje...\n");
            aterrizar();
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Frecuencia baja
    }
    vTaskDelete(NULL); // Finaliza la tarea
}

void tareaFinalizacion(void *pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(tiempo_vuelo * 1000)); // Esperar el tiempo configurado
    printf("Tiempo de vuelo completado. Iniciando aterrizaje...\n");
    aterrizar();
    vTaskDelete(NULL); // Finaliza la tarea
}

// Funciones auxiliares simuladas
int botonPresionado() {
    // Simula que el botón ha sido presionado
    return 1;
}

void leerMPU6050(float *pitch, float *roll, float *yaw) {
    // Simula lectura del MPU6050
    *pitch = 0.0;
    *roll = 0.0;
    *yaw = 0.0;
}

float leerSensorAltura() {
    // Simula lectura del sensor infrarrojo
    return 1.5; // Altura en metros
}

float calcularPID(float valor_actual, float valor_deseado) {
    // Simula un cálculo básico de PID
    return valor_deseado - valor_actual;
}

void ajustarMotores(float pitch, float roll) {
    // Simula el ajuste de motores
}

void ajustarAltura(float correccion) {
    // Simula el ajuste de altura
}

void aterrizar() {
    // Simula el aterrizaje seguro del dron
    printf("Aterrizaje completado.\n");
}

int condicionEmergencia() {
    // Simula la verificación de condiciones críticas
    return 0;
}




