#ifndef ZSHELLCOMMANDS
#define ZSHELLCOMMANDS
#include <Arduino.h>

void free(int argc, char *argv)
{
     Serial.println("Free memory: " + String(esp_get_free_heap_size()) + " bytes");
}

void sysinfo(int argc, char *argv)
{
     uint32_t chipId = 0;

     for (int i = 0; i < 17; i = i + 8)
     {
          chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
     }

     Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
     Serial.printf("This chip has %d cores\n", ESP.getChipCores());
     Serial.print("Chip ID: ");
     Serial.println(chipId);

     uint32_t Freq = getCpuFrequencyMhz();
     Serial.print("CPU Freq = ");
     Serial.print(Freq);
     Serial.println(" MHz");
     Freq = getXtalFrequencyMhz();
     Serial.print("XTAL Freq = ");
     Serial.print(Freq);
     Serial.println(" MHz");
     Freq = getApbFrequency();
     Serial.print("APB Freq = ");
     Serial.print(Freq);
     Serial.println(" Hz");
}

#endif