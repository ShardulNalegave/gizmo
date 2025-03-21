
#ifndef GIZMO_AUDIO_H
#define GIZMO_AUDIO_H

#include "stdint.h"

typedef enum {
    AUDIO_MASTER_CONTROL_ON = 0b10000000,
    AUDIO_MASTER_CONTROL_CH4_ON = 0b00001000,
    AUDIO_MASTER_CONTROL_CH3_ON = 0b00000100,
    AUDIO_MASTER_CONTROL_CH2_ON = 0b00000010,
    AUDIO_MASTER_CONTROL_CH1_ON = 0b00000001,
} audio_master_control_t;

typedef enum {
    SOUND_PANNING_CH4_LEFT = 0b10000000,
    SOUND_PANNING_CH3_LEFT = 0b01000000,
    SOUND_PANNING_CH2_LEFT = 0b00100000,
    SOUND_PANNING_CH1_LEFT = 0b00010000,
    SOUND_PANNING_CH4_RIGHT = 0b00001000,
    SOUND_PANNING_CH3_RIGHT = 0b00000100,
    SOUND_PANNING_CH2_RIGHT = 0b00000010,
    SOUND_PANNING_CH1_RIGHT = 0b00000001,
} sound_panning_t;

typedef struct {
    // Global Control Registers
    uint8_t master_volume_and_vin_panning;   // NR50 - 0xFF24
    uint8_t sound_panning;                   // NR51 - 0xFF25
    uint8_t audio_master_control;            // NR52 - 0xFF26

    // Sound Channel 1 - Pulse with Period Sweep
    uint8_t channel_1_sweep;                        // NR10 - 0xFF10
    uint8_t channel_1_length_timer_and_duty_cycle;  // NR11 - 0xFF11
    uint8_t channel_1_volume_and_envelope;          // NR12 - 0xFF12
    uint8_t channel_1_period_low;                   // NR13 - 0xFF13
    uint8_t channel_1_period_high_and_control;      // NR14 - 0xFF14

    // Sound Channel 2 - Pulse
    uint8_t channel_2_length_timer_and_duty_cycle;  // NR21 - 0xFF16
    uint8_t channel_2_volume_and_envelope;          // NR22 - 0xFF17
    uint8_t channel_2_period_low;                   // NR23 - 0xFF18
    uint8_t channel_2_period_high_and_control;      // NR24 - 0xFF19

    // Sound Channel 3 - Wave output
    uint8_t channel_3_dac_enable;                   // NR30 - 0xFF1A
    uint8_t channel_3_length_timer;                 // NR31 - 0xFF1B
    uint8_t channel_3_output_level;                 // NR32 - 0xFF1C
    uint8_t channel_3_period_low;                   // NR33 - 0xFF1D
    uint8_t channel_3_period_high_and_control;      // NR34 - FF1E
    uint8_t channel_3_wave_pattern_ram[16];         // 0xFF30-0xFF3F

    // Sound Channel 4 - Noise
    uint8_t channel_4_length_timer;                 // NR41 - 0xFF20
    uint8_t channel_4_volume_and_envelope;          // NR42 - 0xFF21
    uint8_t channel_4_frequency_and_randomness;     // NR43 - 0xFF22
    uint8_t channel_4_control;                      // NR44 - 0xFF23
} gizmo_audio_t;

#endif