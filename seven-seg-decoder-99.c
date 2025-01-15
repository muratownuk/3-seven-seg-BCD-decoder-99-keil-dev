/*
    includes
*/
#include <c8051F000.h>

/*
    16-bit SFR definitions for C8051F005
*/
sfr16 RCAP2=0xCA;                   // timer 2 reload value
sfr16 T2=0xCC;                      // timer 2

/*
    sbit definitions
*/
sbit dec1A=P0^0; 
sbit dec1B=P0^1; 
sbit dec1C=P0^2; 
sbit dec1D=P0^3; 
sbit dec2A=P0^4; 
sbit dec2B=P0^5; 
sbit dec2C=P0^6; 
sbit dec2D=P0^7; 

/*
    function prototypes
*/
void vWatchDog(bit status); 
void vOSC_Init(void); 
void vPort_Init(void); 
void vTimer2_Init(void); 
void vDisplayNumber(int number, unsigned int decoder); 
void vDelay_ms(unsigned int ms); 

/*
    global constants
*/
#define OFF  0
#define ON   1
#define DEC1 1
#define DEC2 2 

#define SYSCLK 16000000                 // internal oscillator frequency
#define DELAY  1000                     // 1 second delay
#define RELOAD_VAL -((SYSCLK/12)/1000)  // RCAP2 reload value for timer 2

/*
    main
*/
void main(void){

    int count=0;

    // initialize c8051f005
    vWatchDog(OFF);                 // disable watchdog timer
    vOSC_Init();                    // initialize oscillator (16.0 MHz)
    vPort_Init();                   // initialize xbar & GPIO
    vTimer2_Init();                 // initialize timer 2

    // main program
    while(1){
        
        // display one's order on first 7-seg LED
        vDisplayNumber(count%10, DEC1);
        // display ten's order on second 7-seg LED
        vDisplayNumber(count/10, DEC2);
        vDelay_ms(DELAY);           // 1 second delay
        count++;

        if(count==100)
            count=0;

    }

}

/*
    functions
*/
/*
    vWatchDog: 
    Turn watchdog timer On or Off.
*/
void vWatchDog(bit status){

    if(status==ON)
        return;                     // watchdog is enabled on power-on
    
    else{
        WDTCN=0xDE;                 // disable watchdog timer
        WDTCN=0xAD;
    }
}

/*
    vOSC_Init: 
    use internal oscillator (OSCICN) at 16.0 MHz (SYSCLK) and turn off 
    external oscillator (OSCXCN).

    parameters: none
    return    : none
    

*/
void vOSC_Init(void){

    OSCXCN&=0x00;                    // turn off external oscillator
    OSCICN|=0x83;                    // CLKSL=0 (internal oscillator) @16MHz

}

/*
    vPORT_Init:
    enable crossbar (XBARE) for port outputs and use ports P0.0-7 as outputs
    (push-pull). Initiallize the P0 outputs all to low.

    parameters: none
    return    : none

*/
void vPort_Init(void){ 
    
    XBR2=0x40;                      // enable crossbar (xbar) and weak-pullups
    PRT0CF=0xFF;                    // P0.0-7 as push-pull outputs
    P0=0x00;                        // turn all of port 0 (P0) outputs low

}

/*
    vTimer2_init:
    initialize timer 2 to how we want to use it. timer 2 in mode 1 with 
    auto-reload. Disable timer 2 interrupts (ET2) as we will use timer 2 flag 
    (TF2) directly.

*/
void vTimer2_Init(void){

    ET2=0;                          // disable T2 interrupt (EA=0 anyways)
    // make sure T2M=0 in clock control reg, this uses SYSCLK/12 as time base.
    CKCON&=!0x20;
    // load the reload value for T2 in RCAP2. timer 2 overflows at 1KHz.                   
    RCAP2=RELOAD_VAL;
    T2=RCAP2;                       // initial load value for T2           
 
}

/*
    vDisplayNumber:
    display the number on the 7-segment LED display.

    parameters: number (the number to display), decoder (the decoder number)
    return    : none  

*/
void vDisplayNumber(int number, unsigned int decoder){

    switch(number){  
        case 0:
            if(decoder==DEC1){
                dec1A=0; dec1B=0; dec1C=0; dec1D=0;
            }
            else if (decoder==DEC2){
                dec2A=0; dec2B=0; dec2C=0; dec2D=0;
            }
            else
                ;
            break;
        case 1:
            if(decoder==DEC1){
                dec1A=1; dec1B=0; dec1C=0; dec1D=0;
            }
            else if (decoder==DEC2){
                dec2A=1; dec2B=0; dec2C=0; dec2D=0;
            }
            else
                ;
            break;
        case 2:
            if(decoder==DEC1){
                dec1A=0; dec1B=1; dec1C=0; dec1D=0;
            }
            else if (decoder==DEC2){
                dec2A=0; dec2B=1; dec2C=0; dec2D=0;
            }
            else
                ;
            break;
        case 3:
            if(decoder==DEC1){
                dec1A=1; dec1B=1; dec1C=0; dec1D=0;
            }
            else if (decoder==DEC2){
                dec2A=1; dec2B=1; dec2C=0; dec2D=0;
            }
            else
                ;  
            break;
        case 4:
            if(decoder==DEC1){
                dec1A=0; dec1B=0; dec1C=1; dec1D=0;
            }
            else if (decoder==DEC2){
                dec2A=0; dec2B=0; dec2C=1; dec2D=0;
            }
            else
                ;  
            break;
        case 5:
            if(decoder==DEC1){
                dec1A=1; dec1B=0; dec1C=1; dec1D=0;
            }
            else if (decoder==DEC2){
                dec2A=1; dec2B=0; dec2C=1; dec2D=0;
            }
            else
                ;  
            break;
        case 6:
            if(decoder==DEC1){
                dec1A=0; dec1B=1; dec1C=1; dec1D=0;
            }
            else if (decoder==DEC2){
                dec2A=0; dec2B=1; dec2C=1; dec2D=0;
            }
            else
                ;   
            break;
        case 7:
            if(decoder==DEC1){
                dec1A=1; dec1B=1; dec1C=1; dec1D=0;
            }
            else if (decoder==DEC2){
                dec2A=1; dec2B=1; dec2C=1; dec2D=0;
            }
            else
                ;   
            break;
        case 8:
            if(decoder==DEC1){
                dec1A=0; dec1B=0; dec1C=0; dec1D=1;
            }
            else if (decoder==DEC2){
                dec2A=0; dec2B=0; dec2C=0; dec2D=1;
            }
            else
                ;  
            break;
        case 9:
            if(decoder==DEC1){
                dec1A=1; dec1B=0; dec1C=0; dec1D=1;
            }
            else if (decoder==DEC2){
                dec2A=1; dec2B=0; dec2C=0; dec2D=1;
            }
            else
                ; 
            break;
        default:
            if(decoder==DEC1){
                dec1A=0; dec1B=0; dec1C=0; dec1D=1;
            }
            else if (decoder==DEC2){
                dec2A=0; dec2B=0; dec2C=0; dec2D=1;
            }
            else
                ; 
    }

}

/*
    vDelay_ms:
    create milliseconds delay with this function.

    parameters: ms (number of milliseconds of delay)
    return    : none

*/
void vDelay_ms(unsigned int ms){
    
    TR2=1;                          // start timer 2
    while(ms){        
        TF2=0;                      // clear timer 2 flag
        while(!TF2)
            ;                       // wait until T2 overflows
        ms--;                       // decrement millisecond count
    }
    TR2=0;                          // stop timer 2 

}






























