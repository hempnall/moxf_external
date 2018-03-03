//
//  moxf_types.h
//  rtmidi_test
//
//  Created by James Hook on 28/02/2018.
//  Copyright © 2018 James Hook. All rights reserved.
//

#ifndef moxf_types_h
#define moxf_types_h

typedef unsigned char midi7_t;
typedef uint8_t midi_channel_t;
typedef uint8_t part_number_t;
typedef uint16_t midi2_7_t;



struct common_information
{
    midi7_t dummy;
};

struct     part_information_36_00
{
    midi7_t bank_select_msb;
    midi7_t bank_select_lsb;
    midi7_t program_number;
    midi_channel_t receive_channel;
    midi7_t mono_poly;
    midi7_t velocity_limit_low;
    midi7_t velocity_limit_high;
    midi7_t note_limit_low;
    midi7_t note_limit_high;
    midi7_t pitch_bend_range_upper;
    midi7_t pitch_bend_range_lower;
    midi7_t velocity_sensitivity_depth;
    midi7_t velocity_sensitivity_offset;
    midi7_t volume;
    midi7_t pan;
    midi2_7_t detune;
    midi7_t reverb_send;
    midi2_7_t chorus_send;
    midi7_t reserved1;
    midi7_t dry_level;
    midi7_t note_shift;
    midi7_t reserved2;
    midi7_t param_with_voice;
    midi7_t voice_with_arp;
    midi7_t portamento_switch;
    midi7_t portamento_time;
    midi7_t portamento_mode;
    midi7_t reserved3;
    midi7_t usb_audio_output_select_mode;
    midi7_t receive_various1; // 0x1f
    midi7_t receive_various2; // 0x20
    midi7_t receive_various3; // 0x21
    midi7_t voice_element_pan;
    midi7_t aeg_attack_time;
    midi7_t aeg_decay_time;
    midi7_t aeg_sustain_time;
    midi7_t aeg_release_time;
    midi7_t feg_attack_time;
    midi7_t feg_decay_time;
    midi7_t feg_sustain_time;
    midi7_t feg_release_time;
    midi7_t feg_depth;
    midi7_t reserved4;
    midi7_t filter_cutoff_frequency;
    midi7_t filter_resonance_width;
    midi7_t reserved5;
    midi2_7_t eq_low_frequency;
    midi7_t eq_low_gain;
    midi7_t reserved6;
    midi2_7_t eq_mid_frequency;
    midi7_t eq_mid_gain;
    midi7_t eq_mid_q;
    midi2_7_t eq_high_frquency;
    midi7_t eq_high_gain;
    midi7_t reserved;
    midi7_t assignable_knob1_value;
    midi7_t assignable_knob2_value;
};

struct arp_information_38_00
{
    midi7_t arp_switch;
    midi7_t arp_midi_out_switch;
    midi7_t arp_transmit_channel;
    midi7_t arp_play_only;
    midi7_t arp_fixed_sdbd;
    midi7_t reserved1;
    midi7_t arp_loop;
    midi7_t arp_hold;
    midi7_t arp_unit_multiply;
    midi7_t arp_note_limit_low;
    midi7_t arp_note_limit_high;
    midi7_t arp_velocity_limit_low;
    midi7_t arp_velocity_limit_high;
    midi7_t arp_key_mode;
    midi7_t arp_velocity_mode;
    midi7_t arp_change_timing;
    midi7_t arp_quantize_value;
    midi7_t arp_quantize_strength;
    midi2_7_t arp_velocity_rate;
    midi2_7_t arp_gate_time_rate;
    midi7_t reserved2;
    midi7_t reserved3;
    midi7_t reserved4;
    midi7_t reserved5;
    midi2_7_t arp_swing;
    midi7_t arp_accent_velocity_threshold;
    midi7_t arp_accent_start_quantize;
    midi7_t arp_octave_range;
    midi7_t arp_output_octave_shift;
    midi7_t arp_trigger_mode;
    midi7_t arp_random_sfx;
    midi7_t arp_random_sfx_keyon_control;
    midi7_t arp_random_sfx_velocity_offset;
    midi2_7_t arp_assign_velocity_rate_offset_sf1;
    midi2_7_t arp_assign_gate_time_rate_offset_sf1;
    midi2_7_t arp_assign_velocity_rate_offset_sf2;
    midi2_7_t arp_assign_gate_time_rate_offset_sf2;
    midi2_7_t arp_assign_velocity_rate_offset_sf3;
    midi2_7_t arp_assign_gate_time_rate_offset_sf3;
    midi2_7_t arp_assign_velocity_rate_offset_sf4;
    midi2_7_t arp_assign_gate_time_rate_offset_sf4;
    midi2_7_t arp_assign_velocity_rate_offset_sf5;
    midi2_7_t arp_assign_gate_time_rate_offset_sf5;
    midi2_7_t arp_assign_velocity_rate_offset_sf6;
    midi2_7_t arp_assign_gate_time_rate_offset_sf6;
    midi2_7_t arp_sf1_assign_type;
    midi2_7_t arp_sf2_assign_type;
    midi2_7_t arp_sf3_assign_type;
    midi2_7_t arp_sf4_assign_type;
    midi2_7_t arp_sf5_assign_type;
    midi2_7_t arp_sf6_assign_type;
};


typedef void(*part_callback_fn) ( part_number_t pp , part_information_36_00* part_info );
typedef void(*arp_callback_fn)  ( part_number_t pp , arp_information_38_00* arp_info );


#endif /* moxf_types_h */
