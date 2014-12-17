/*
 * AHCC interface for Wizzcat 12kHz Protracker replay (STE only)
 * based on the Wizzcat interface by GT Turbo / Cerebral Vortex for GFABASIC
 *
 * AHCC interface (c) 2011 by Simon Sunnyboy / Paradize
 */

 #ifndef _WIZZCAT_H
    #define _WIZZCAT_H

    /**
     * This function relocates the STE Wizzcat replay routine and makes it ready to use.
     */
    void Wizzcat_Init(void);
    /**
     * This function starts playing a given Protracker file from address tune.
     * tune_end defines the end of the tune address and should include approx 16KB
     * of workspace behind the modfile. If the music is 50K long, add buffer space behind.
     */
    void Wizzcat_Play(void *tune, void *tune_end);
    /**
     * This function stops the currently playing tune with the Wizzcat replay.
     */
    void Wizzcat_Stop(void);
 #endif
