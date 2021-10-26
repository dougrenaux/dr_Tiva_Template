/******************************************************************************
 * @file     system_TM4C1294.c (based on system_TM4C129.c)
 * @brief    CMSIS Device System Source File for
 *           TI TIVA TM4C129 Snowflake Device Series
 * @version  V1.00
 * @date     11. August 2019 (modified by Hugo Vieira Neto)
 ******************************************************************************/

#include <stdint.h>
#include "TM4C1294NCPDT.h"

/*----------------------------------------------------------------------------
  Defines taken from inc/hw_sysctl.h
 *----------------------------------------------------------------------------*/
#define SYSCTL_MEMTIM0_EBCHT_0_5                                              \
                                (0x00000000)  // 1/2 system clock period
#define SYSCTL_MEMTIM0_EBCHT_1_5                                              \
                                (0x00800000)  // 1.5 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_2  (0x00C00000)  // 2 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_2_5                                              \
                                (0x01000000)  // 2.5 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_3  (0x01400000)  // 3 system clock periods
#define SYSCTL_MEMTIM0_EBCHT_3_5                                              \
                                (0x01800000)  // 3.5 system clock periods
#define SYSCTL_MEMTIM0_EBCE     (0x00200000)  // EEPROM Bank Clock Edge
#define SYSCTL_MEMTIM0_MB1      (0x00100010)  // Must be one
#define SYSCTL_MEMTIM0_FBCHT_0_5                                              \
                                (0x00000000)  // 1/2 system clock period
#define SYSCTL_MEMTIM0_FBCHT_1_5                                              \
                                (0x00000080)  // 1.5 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_2  (0x000000C0)  // 2 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_2_5                                              \
                                (0x00000100)  // 2.5 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_3  (0x00000140)  // 3 system clock periods
#define SYSCTL_MEMTIM0_FBCHT_3_5                                              \
                                (0x00000180)  // 3.5 system clock periods
#define SYSCTL_MEMTIM0_FBCE     (0x00000020)  // Flash Bank Clock Edge
#define SYSCTL_MEMTIM0_FWS_M    (0x0000000F)  // Flash Wait State
#define SYSCTL_MEMTIM0_EWS_S    (16)
#define SYSCTL_MEMTIM0_FWS_S    (0)

#define SYSCTL_MOSCCTL_OSCRNG   (0x00000010)  // Oscillator Range
#define SYSCTL_MOSCCTL_PWRDN    (0x00000008)  // Power Down
#define SYSCTL_MOSCCTL_NOXTAL   (0x00000004)  // No Crystal Connected

#define SYSCTL_PLLFREQ0_PLLPWR  (0x00800000)  // PLL Power
#define SYSCTL_PLLFREQ0_MFRAC_M (0x000FFC00)  // PLL M Fractional Value
#define SYSCTL_PLLFREQ0_MINT_M  (0x000003FF)  // PLL M Integer Value
#define SYSCTL_PLLFREQ0_MFRAC_S (10)

#define SYSCTL_PLLFREQ1_Q_M     (0x00001F00)  // PLL Q Value
#define SYSCTL_PLLFREQ1_N_M     (0x0000001F)  // PLL N Value
#define SYSCTL_PLLFREQ1_Q_S     (8)
#define SYSCTL_PLLFREQ1_N_S     (0)

#define SYSCTL_PLLSTAT_LOCK     (0x00000001)  // PLL Lock

#define SYSCTL_RSCLKCFG_MEMTIMU (0x80000000)  // Memory Timing Register Update
#define SYSCTL_RSCLKCFG_NEWFREQ (0x40000000)  // New PLLFREQ Accept
#define SYSCTL_RSCLKCFG_USEPLL  (0x10000000)  // Use PLL
#define SYSCTL_RSCLKCFG_PLLSRC_M                                              \
                                (0x0F000000)  // PLL Source
#define SYSCTL_RSCLKCFG_PLLSRC_PIOSC                                          \
                                (0x00000000)  // PIOSC is PLL input clock source
#define SYSCTL_RSCLKCFG_PLLSRC_MOSC                                           \
                                (0x03000000)  // MOSC is the PLL input clock
                                            // source
#define SYSCTL_RSCLKCFG_OSCSRC_M                                              \
                                (0x00F00000)  // Oscillator Source
#define SYSCTL_RSCLKCFG_OSCSRC_PIOSC                                          \
                                (0x00000000)  // PIOSC is oscillator source
#define SYSCTL_RSCLKCFG_OSCSRC_LFIOSC                                         \
                                (0x00200000)  // LFIOSC is oscillator source
#define SYSCTL_RSCLKCFG_OSCSRC_MOSC                                           \
                                (0x00300000)  // MOSC is oscillator source
#define SYSCTL_RSCLKCFG_OSCSRC_RTC                                            \
                                (0x00400000)  // Hibernation Module RTC
                                              // Oscillator (RTCOSC)
#define SYSCTL_RSCLKCFG_PSYSDIV_M                                             \
                                (0x000003FF)  // PLL System Clock Divisor

#define SYSCTL_RIS_MOSCPUPRIS   (0x00000100)  // MOSC Power Up Raw Interrupt
                                              // Status
#define SYSCTL_RSCLKCFG_OSYSDIV_M                                             \
                                (0x000FFC00)  // Oscillator System Clock Divisor
#define SYSCTL_RSCLKCFG_PSYSDIV_M                                             \
                                (0x000003FF)  // PLL System Clock Divisor
#define SYSCTL_RSCLKCFG_OSYSDIV_S                                             \
                                (10)
#define SYSCTL_RSCLKCFG_PSYSDIV_S                                             \
                                (0)


/*----------------------------------------------------------------------------
  Defines taken from driverlib/sysctl.h
 *----------------------------------------------------------------------------*/
#define SYSCTL_CFG_VCO_480      (0xF1000000)  // VCO is 480 MHz
#define SYSCTL_CFG_VCO_320      (0xF0000000)  // VCO is 320 MHz
#define SYSCTL_OSC_MAIN         (0x00000000)  // Osc source is main osc
#define SYSCTL_OSC_INT          (0x00000010)  // Osc source is int. osc
#define SYSCTL_OSC_INT30        (0x00000030)  // Osc source is int. 30 kHz
#define SYSCTL_OSC_EXT32        (0x80000038)  // Osc source is ext. 32 kHz
#define SYSCTL_USE_PLL          (0x00000000)  // System clock is the PLL clock
#define SYSCTL_USE_OSC          (0x00003800)  // System clock is the osc clock
#define SYSCTL_XTAL_5MHZ        (0x00000240)  // External crystal is 5MHz
#define SYSCTL_XTAL_5_12MHZ     (0x00000280)  // External crystal is 5.12MHz
#define SYSCTL_XTAL_6MHZ        (0x000002C0)  // External crystal is 6MHz
#define SYSCTL_XTAL_6_14MHZ     (0x00000300)  // External crystal is 6.144MHz
#define SYSCTL_XTAL_7_37MHZ     (0x00000340)  // External crystal is 7.3728MHz
#define SYSCTL_XTAL_8MHZ        (0x00000380)  // External crystal is 8MHz
#define SYSCTL_XTAL_8_19MHZ     (0x000003C0)  // External crystal is 8.192MHz
#define SYSCTL_XTAL_10MHZ       (0x00000400)  // External crystal is 10 MHz
#define SYSCTL_XTAL_12MHZ       (0x00000440)  // External crystal is 12 MHz
#define SYSCTL_XTAL_12_2MHZ     (0x00000480)  // External crystal is 12.288 MHz
#define SYSCTL_XTAL_13_5MHZ     (0x000004C0)  // External crystal is 13.56 MHz
#define SYSCTL_XTAL_14_3MHZ     (0x00000500)  // External crystal is 14.31818 MHz
#define SYSCTL_XTAL_16MHZ       (0x00000540)  // External crystal is 16 MHz
#define SYSCTL_XTAL_16_3MHZ     (0x00000580)  // External crystal is 16.384 MHz
#define SYSCTL_XTAL_18MHZ       (0x000005C0)  // External crystal is 18.0 MHz
#define SYSCTL_XTAL_20MHZ       (0x00000600)  // External crystal is 20.0 MHz
#define SYSCTL_XTAL_24MHZ       (0x00000640)  // External crystal is 24.0 MHz
#define SYSCTL_XTAL_25MHZ       (0x00000680)  // External crystal is 25.0 MHz


/*----------------------------------------------------------------------------
  Defines for clock configuration -- user defined
 *----------------------------------------------------------------------------*/
#define __CONFIG_CLOCK                                                        \
    (SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320)
//#define __SYSTEM_CLOCK    (120000000UL)
#define __SYSTEM_CLOCK    (5000000UL)        


/*----------------------------------------------------------------------------
  Defines taken from driverlib/sysctl.c
 *----------------------------------------------------------------------------*/
#define MAX_VCO_ENTRIES         2
#define MAX_XTAL_ENTRIES        18

/*----------------------------------------------------------------------------
  Macros taken from driverlib/sysctl.c
 *----------------------------------------------------------------------------*/
// Macro that converts the XTAL value to an index to the g_pui32Xtals array
#define SysCtlXtalCfgToIndex(a) ((a & 0x7c0) >> 6)
// Macros that make g_pui32XTALtoVCO table more readable
#define PLL_M_TO_REG(mi, mf)                                                  \
        ((uint32_t)mi | (uint32_t)(mf << SYSCTL_PLLFREQ0_MFRAC_S))
#define PLL_N_TO_REG(n)                                                       \
        ((uint32_t)(n - 1) << SYSCTL_PLLFREQ1_N_S)
#define PLL_Q_TO_REG(q)                                                       \
        ((uint32_t)(q - 1) << SYSCTL_PLLFREQ1_Q_S)


/*----------------------------------------------------------------------------
  Constants taken from driverlib/sysctl.c
 *----------------------------------------------------------------------------*/
// Array that maps the crystal number in RCC to a frequency
static const uint32_t g_pui32Xtals[] = { 1000000,  1843200,  2000000,
                                         2457600,  3579545,  3686400,
                                         4000000,  4096000,  4915200, 
                                         5000000,  5120000,  6000000,
                                         6144000,  7372800,  8000000,
                                         8192000, 10000000, 12000000,
                                        12288000, 13560000, 14318180,
                                        16000000, 16384000, 18000000,
                                        20000000, 24000000, 25000000
};

// Look up table of the possible VCO frequencies
static const uint32_t g_pui32VCOFrequencies[MAX_VCO_ENTRIES] = {
    160000000,                              // VCO 320
    240000000                               // VCO 480
};

// Look-up table of the values that go into the PLLFREQ0 and PLLFREQ1 registers
static const uint32_t g_pppui32XTALtoVCO[MAX_VCO_ENTRIES][MAX_XTAL_ENTRIES][3] =
{
  {
    // VCO 320 MHz
    { PLL_M_TO_REG(64, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 5 MHz
    { PLL_M_TO_REG(62, 512), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 5.12 MHz
    { PLL_M_TO_REG(160, 0),  PLL_N_TO_REG(3), PLL_Q_TO_REG(2) }, // 6 MHz
    { PLL_M_TO_REG(52, 85),  PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 6.144 MHz
    { PLL_M_TO_REG(43, 412), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 7.3728 MHz
    { PLL_M_TO_REG(40, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 8 MHz
    { PLL_M_TO_REG(39, 64),  PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 8.192 MHz
    { PLL_M_TO_REG(32, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 10 MHz
    { PLL_M_TO_REG(80, 0),   PLL_N_TO_REG(3), PLL_Q_TO_REG(2) }, // 12 MHz
    { PLL_M_TO_REG(26, 43),  PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 12.288 MHz
    { PLL_M_TO_REG(23, 613), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 13.56 MHz
    { PLL_M_TO_REG(22, 358), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 14.318180 MHz
    { PLL_M_TO_REG(20, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 16 MHz
    { PLL_M_TO_REG(19, 544), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 16.384 MHz
    { PLL_M_TO_REG(160, 0),  PLL_N_TO_REG(9), PLL_Q_TO_REG(2) }, // 18 MHz
    { PLL_M_TO_REG(16, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 20 MHz
    { PLL_M_TO_REG(40, 0),   PLL_N_TO_REG(3), PLL_Q_TO_REG(2) }, // 24 MHz
    { PLL_M_TO_REG(64, 0),   PLL_N_TO_REG(5), PLL_Q_TO_REG(2) }  // 25 MHz
  },
  {
    // VCO 480 MHz
    { PLL_M_TO_REG(96, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 5 MHz
    { PLL_M_TO_REG(93, 768), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 5.12 MHz
    { PLL_M_TO_REG(80, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 6 MHz
    { PLL_M_TO_REG(78, 128), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 6.144 MHz
    { PLL_M_TO_REG(65, 107), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 7.3728 MHz
    { PLL_M_TO_REG(60, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 8 MHz
    { PLL_M_TO_REG(58, 608), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 8.192 MHz
    { PLL_M_TO_REG(48, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 10 MHz
    { PLL_M_TO_REG(40, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 12 MHz
    { PLL_M_TO_REG(39, 64),  PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 12.288 MHz
    { PLL_M_TO_REG(35, 408), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 13.56 MHz
    { PLL_M_TO_REG(33, 536), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 14.318180 MHz
    { PLL_M_TO_REG(30, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 16 MHz
    { PLL_M_TO_REG(29, 304), PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 16.384 MHz
    { PLL_M_TO_REG(80, 0),   PLL_N_TO_REG(3), PLL_Q_TO_REG(2) }, // 18 MHz
    { PLL_M_TO_REG(24, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 20 MHz
    { PLL_M_TO_REG(20, 0),   PLL_N_TO_REG(1), PLL_Q_TO_REG(2) }, // 24 MHz
    { PLL_M_TO_REG(96, 0),   PLL_N_TO_REG(5), PLL_Q_TO_REG(2) }  // 25 MHz
  }
};

// Array that maps system clock frequency to flash memory timing parameters
static const struct {
    uint32_t ui32Frequency;
    uint32_t ui32MemTiming;
} g_sXTALtoMEMTIM[] = {
    { 16000000, (SYSCTL_MEMTIM0_FBCHT_0_5 | SYSCTL_MEMTIM0_FBCE |
                 (0 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_0_5 | SYSCTL_MEMTIM0_EBCE |
                 (0 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    { 40000000, (SYSCTL_MEMTIM0_FBCHT_1_5 | (1 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_1_5 | (1 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    { 60000000, (SYSCTL_MEMTIM0_FBCHT_2   | (2 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_2   | (2 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    { 80000000, (SYSCTL_MEMTIM0_FBCHT_2_5 | (3 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_2_5 | (3 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    {100000000, (SYSCTL_MEMTIM0_FBCHT_3   | (4 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_3   | (4 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    {120000000, (SYSCTL_MEMTIM0_FBCHT_3_5 | (5 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_3_5 | (5 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) }
};


/*----------------------------------------------------------------------------
  Functions taken from driverlib/sysctl.c
 *----------------------------------------------------------------------------*/
// Get the correct memory timings for a given system clock value
static uint32_t _SysCtlMemTimingGet(uint32_t ui32SysClock){
  for(uint_fast8_t ui8Idx = 0;
      ui8Idx < (sizeof(g_sXTALtoMEMTIM) / sizeof(g_sXTALtoMEMTIM[0])); ui8Idx++)
    if(ui32SysClock <= g_sXTALtoMEMTIM[ui8Idx].ui32Frequency)
      return(g_sXTALtoMEMTIM[ui8Idx].ui32MemTiming);
  return(0);
} // _SysCtlMemTimingGet

// Calculate the system frequency from the register settings
static uint32_t _SysCtlFrequencyGet(uint32_t ui32Xtal){
    uint_fast16_t ui16PFract = ((SYSCTL->PLLFREQ0 & SYSCTL_PLLFREQ0_MFRAC_M) >>
                  SYSCTL_PLLFREQ0_MFRAC_S);
    uint_fast16_t ui16PInt = SYSCTL->PLLFREQ0 & SYSCTL_PLLFREQ0_MINT_M;
    uint_fast8_t ui8Q = (((SYSCTL->PLLFREQ1 & SYSCTL_PLLFREQ1_Q_M) >>
             SYSCTL_PLLFREQ1_Q_S) + 1);
    uint_fast8_t ui8N = (((SYSCTL->PLLFREQ1 & SYSCTL_PLLFREQ1_N_M) >>
             SYSCTL_PLLFREQ1_N_S) + 1);
    ui32Xtal /= (uint32_t)ui8N;
    uint_fast16_t ui16F1 = ui16PFract / 32;
    uint_fast16_t ui16F2 = ui16PFract - (ui16F1 * 32);
    uint32_t ui32Result = ui32Xtal * (uint32_t)ui16PInt;
    ui32Result += (ui32Xtal * (uint32_t)ui16F1) / 32;
    ui32Result += (ui32Xtal * (uint32_t)ui16F2) / 1024;
    ui32Result = ui32Result / (uint32_t)ui8Q;
    return(ui32Result / 2);
} // _SysCtlFrequencyGet


/*----------------------------------------------------------------------------
  Externals
 *----------------------------------------------------------------------------*/
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  extern uint32_t __Vectors;
#endif


/*----------------------------------------------------------------------------
  System Core Clock variable
 *----------------------------------------------------------------------------*/
__no_init uint32_t SystemCoreClock; // System Core Clock Frequency


/*----------------------------------------------------------------------------
  System Core Clock update function
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate(void){
  /* TODO: Updates required to fully work with TM4C1294 series devices */
} // SystemCoreClockUpdate


/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/
void SystemInit(void){
  #if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
    SCB->VTOR = (uint32_t) &__Vectors;
  #endif

  #if defined (__FPU_USED) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3UL << 10*2) |  // enable CP10 Full Access
                   (3UL << 11*2));  // enable CP11 Full Access
  #endif

  #ifdef UNALIGNED_SUPPORT_DISABLE
    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
  #endif

  // Clock configuration adapted from driverlib/sysctl.c
  // SysCtlClockFreqSet with CMSIS-Core style register access
  SystemCoreClock = 0;
  
  // Get the index of the crystal
  int32_t i32XtalIdx = SysCtlXtalCfgToIndex(__CONFIG_CLOCK);

  // Determine which non-PLL source was selected
  uint32_t ui32Osc, ui32OscSelect;
  uint32_t ui32MOSCCTL;
  
  if((__CONFIG_CLOCK & 0x38) == SYSCTL_OSC_INT){
    // Use the nominal frequency for the PIOSC oscillator
    ui32Osc = 16000000;
    ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_PIOSC | SYSCTL_RSCLKCFG_PLLSRC_PIOSC;
    // Force the crystal index to 16 MHz
    i32XtalIdx = SysCtlXtalCfgToIndex(SYSCTL_XTAL_16MHZ);
  } // if
  
  else if((__CONFIG_CLOCK & 0x38) == SYSCTL_OSC_INT30){
    // Use the nominal frequency for the low frequency oscillator
    ui32Osc = 30000;
    ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_LFIOSC;
  } // else if
  
  else if((__CONFIG_CLOCK & 0x38) == (SYSCTL_OSC_EXT32 & 0x38)){
    // Use the RTC frequency
    ui32Osc = 32768;
    ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_RTC;
  } // else if
  
  else if((__CONFIG_CLOCK & 0x38) == SYSCTL_OSC_MAIN){
    // Bounds check the source frequency for the main oscillator
    // The PLL tables in the g_pppui32XTALtoVCO structure range from 5 to 25MHz
    if((i32XtalIdx > (SysCtlXtalCfgToIndex(SYSCTL_XTAL_25MHZ))) ||
       (i32XtalIdx < (SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ))))
      return;

    ui32Osc = g_pui32Xtals[i32XtalIdx];
    // Set the PLL source select to MOSC
    ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_MOSC | SYSCTL_RSCLKCFG_PLLSRC_MOSC;

    // Clear MOSC power down, high oscillator range setting, and no crystal
    // present setting
    ui32MOSCCTL = SYSCTL->MOSCCTL & ~(SYSCTL_MOSCCTL_OSCRNG |
                  SYSCTL_MOSCCTL_PWRDN | SYSCTL_MOSCCTL_NOXTAL);
    // Increase the drive strength for MOSC of 10 MHz and above
    if(i32XtalIdx >= (SysCtlXtalCfgToIndex(SYSCTL_XTAL_10MHZ) -
                     (SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ))))
      ui32MOSCCTL |= SYSCTL_MOSCCTL_OSCRNG;
    SYSCTL->MOSCCTL = ui32MOSCCTL;
    
    // Timeout using the legacy delay value
    uint32_t ui32Delay = 524288;
    while((SYSCTL->RIS & SYSCTL_RIS_MOSCPUPRIS) == 0){
      ui32Delay--;
      if(ui32Delay == 0)
          break;
     } // while

    // If the main oscillator failed to start up then return
    if(ui32Delay == 0)
      return;
  } // else if
  
  else{
    // Invalid request because no oscillator source was indicated
    ui32Osc = 0;
    ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_PIOSC;
  } // else
  
  uint32_t ui32RSClkConfig, ui32SysDiv;
  // Check if the running with the PLL enabled was requested
  if((__CONFIG_CLOCK & SYSCTL_USE_OSC) == SYSCTL_USE_PLL){
    // __CONFIG_CLOCK must be SYSCTL_OSC_MAIN or SYSCTL_OSC_INT
    if(((__CONFIG_CLOCK & 0x38) != SYSCTL_OSC_MAIN) &&
       ((__CONFIG_CLOCK & 0x38) != SYSCTL_OSC_INT))
      return;
    
    // Get the VCO index out of the __CONFIG_CLOCK parameter
    int32_t i32VCOIdx = (__CONFIG_CLOCK >> 24) & 0x7;

//    // Check if the VCO index is not out of bounds
//    if(i32VCOIdx >= MAX_VCO_ENTRIES)
//      while(1); // error!
    
    // Set the memory timings for the maximum external frequency since
    // this could be a switch to PIOSC or possibly to MOSC which can be
    // up to 25MHz
    SYSCTL->MEMTIM0 = _SysCtlMemTimingGet(25000000);

    // Clear the old PLL divider and source in case it was set
    ui32RSClkConfig = SYSCTL->RSCLKCFG & ~(SYSCTL_RSCLKCFG_PSYSDIV_M |
                      SYSCTL_RSCLKCFG_OSCSRC_M | SYSCTL_RSCLKCFG_PLLSRC_M |
                      SYSCTL_RSCLKCFG_USEPLL);
    // Update the memory timings to match running from PIOSC
    ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;
    // Update clock configuration to switch back to PIOSC
    SYSCTL->RSCLKCFG = ui32RSClkConfig;

    // The table starts at 5 MHz so modify the index to match this
    i32XtalIdx -= SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ);

    // Calculate the System divider for the closest frequency to the requested
    ui32SysDiv = (g_pui32VCOFrequencies[i32VCOIdx] + __SYSTEM_CLOCK - 1) /
                  __SYSTEM_CLOCK;

    // Set the oscillator source
    SYSCTL->RSCLKCFG |= ui32OscSelect;

    // Set the M, N and Q values provided from the table and preserve
    // the power state of the main PLL
    SYSCTL->PLLFREQ1  = g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][1];
    SYSCTL->PLLFREQ1 |= PLL_Q_TO_REG(ui32SysDiv);
    SYSCTL->PLLFREQ0  = (g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][0] |
                       (SYSCTL->PLLFREQ0 & SYSCTL_PLLFREQ0_PLLPWR));

    // Calculate the actual system clock
    SystemCoreClock = _SysCtlFrequencyGet(ui32Osc);

    // Set the Flash and EEPROM timing values
    SYSCTL->MEMTIM0 = _SysCtlMemTimingGet(SystemCoreClock);

    // Check if the PLL is already powered up
    if(SYSCTL->PLLFREQ0 & SYSCTL_PLLFREQ0_PLLPWR)
      SYSCTL->RSCLKCFG |= SYSCTL_RSCLKCFG_NEWFREQ; // Trigger the PLL
    else
      SYSCTL->PLLFREQ0 |= SYSCTL_PLLFREQ0_PLLPWR; // Power up the PLL

    // Wait until the PLL has locked
    int32_t i32Timeout; 
    for(i32Timeout = 32768; i32Timeout > 0; i32Timeout--)
      if((SYSCTL->PLLSTAT & SYSCTL_PLLSTAT_LOCK))
        break;

    // If the loop above did not timeout then switch over to the PLL
    if(i32Timeout){
      ui32RSClkConfig = SYSCTL->RSCLKCFG |
                        (1 << SYSCTL_RSCLKCFG_PSYSDIV_S) | ui32OscSelect |
                        SYSCTL_RSCLKCFG_USEPLL | SYSCTL_RSCLKCFG_MEMTIMU;
      // Set the new clock configuration.
      SYSCTL->RSCLKCFG = ui32RSClkConfig;
    }
  } // if
  
  else{
    // Set the Flash and EEPROM timing values for PIOSC
    SYSCTL->MEMTIM0 = _SysCtlMemTimingGet(16000000);
    // Make sure that the PLL is powered down since it is not being used
    SYSCTL->PLLFREQ0 &= ~SYSCTL_PLLFREQ0_PLLPWR;
    // Clear the old PLL divider and source in case it was set
    ui32RSClkConfig = SYSCTL->RSCLKCFG & ~(SYSCTL_RSCLKCFG_OSYSDIV_M |
                      SYSCTL_RSCLKCFG_OSCSRC_M | SYSCTL_RSCLKCFG_USEPLL);
    // Update the memory timings
    ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;
    // Set the new clock configuration
    SYSCTL->RSCLKCFG = ui32RSClkConfig;
    
    // If zero given as the system clock then default to divide by 1
    if(__SYSTEM_CLOCK == 0)
      ui32SysDiv = 0;
    else{
      // Calculate the System divider based on the requested
      // frequency
      ui32SysDiv = ui32Osc / __SYSTEM_CLOCK;
      // If the system divisor is not already zero, subtract one to
      // set the value in the register which requires the value to
      // be n-1
      if(!ui32SysDiv)
        ui32SysDiv -= 1;
      // Calculate the system clock
      SystemCoreClock = ui32Osc / (ui32SysDiv + 1);
    } // else

    // Set the memory timing values for the new system clock
    SYSCTL->MEMTIM0 = _SysCtlMemTimingGet(SystemCoreClock);
    // Set the new system clock values and update the memory timings
    ui32RSClkConfig = SYSCTL->RSCLKCFG |
                      (ui32SysDiv << SYSCTL_RSCLKCFG_OSYSDIV_S) |
                       ui32OscSelect | SYSCTL_RSCLKCFG_MEMTIMU;
    // Set the new clock configuration
    SYSCTL->RSCLKCFG = ui32RSClkConfig;
  } // else
  
  // Finally change the OSCSRC back to PIOSC
  SYSCTL->RSCLKCFG &= ~(SYSCTL_RSCLKCFG_OSCSRC_M);
} // SystemInit
