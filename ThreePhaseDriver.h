/* 
 * File:   ThreePhaseDriver.h
 * Author: Cameron
 *
 * Created on December 17, 2014, 3:20 PM
 */

#ifndef THREEPHASEDRIVER_H
#define	THREEPHASEDRIVER_H

#include "basicTypes.h"
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect,__attribute__((naked)));

class ThreePhaseDriver {
 /*
  * Called by the naked interrupt routine so it needs to pretend to be the interrupt.
  * Give it the same attributes.
  */
 static void stepFunction() __attribute__ ((signal,__INTR_ATTRS));
 
 /**
  * Read the sin table
  * @param phase
  * @return 
  */
 static inline u1 getPhasePWM(u1 const phase) __attribute__((const));
 
 friend void TIMER1_OVF_vect();
 
// static u1 cacheA;
// static register u1 cacheB asm("r11");
// static register u1 cacheC asm("r12");

public:
 /**
  * Internal granularity of sin wave for each phase
  */
 static u2 constexpr StepsPerPhase = 256;
 
 /**
  * One for each of A, B and C.
  */
 static u1 constexpr PhasesPerCycle = 3;
 
 /**
  * One Cycle is one full commutation "revolution" of the motor. This is almost
  * certainly not one actual revolution of the motor shaft.
  */
 static u2 constexpr StepsPerCycle = StepsPerPhase * PhasesPerCycle;

 static void init();
 static void advanceTo(u1 const phase, u1 const step);
};

#endif	/* THREEPHASEDRIVER_H */

