/*
 * Generated with the FPGA Interface C API Generator 13.0.0
 * for NI-RIO 13.0.0 or later.
 */

#ifndef __NiFpga_SimpleDataCollection_h__
#define __NiFpga_SimpleDataCollection_h__

#ifndef NiFpga_Version
   #define NiFpga_Version 1300
#endif

#include "NiFpga.h"

/**
 * The filename of the FPGA bitfile.
 *
 * This is a #define to allow for string literal concatenation. For example:
 *
 *    static const char* const Bitfile = "C:\\" NiFpga_SimpleDataCollection_Bitfile;
 */
#define NiFpga_SimpleDataCollection_Bitfile "NiFpga_SimpleDataCollection.lvbitx"

/**
 * The signature of the FPGA bitfile.
 */
static const char* const NiFpga_SimpleDataCollection_Signature = "08DECC61C6001A32AD952794C317AE25";

typedef enum
{
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister = 0x12,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister10 = 0x26,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister11 = 0x22,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister2 = 0x46,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister3 = 0x42,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister4 = 0x3E,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister5 = 0x3A,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister6 = 0x36,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister7 = 0x32,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister8 = 0x2E,
   NiFpga_SimpleDataCollection_IndicatorU8_CountRegister9 = 0x2A,
} NiFpga_SimpleDataCollection_IndicatorU8;

typedef enum
{
   NiFpga_SimpleDataCollection_ControlI16_MCP = 0x16,
   NiFpga_SimpleDataCollection_ControlI16_PAC = 0x1A,
} NiFpga_SimpleDataCollection_ControlI16;

#endif
