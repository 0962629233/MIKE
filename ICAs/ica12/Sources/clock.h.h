//Clock System Library
//Processor: MC9S12XDP512
//Crystal: 16 MHz
//by Carlos Estay
//January 2022
//Edit: October 6th, 2022
//Added clockDiv enumerations: October 11th, 2023


#define DEF_BUS_CLOCK 8000000   //default clock speed

/*
    The following defines are just to avoid errors in VsCode,
    not necessary to compile and flash a program using code warrior
*/
#define EnableInterrupts   {__asm CLI;}
#define DisableInterrupts  {__asm SEI;}
#define asm _asm

//Enumeraion used for clock output / divider
typedef enum ClockDivTypedef
{
    ClockOutDiv1 = 0b00000000,
    ClockOutDiv2 = 0b00000001,
    ClockOutDiv3 = 0b00000010,
    ClockOutDiv4 = 0b00000011
}ClockOutDiv;


/// @brief Enable output specifying divider for it
/// @param  ClockOutDiv
void Clock_EnableOutput(ClockOutDiv);

/// @brief Set clock to 8MHZ(default, disable pll)
/// @param  
void Clock_Set8MHZ(void); 

/// @brief Set clock to 20MHZ using PLL
/// @param  void
void PLL_To20MHz (void);

/// @brief Set clock to 24MHZ using PLL
/// @param void 
void PLL_To24MHz (void);

/// @brief Set clock to 40MHZ using PLL (optional)
/// @param void 
void Clock_Set40MHZ(void); //Set clock to 40MHZ using PLL

/// @brief Get current clock speed
/// @param  void
/// @return current BUS speed
unsigned long Clock_GetBusSpeed(void);


