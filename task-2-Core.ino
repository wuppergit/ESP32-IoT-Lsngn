/**
 * arbeiten mit FreeRTOS    
 */
#include <Arduino.h>
TaskHandle_t task_handle_1;
TaskHandle_t task_handle_2;

// Task Codes
void task_code_1 ( void * pvParameters ){
  Serial.print  ("Task1 ausgefuehrt in Kern ");
  Serial.println(xPortGetCoreID());

  for(;;){
    Serial.println("Meldung von Task1");
    delay(2000);
  } 
}

void task_code_2( void * pvParameters ){
  Serial.print  ("Task2 ausgefuehrt in Kern ");
  Serial.println(xPortGetCoreID());

  for(;;){
    Serial.println("Meldung von       Task2");
    delay(1000);
  }
}

void setup() {
  Serial.begin(115200); 
  delay (100);                           // warten Serial o.k.

  Serial.print  ("Anzahl Tasks vor Create Tasks  ");             
  Serial.println(uxTaskGetNumberOfTasks()); 
  //create a task that will be executed in the Thread1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    task_code_1,         // Task function. 
                    "Task1",             // name of task. 
                    10000,               // Stack size of task 
                    NULL,                // parameter of the task 
                    1,                   // priority of the task 
                    &task_handle_1,      // Task handle to keep track of created task 
                    0);                  // pin task to core 0              
  delay(500); 

  //create a task that will be executed in the Thread2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    task_code_2,         // Task function. 
                    "Task2",             // name of task. 
                    10000,               // Stack size of task 
                    NULL,                // parameter of the task
                    1,                   // priority of the task 
                    &task_handle_2,      // Task handle to keep track of created task /
                    1);                  // pin task to core 1 
  delay(500); 
  Serial.print  ("Anzahl Tasks nach Create Tasks  ");             
  Serial.println(uxTaskGetNumberOfTasks());     
}


void loop() {
  delay(10000);  
}
