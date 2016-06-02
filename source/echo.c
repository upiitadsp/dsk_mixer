//DSP
//Practica: Ecualizador
//Grupo: 3MM5
//Nombres: Bejarano Montiel Omar
         //Enriquez Ramirez Oscar
         //Villaseñor Hernandez Carlos

#include "dsk6713.h"
#include "dsk6713_aic23.h"
#include "dsk6713_dip.h"
#include "dsk6713_led.h"
#include <stdio.h>
#include "kernels.h"
#include "fir.h"


Uint32 fs = DSK6713_AIC23_FREQ_16KHZ;
DSK6713_AIC23_CodecHandle manejador;
DSK6713_AIC23_Config configuracion = DSK6713_AIC23_DEFAULTCONFIG;

void codec_init(void);
Uint32 codec_read(void);
void codec_write(Uint32 output_data);
#define OUTPUT_GAIN 1

void leds_output(short led_state);
#define LED_STATE_ACTIVE 1
#define LED_STATE_WATING 0

int main(){
    float input_data;
    float output_data;
    //Configure hardware
    codec_init();
    fir_init(banda1,banda2,banda3,banda4,banda5);

    while(1){
        //Processing data
        if(DSK6713_DIP_get(3)==0){
            //Initialize processing
            leds_output(LED_STATE_ACTIVE);

            while(DSK6713_DIP_get(3)==0){
                input_data = codec_read();
                output_data = fir_filter(input_data);
                codec_write(output_data * OUTPUT_GAIN);
            }
        }
        //Waiting
        else{
            leds_output(LED_STATE_WATING);
        }
    }
}

void codec_init(void){
    manejador = DSK6713_AIC23_openCodec(0,&configuracion);
    DSK6713_AIC23_setFreq(manejador,fs);
    DSK6713_DIP_init();
    DSK6713_LED_init();

}

Uint32 codec_input_data;
Uint32 codec_read(void){
    while(!(DSK6713_AIC23_read(manejador, &codec_input_data)));
    return codec_input_data;
}

void codec_write(Uint32 output_data){
    while(!(DSK6713_AIC23_write(manejador,output_data)));
}


void leds_output(short led_state){
    if(led_state == LED_STATE_ACTIVE){
        DSK6713_LED_on(0);
        DSK6713_LED_off(1);
        DSK6713_LED_off(2);
        DSK6713_LED_off(3);
    }else{
        DSK6713_LED_off(0);
        DSK6713_LED_off(1);
        DSK6713_LED_off(2);
        DSK6713_LED_off(3);
    }
}
