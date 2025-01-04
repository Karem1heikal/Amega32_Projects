/*
 * main.c
 *
 *  Created on: Dec 17, 2024
 *      Author: user
 */

#define PRIORITY_INHERETANCE  	1
#define PRIORITY_CEILING  		1

#if PRIORITY_INHERETANCE == 1
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// Mutex handle
xSemaphoreHandle xMutex;

// High priority task
void HighPriorityTask(void *pvParameters) {
    while (1) {
        // Try to take the mutex
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdPASS) {
            // Perform operations
            // Release the mutex
            xSemaphoreGive(xMutex);
        }
    }
}

// Medium priority task
void MediumPriorityTask(void *pvParameters) {
    while (1) {
        // Perform operations that take a long time
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Low priority task
void LowPriorityTask(void *pvParameters) {
    while (1) {
        // Take the mutex
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdPASS) {
            // Perform operations
            vTaskDelay(pdMS_TO_TICKS(5000)); // Simulate long operation
            // Release the mutex
            xSemaphoreGive(xMutex);
        }
    }
}

int main() {
    // Create the mutex
    xMutex = xSemaphoreCreateMutex();

    // Create tasks
    xTaskCreate(HighPriorityTask, "HighPriorityTask", 1000, NULL, 3, NULL);
    xTaskCreate(MediumPriorityTask, "MediumPriorityTask", 1000, NULL, 2, NULL);
    xTaskCreate(LowPriorityTask, "LowPriorityTask", 1000, NULL, 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    for (;;) {}

    return 0;
}
#endif
#if PRIORITY_INHERETANCE == 0

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// Mutex handle
xSemaphoreHandle xMutex;

// High priority task
void HighPriorityTask(void *pvParameters) {
    while (1) {
        // Try to take the mutex
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdPASS) {
            // Perform operations
            // Release the mutex
            xSemaphoreGive(xMutex);
        }
    }
}

// Medium priority task
void MediumPriorityTask(void *pvParameters) {
    while (1) {
        // Perform operations that take a long time
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Low priority task
void LowPriorityTask(void *pvParameters) {
    while (1) {
        // Take the mutex
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdPASS) {
            // Perform operations
            vTaskDelay(pdMS_TO_TICKS(5000)); // Simulate long operation
            // Release the mutex
            xSemaphoreGive(xMutex);
        }
    }
}

int main() {
    // Create the mutex with priority inheritance
    xMutex = xSemaphoreCreateMutex();

    // Create tasks
    xTaskCreate(HighPriorityTask, "HighPriorityTask", 1000, NULL, 3, NULL);
    xTaskCreate(MediumPriorityTask, "MediumPriorityTask", 1000, NULL, 2, NULL);
    xTaskCreate(LowPriorityTask, "LowPriorityTask", 1000, NULL, 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    for (;;) {}

    return 0;
}
#endif

#if PRIORITY_CEILING == 1
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// Mutex handle
xSemaphoreHandle xSem;

// High priority task
void HighPriorityTask(void *pvParameters) {
    while (1) {
        // Try to take the mutex
        if (xSemaphoreTake(xSem, portMAX_DELAY) == pdPASS) {
            // Perform operations
            // Release the mutex
            xSemaphoreGive(xSem);
        }
    }
}

// Medium priority task
void MediumPriorityTask(void *pvParameters) {
    while (1) {
        // Perform operations that take a long time
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Low priority task
void LowPriorityTask(void *pvParameters) {
    while (1) {
        // Raise priority to the ceiling level before taking the mutex
        u8 originalPriority = uxTaskPriorityGet(NULL);
        vTaskPrioritySet(NULL, 3); // Set to the highest priority that will use the mutex

        // Take the mutex
        if (xSemaphoreTake(xSem, portMAX_DELAY) == pdPASS) {
            // Perform operations
            vTaskDelay(pdMS_TO_TICKS(5000)); // Simulate long operation
            // Release the mutex
            xSemaphoreGive(xSem);
        }

        // Restore original priority after releasing the mutex
        vTaskPrioritySet(NULL, originalPriority);
    }
}

int main() {
    // Create the mutex
	xSem = xSemaphoreCreateCounting(1,0);

    // Create tasks
    xTaskCreate(HighPriorityTask, "HighPriorityTask", 1000, NULL, 3, NULL);
    xTaskCreate(MediumPriorityTask, "MediumPriorityTask", 1000, NULL, 2, NULL);
    xTaskCreate(LowPriorityTask, "LowPriorityTask", 1000, NULL, 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    for (;;) {}

    return 0;
}
#endif
