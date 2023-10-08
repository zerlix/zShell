#ifndef ZSHELLCOMMANDS
#define ZSHELLCOMMANDS
#include <Arduino.h>

void free(int argc, char *argv)
{
     Serial.println("Free memory: " + String(esp_get_free_heap_size()) + " bytes");
}

/**
 * @brief: gibt systeminformationen aus
 **/
void sysinfo(int argc, char *argv)
{
     

     // Chipmodel
     uint32_t chipId = 0;
     for (int i = 0; i < 17; i = i + 8)
     {
          chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
     }
     Serial.printf("Chip model   :\t %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
     Serial.printf("Anzahl Kerne :\t %d \n", ESP.getChipCores());
     Serial.printf("Chip ID      :\t %d \n", chipId);
     Serial.printf("CPU Freq.    :\t %d \n Mhz", ESP.getCpuFreqMHz());
     Serial.printf("Max  DRAM    :\t %d \n Byte", ESP.getHeapSize());
     Serial.printf("Free DRAM    :\t %d \n Byte", ESP.getFreeHeap());
     Serial.printf("Max  PSRAM   :\t %d \n Byte", ESP.getPsramSize());
     Serial.printf("Free PSRAM   :\t %d \n Byte", ESP.getFreePsram());
}

#endif