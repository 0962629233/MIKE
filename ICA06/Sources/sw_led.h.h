// Switch and indicator LED library
// Revision History:
// May 9th 2014 - Initial Port to C - Simon Walker
// June 2018 - Minor change to AnyButton, typedef on enum added
// Oct 2018 - Added enum switch function, separated debounce/non-debounce versions
// Dec 2020 - Simplified function names
// Sep 2021 - Debounce option added to Transition
// Sept 2022 - Revised by Carlos, added bit fields, modeled switch states, and added optional passing by reference functions
//Oct 07, 2022 - Corrected some mistakes: using wrong typedef
//Sept 27. 2023 - Correction: Removed extra binary digit from SWL_ANY. Monir edits

// enum to describe LED indicator positions
// tag values represent actual bit positions
typedef enum LEDColourTypedef__ 
{
  SWL_RED     = 0b10000000,
  SWL_YELLOW  = 0b01000000,
  SWL_GREEN   = 0b00100000,
  SWL_ALL     = 0b11100000
} SWL_LEDColour;

// enum to describe mc switch positions
// tag values represent actual bit positions
typedef enum SwitchPosTypedef__ 
{
  SWL_CTR  = 0b00000001,
  SWL_RIGHT= 0b00000010,
  SWL_DOWN = 0b00000100,
  SWL_LEFT = 0b00001000,
  SWL_UP   = 0b00010000, 
  SWL_ANY = 0b00011111
} SWL_SwitchPos;

//To model switch states as 4 states
typedef enum SwStateTypedef__
{
  Idle,
  Pressed,
  Held,
  Released,
}SwState;

//Optional - To use bitfields with switches and leds
typedef union SwLedTypedef__
{
  volatile unsigned char Port;
  struct __Bits
  {
    unsigned int SwMid_BIT:1;
    unsigned int SwRight_BIT:1;
    unsigned int SwDown_BIT:1;
    unsigned int SwLeft_BIT:1;
    unsigned int SwUp_BIT:1;
    unsigned int GreenLed_BIT:1;
    unsigned int YellowLed_BIT:1;
    unsigned int RedLed_BIT:1;
  }Bits;
}SwLedTypedef;


// init - must be called to init port PT1AD1
void SWL_Init (void);

///////////////////////////////////////////////////////////////
// LED functions
void SWL_ON (SWL_LEDColour led);
void SWL_OFF (SWL_LEDColour led);
void SWL_TOG (SWL_LEDColour led);
///////////////////////////////////////////////////////////////
// special LED function
//void SWL_AUX_ON (void);
//void SWL_AUX_OFF(void);

///////////////////////////////////////////////////////////////
// switch functions

// is a specific switch being pushed (T/F)
int SWL_Pushed (SWL_SwitchPos pos);

// is any switch being pushed (T/F)
int SWL_Any (void);
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////

  /*
  You won't implement these functions initially
  After we talk about some switch related issues, you will be
  implementing these functions
  */

// by switch name
int SWL_PushedDeb (SWL_SwitchPos pos);  //Debounced version of SWL_Pushed

//Optional
SwState Sw_Process(SwState*, SWL_SwitchPos); //Process state of a swicth in PT1AD1
//Process debounced state of a swicth in PT1AD1
SwState Sw_ProcessD(SwState*, SWL_SwitchPos); //port, SwState, PIN

void PLL_To20MHz (void);
void PLL_To24MHz (void);
void delayTimer(int delaytime);
