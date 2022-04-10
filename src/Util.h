#pragma once
#ifndef __UTIL_H__
#define __UTIL_H__

using namespace std;

// main.cpp

static const char* kWindowName = "Team Project - Funny Game!";
static const char* kVertexShaderPath = "../bin/shaders/teamproject.vert";
static const char* kFragmentShaderPath = "../bin/shaders/teamproject.frag";
static const char* kPlayTimeString = "Play Time  : ";
static const char* kNumberOfJumpString = "Jump Count : ";

enum class eGameMode {
	MODE_RESET_AND_INTRO,
	MODE_PLAYING,
	MODE_STORM,
	MODE_EXPLOSION,
	MODE_ENDING_CREDIT
};

// constants

static const float	kMaxIntroLogoProceed = 4.0f;
static const float	kMaxReadingTime = 1.5f;

static const float kSphereRotationSpeed = 4.3f;			// 구 회전속도 계수
static const vec2 kFloorElasticity = vec2(0.35f);			// 바닥
static const vec2 kWallElasticity = vec2(0.13f);			// 벽
static const vec2 kBasicPlateElasticity = vec2(0.43f, 0.43f);	// 기본 발판
static const vec2 kIcePlateElasticity = vec2(0.05f, 0.5f);	// 얼음 발판
static const vec2 kStickyPlateElasticity = vec2(0.9f, 0.9f);	// 끈끈이 발판
static const vec2 kJumpPlateElasticity = vec2(0.43f, 0.43f);	// 점프 발판

static const float kSpaceAnimationSpeed = 0.005f;

static const float kSphereJumpBasicPower = 12.3f;

static const float kStormAngleBasicSpeed = 0.6f;		// 시공의 폭풍의 기본 회전 속도
static const float kStormIncreaseSpeed = 12.0f;				// 시공의 폭풍의 회전 속도 증가량
static const float kStormMaxTime = 3.5f;				// 시공의 폭풍 진입 경과 시간

static const char* kFontPath = "../bin/fonts/consola.ttf";
static const char* kVertexTextPath = "../bin/shaders/text.vert"; // text vertex shaders
static const char* kFragmentTextPath = "../bin/shaders/text.frag"; // text fragment shaders

// image

static const char* kLogoImagePath = "../bin/images/logo.png";
static const char* kIntroImagePath[] = {
	"../bin/images/intro_capture_1.png",
	"../bin/images/intro_capture_2.png",
	"../bin/images/intro_capture_3.png"
};
static const char* kFloorImagePath = "../bin/images/lava_floor.png";
static const char* kExplosionImagePath = "../bin/images/explosion.png";
static const char* kBasicPlateImagePath = "../bin/images/rock.png";
static const char* kIcePlateImagePath = "../bin/images/ice.jpg";
static const char* kStickyPlateImagePath = "../bin/images/sticky.jpg";
static const char* kJumpPlateImagePath = "../bin/images/whitehole.jpg";
static const char* kPointerImagePath = "../bin/images/pointer.jpg";
static const char* kSpaceImagePath = "../bin/images/space.jpg";
static const char* kSphereImagePath = "../bin/images/earth.png";
static const char* kStormImagePath = "../bin/images/storm.jpg";
static const char* kBrickImagePath = "../bin/images/lava.png";

// sound

static const char* kCollisionSoundPath = "../bin/sound/colision.wav";
static const char* kCollisionWithFloorSoundPath = "../bin/sound/grass.wav";
static const char* kCollisionWithWallSoundPath = "../bin/sound/bricks.wav";
static const char* kCollisionWithPlate_1SoundPath = "../bin/sound/iron_plate.wav";	// 철판
static const char* kCollisionWithPlate_2SoundPath = "../bin/sound/jump_1.wav";
static const char* kCollisionWithPlate_3SoundPath = "../bin/sound/jump_2.wav";		// 스티키
static const char* kCollisionWithPlate_4SoundPath = "../bin/sound/jump_3_ice.wav";		// 얼음
static const char* kIntroSoundPath = "../bin/sound/intro.wav";
static const char* kOutroSoundPath = "../bin/sound/outro.wav";
static const char* kPlayingSoundPath = "../bin/sound/playing.wav";
static const char* kStormSoundPath = "../bin/sound/storm.wav";
static const char* kBombSoundPath = "../bin/sound/bomb.wav";



#endif // !__UTIL_H__