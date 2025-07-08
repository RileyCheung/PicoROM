#include <stdio.h>
#include "pico/stdlib.h"

uint8_t ROM[32768] = {};
const int address_pins[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
const int clock_pin = 15;
const int data_pins[8] = {16, 17, 18, 19, 20, 21, 22, 26};
const int data_oe_pin = 27;

// the output enable will be done in hardware, if add15 high -> data output enable high

uint16_t read_address(){
    uint16_t address = 0;
    for (int i = 14; i >= 0; i--)
    {
        address = (address<<1);
        address += gpio_get(address_pins[i]);
    }
    return address;
}

uint8_t output_data(uint16_t address){
    // checking valid inputlear
    if( address >= 32768 ){
        printf("Address out of range : %i \n", address);
        return 0;
    }

    //output onto data bus
    uint8_t data = ROM[address];
    for (int i = 0; i < 8; i++)
    {
        gpio_put(data_pins[i], (data>>i) & 1 );
    }
    
    return data;
}

void on_clk(){
    uint16_t address = read_address();
    uint8_t data = output_data(address);

    printf("%i\n", address);
}

int main()
{
    printf("asdasdsa !!!\n");
    stdio_init_all();

    // setup address pins
    for (size_t i = 0; i < 15; i++)
    {
        // address pins should only be read
        gpio_init(address_pins[i]);
        gpio_set_dir(address_pins[i],GPIO_IN);
        gpio_pull_down(address_pins[i]);
    }
    // setup data pins
    for (size_t i = 0; i < 8; i++)
    {
        // data pins should only be output
        gpio_init(data_pins[i]);
        gpio_set_dir(data_pins[i], GPIO_OUT);
    }

    //setup clock in as interrupt
    gpio_init(clock_pin);
    gpio_set_dir(clock_pin, GPIO_IN);
    gpio_pull_down(clock_pin); // tied to low unless clock

    gpio_init(data_oe_pin);
    gpio_set_dir(data_oe_pin, GPIO_OUT);

    printf("Starting ROM\n");
    
    bool clock = true;
    bool clock_previous = false;

    gpio_put(data_oe_pin, 1);
    int counter = 0;
    while (true) {

        // On rising edge of clock pulse
        if(clock == true & clock_previous==false){
            on_clk();
        }
        clock_previous = clock;
        clock = gpio_get(clock_pin);

        on_clk();
        
        for (int i = 0; i < 8; i++){
            gpio_put(data_pins[i], (counter>>i) & 1 );
        }
        counter++;

        sleep_ms(1);
    }
    return 0;
}