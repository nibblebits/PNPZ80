/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/

#ifndef __PNPZ80_H__
#define __PNPZ80_H__

#include <windows.h>
#include <stdint.h>


// Main register ids
enum
{
    B_REG = 0b000,
    C_REG = 0b001,
    D_REG = 0b010,
    E_REG = 0b011,
    H_REG = 0b100,
    L_REG = 0b101,
    F_REG = 0b110,
    A_REG = 0b111
};

// Register pair ids
enum
{
    BC_REG_PAIR_DD = 0b00,
    DE_REG_PAIR_DD = 0b01,
    HL_REG_PAIR_DD = 0b10,
    SP_REG_PAIR_DD = 0b11
};

// qq register pair ids
enum
{
    BC_REG_PAIR_QQ = 0b00,
    DE_REG_PAIR_QQ = 0b01,
    HL_REG_PAIR_QQ = 0b10,
    AF_REG_PAIR_QQ = 0b11
};

enum
{
    PAIR_TYPE_DD = 0,
    PAIR_TYPE_QQ = 1
};
// Flags
enum
{
    C_FLAG = 0b00000001,
    N_FLAG = 0b00000010,
    PV_FLAG = 0b00000100,
    H_FLAG = 0b00010000,
    Z_FLAG = 0b01000000,
    S_FLAG = 0b10000000
};

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif


#ifdef __cplusplus
}
#endif

#endif // __PNPZ80_H__
