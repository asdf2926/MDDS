/*
 * error.c
 *
 *  Created on: 2019Äê1ÔÂ23ÈÕ
 *      Author: asdf2
 */
#include <includes.h>
inline void AutoRecovery(enum e_SystemFault Fault)
{
    switch(Fault)
    {

    }

}


#pragma vector = NMI_VECTOR
__interrupt void NMInterrupt()
{

    if(IFG1&OFIFG)AutoRecovery(OscFault);
}
