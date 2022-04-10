#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__

#include "irrKlang/irrKlang.h"	// irrKlang for sound
#include "Util.h"
#pragma comment(lib, "irrKlang.lib")

// irrKlang objects
irrklang::ISoundEngine* engine = nullptr;
irrklang::ISoundSource* sound_src = nullptr;
irrklang::ISoundSource* sound_floor_src = nullptr;
irrklang::ISoundSource* sound_wall_src = nullptr;
irrklang::ISoundSource* sound_plate_1_src = nullptr;
irrklang::ISoundSource* sound_plate_2_src = nullptr;
irrklang::ISoundSource* sound_plate_3_src = nullptr;
irrklang::ISoundSource* sound_plate_4_src = nullptr;
irrklang::ISoundSource* sound_intro_src = nullptr;
irrklang::ISoundSource* sound_outro_src = nullptr;
irrklang::ISoundSource* sound_playing_src = nullptr;
irrklang::ISoundSource* sound_storm_src = nullptr;
irrklang::ISoundSource* sound_bomb_src = nullptr;

bool	sound_init() {
	// create engine
	engine = irrklang::createIrrKlangDevice();
	if (!engine) {
		return false;
	}

	//add sound source from the sound file
	// sound_src =		  engine->addSoundSourceFromFile(colision_sound_path);
	sound_floor_src = engine->addSoundSourceFromFile(kCollisionWithFloorSoundPath);
	sound_wall_src =  engine->addSoundSourceFromFile(kCollisionWithWallSoundPath);
	sound_plate_1_src = engine->addSoundSourceFromFile(kCollisionWithPlate_1SoundPath);
	sound_plate_2_src = engine->addSoundSourceFromFile(kCollisionWithPlate_2SoundPath);
	sound_plate_3_src = engine->addSoundSourceFromFile(kCollisionWithPlate_3SoundPath);
	sound_plate_4_src = engine->addSoundSourceFromFile(kCollisionWithPlate_4SoundPath);

	sound_intro_src = engine->addSoundSourceFromFile(kIntroSoundPath);
	sound_outro_src = engine->addSoundSourceFromFile(kOutroSoundPath);
	sound_playing_src = engine->addSoundSourceFromFile(kPlayingSoundPath);
	sound_storm_src = engine->addSoundSourceFromFile(kStormSoundPath);
	sound_bomb_src = engine->addSoundSourceFromFile(kBombSoundPath);

	return true;
}

#endif // !__SOUND_H__
