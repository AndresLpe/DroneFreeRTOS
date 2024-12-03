# DroneFreeRTOS
Código para dron con FreeRTOS utilizando STM32 Nucleo-F303RE

## Task Description

### **Overview**
Este proyecto implementa un sistema para un dron basado en FreeRTOS en una STM32 Nucleo-F303RE. A continuación, se describen las tareas implementadas, su periodicidad, tipo de ejecución (por mensaje, interrupción o bucle continuo), y qué sucede tras su ejecución.

### **Tareas y características**
1. **Configuración Inicial:**
   - **Periodicidad:** Ejecución única al inicio del sistema.
   - **Tipo de ejecución:** Evento basado en entrada del usuario (botón presionado).
   - **Flujo tras ejecución:** Habilita las tareas de control para iniciar el vuelo.
   - **Código asociado:** [tareaConfiguracionInicial](./main.c#L12-L28).

2. **Control de Estabilización:**
   - **Periodicidad:** Ejecuta cada 10 ms.
   - **Tipo de ejecución:** Bucle continuo con `vTaskDelay`.
   - **Flujo tras ejecución:** Calcula correcciones de inclinación y ajusta los motores.
   - **Código asociado:** [tareaControlEstabilizacion](./main.c#L30-L44).

3. **Control de Altura:**
   - **Periodicidad:** Ejecuta cada 20 ms.
   - **Tipo de ejecución:** Bucle continuo con `vTaskDelay`.
   - **Flujo tras ejecución:** Ajusta la potencia de los motores para mantener la altitud.
   - **Código asociado:** [tareaControlAltura](./main.c#L46-L59).

4. **Monitoreo y Seguridad:**
   - **Periodicidad:** Ejecuta cada 100 ms.
   - **Tipo de ejecución:** Bucle continuo con `vTaskDelay`.
   - **Flujo tras ejecución:** Evalúa condiciones críticas y, si es necesario, detiene las demás tareas.
   - **Código asociado:** [tareaMonitoreoSeguridad](./main.c#L61-L71).

5. **Finalización:**
   - **Periodicidad:** Ejecución única tras completarse el tiempo de vuelo.
   - **Tipo de ejecución:** Temporizador interno.
   - **Flujo tras ejecución:** Realiza el aterrizaje y apaga los motores.
   - **Código asociado:** [tareaFinalizacion](./main.c#L73-L81).

### **Diagrama de flujo**
Incluye un diagrama de flujo general que describe el comportamiento del sistema desde la configuración inicial hasta el aterrizaje.

### **Código adicional**
Las funciones auxiliares para leer sensores, calcular PID y manejar motores están implementadas en el archivo [main.c](./main.c).
