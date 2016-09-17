#include "BlackGPIO.h"
#include <unistd.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <random>

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"

int readAnalog(int number){
   std::stringstream ss;
   ss << PATH_ADC << number << "_raw";
   std::fstream fs;
   fs.open(ss.str().c_str(), std::fstream::in);
   fs >> number;
   fs.close();
   return number;
}

void red_light(BlackLib::BlackGPIO (&rgb_led)[3]) {
    rgb_led[0].setValue(BlackLib::high);
    rgb_led[1].setValue(BlackLib::low);
    rgb_led[2].setValue(BlackLib::low);
}

void green_light(BlackLib::BlackGPIO (&rgb_led)[3]) {
    rgb_led[0].setValue(BlackLib::low);
    rgb_led[1].setValue(BlackLib::high);
    rgb_led[2].setValue(BlackLib::low);
}

void blue_light(BlackLib::BlackGPIO (&rgb_led)[3]) {
    rgb_led[0].setValue(BlackLib::low);
    rgb_led[1].setValue(BlackLib::low);
    rgb_led[2].setValue(BlackLib::high);
}

void white_light(BlackLib::BlackGPIO (&rgb_led)[3]) {
    rgb_led[0].setValue(BlackLib::high);
    rgb_led[1].setValue(BlackLib::high);
    rgb_led[2].setValue(BlackLib::high);
}

void yellow_light(BlackLib::BlackGPIO (&rgb_led)[3]) {
    rgb_led[0].setValue(BlackLib::high);
    rgb_led[1].setValue(BlackLib::high);
    rgb_led[2].setValue(BlackLib::low);
}

void pink_light(BlackLib::BlackGPIO (&rgb_led)[3]) {
    rgb_led[0].setValue(BlackLib::high);
    rgb_led[1].setValue(BlackLib::low);
    rgb_led[2].setValue(BlackLib::high);
}

void cyan_light(BlackLib::BlackGPIO (&rgb_led)[3]) {
    rgb_led[0].setValue(BlackLib::low);
    rgb_led[1].setValue(BlackLib::high);
    rgb_led[2].setValue(BlackLib::high);
}

int main(int argc, char *argv[]) {
    // Button
    BlackLib::BlackGPIO button(BlackLib::GPIO_115, BlackLib::input, BlackLib::SecureMode);

    // Status Led
    BlackLib::BlackGPIO statusLed(BlackLib::GPIO_50,BlackLib::output, BlackLib::SecureMode);

    //Led RGB
    BlackLib::BlackGPIO leds[3] = {
        BlackLib::BlackGPIO(BlackLib::GPIO_46,BlackLib::output, BlackLib::SecureMode),
        BlackLib::BlackGPIO(BlackLib::GPIO_26,BlackLib::output, BlackLib::SecureMode),
        BlackLib::BlackGPIO(BlackLib::GPIO_44,BlackLib::output, BlackLib::SecureMode)
    };

    void (*functions[])(BlackLib::BlackGPIO (&)[3]) = {
        red_light,
        green_light,
        blue_light,
        white_light,
        yellow_light,
        pink_light,
        cyan_light
    };

    unsigned int sleep_time = 10000;

    statusLed.setValue(BlackLib::high);
    std::cout << "Pressione o botão para iniciar\n";

    while (!button.getNumericValue()) {}

    // Set everything to "default" values
    for (int i = 0; i < 3; i++)
        leds[i].setValue(BlackLib::high);

    std::cout << "Executando o programa, pressione o botão para parar!\n";

    do {
        if (readAnalog(0) < 2000)
            std::random_shuffle(functions, functions + 6);
        sleep_time = (readAnalog(1) + 500)*100;
        for (int i = 0; i < 6; i++) {
            functions[i](leds);
            usleep(sleep_time);
        }
    } while (!button.getNumericValue());

    std::cout << "Programa encerrado, desligando leds\n";

    // Reset everything
    for (int i = 0; i < 3; i++)
        leds[i].setValue(BlackLib::low);
    statusLed.setValue(BlackLib::low);

    return 0;
}
