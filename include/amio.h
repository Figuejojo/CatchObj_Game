#ifndef AMIO_H
#define AMIO_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

// Limits
#define MAX_AUDIO_SAMPLE_NAME_LENGTH 100
#define MAX_NUMBER_SAMPLES 10
#define MAX_NUMBER_INSTANCES 100

// Types
#define PLAY_ONCE 0
#define PLAY_LOOP 1

void amio_init_audio(void);

void amio_load_sample(const char* sample_name, const char* sample_path);

void amio_add_sample_instance(const char* sample_name, uint8_t type, float volume);

void amio_update_audio(void);

void amio_destroy_audio(void);

#endif
