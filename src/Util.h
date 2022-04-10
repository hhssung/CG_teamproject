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

static const float kSphereRotationSpeed = 4.3f;			// �� ȸ���ӵ� ���
static const vec2 kFloorElasticity = vec2(0.35f);			// �ٴ�
static const vec2 kWallElasticity = vec2(0.13f);			// ��
static const vec2 kBasicPlateElasticity = vec2(0.43f, 0.43f);	// �⺻ ����
static const vec2 kIcePlateElasticity = vec2(0.05f, 0.5f);	// ���� ����
static const vec2 kStickyPlateElasticity = vec2(0.9f, 0.9f);	// ������ ����
static const vec2 kJumpPlateElasticity = vec2(0.43f, 0.43f);	// ���� ����

static const float kSpaceAnimationSpeed = 0.005f;

static const float kSphereJumpBasicPower = 12.3f;

static const float kStormAngleBasicSpeed = 0.6f;		// �ð��� ��ǳ�� �⺻ ȸ�� �ӵ�
static const float kStormIncreaseSpeed = 12.0f;				// �ð��� ��ǳ�� ȸ�� �ӵ� ������
static const float kStormMaxTime = 3.5f;				// �ð��� ��ǳ ���� ��� �ð�

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
static const char* kCollisionWithPlate_1SoundPath = "../bin/sound/iron_plate.wav";	// ö��
static const char* kCollisionWithPlate_2SoundPath = "../bin/sound/jump_1.wav";
static const char* kCollisionWithPlate_3SoundPath = "../bin/sound/jump_2.wav";		// ��ƼŰ
static const char* kCollisionWithPlate_4SoundPath = "../bin/sound/jump_3_ice.wav";		// ����
static const char* kIntroSoundPath = "../bin/sound/intro.wav";
static const char* kOutroSoundPath = "../bin/sound/outro.wav";
static const char* kPlayingSoundPath = "../bin/sound/playing.wav";
static const char* kStormSoundPath = "../bin/sound/storm.wav";
static const char* kBombSoundPath = "../bin/sound/bomb.wav";



#endif // !__UTIL_H__