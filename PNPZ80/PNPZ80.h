#ifndef __MAIN_H__
#define __MAIN_H__

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

// Flags
enum
{


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

#endif // __MAIN_H__
