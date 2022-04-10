#pragma once
#ifndef __INTRO_H__
#define __INTRO_H__
#include "object.h"

// opengl variables
GLuint	LogoTexture = 0;
GLuint	IntroTexture[] = { 0, 0, 0 };

float	reading_time = 0.0;				// ���ð�, �ð� ����� ����, ��� �� 0���� �� ��
float	running_time = 0.0f;			// ����ð�, ���� ����� ����, ��� �� 0���� �� ��
/*
	0 - ��Ʈ�� ��� �غ� ���� ( �����ϸ� 1�� ����)
	1 - �ΰ� �ٿ�� �� -> �ΰ� �� �� ����� �Է� ��ٸ��� �� (���콺 ��ư���� ���� ����)
	2+ - ���� 1~ (���콺 Ŭ������ ���� ����)
	...
	-1 - ��Ʈ�� ���� ���� (��� ��� ����)
*/
int		intro_state = -1;
float	intro_logo_proceed_time = 0;	// logo �ð� ����� ����, ��� �� 0���� �� ��
bool	intro_next_text_ready = false;	// "��ư�� �����ÿ�" �ؽ�Ʈ ��¿� ���� ����
bool	intro_logo = false;				// Logo ������ ���� ����
int		intro_descriptor_index = -1;	// -1 �� ��� ���

//	rect structure :  xyz-pos, xy-scale, xyz-axis, rotation_angle
rect_t	introLogo = { vec3(0, 0.3f, 0), vec2(5.0f, 1.3f), vec3(0), 0 };
rect_t	introDescriptor[] = {	// ������� �ѱ�� ���� å
	{ vec3(0, -2.0f, 4.0f), vec2(6.0f, 4.0f), vec3(0), 0 },
	{ vec3(0, -2.0f, 4.0f), vec2(6.0f, 4.0f), vec3(0), 0 },
	{ vec3(0, -2.0f, 4.0f), vec2(6.0f, 4.0f), vec3(0), 0 }
};


void reset_intro_state() {
	intro_state = 0;
}

eGameMode running_intro(float del_t, bool next_click) {
	running_time += del_t;
	eGameMode next_game_mod = eGameMode::MODE_RESET_AND_INTRO;
	float percent;

	switch (intro_state) {
	case -1:
		// not ready to start
		return next_game_mod;
	case 0:
		// ready to start
		intro_logo_proceed_time = 0;
		intro_next_text_ready = false;
		intro_descriptor_index = -1;	// -1 �� ��� ���
		intro_logo_proceed_time = 0;
		intro_logo = true;
		intro_state++;
		break;
	case 1:
		// �ΰ� ���� Ÿ��
		intro_logo_proceed_time += del_t;
		percent = sin(intro_logo_proceed_time * PI / (kMaxIntroLogoProceed * 2));
		if (intro_logo_proceed_time > kMaxIntroLogoProceed) {
			percent = 1.0f;
			intro_next_text_ready = true;
			// ��ư ������ ���� �ܰ�� ��
			if (next_click) {
				intro_logo_proceed_time++;
				introLogo.scale = vec2(0);
				intro_next_text_ready = false;
				intro_logo = false;
				intro_state++;
				break;
			}
		}
		introLogo.scale = vec2(5.0f, 1.3f) * percent * 1.8f;
		break;
	case 2:
		reading_time += del_t;
		if (reading_time > kMaxReadingTime) {
			intro_next_text_ready = true;
			// ��ư ������ ���� �ܰ�� ��
			if (next_click) {
				reading_time = 0;
				intro_logo_proceed_time++;
				intro_next_text_ready = false;
				intro_descriptor_index = 1;
				intro_state++;
				break;
			}
		}
		intro_descriptor_index = 0;
		break;
	case 3:
		reading_time += del_t;
		if (reading_time > kMaxReadingTime) {
			intro_next_text_ready = true;
			// ��ư ������ ���� �ܰ�� ��
			if (next_click) {
				reading_time = 0;
				intro_logo_proceed_time++;
				intro_next_text_ready = false;
				intro_descriptor_index = 2;
				intro_state++;
				break;
			}
		}
		intro_descriptor_index = 1;
		break;
	case 4:
		reading_time += del_t;
		if (reading_time > kMaxReadingTime) {
			intro_next_text_ready = true;
			// ��ư ������ ���� �ܰ�� ��
			if (next_click) {
				reading_time = 0;
				intro_logo_proceed_time++;
				intro_next_text_ready = false;
				intro_descriptor_index = -1;
				intro_state++;
				break;
			}
		}
		intro_descriptor_index = 2;
		break;
	default:
		intro_state = -1;
		intro_descriptor_index = -1;
		next_game_mod = eGameMode::MODE_PLAYING;
	}

	return next_game_mod;
}



// render function
void render_introLogo(GLuint program, rect_t& logo) {
	glBindVertexArray(rect_vertex_array);

	if (LogoTexture != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, LogoTexture);
		glUniform1i(glGetUniformLocation(program, "TEX"), 0);
	}

	mat4 model_matrix = mat4::translate(logo.center) *
		mat4::rotate(logo.axle, logo.angle) *
		mat4::scale(logo.scale.x, logo.scale.y, 0);

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, GL_TRUE, model_matrix);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
}
void render_introBoard(GLuint program) {
	glBindVertexArray(rect_vertex_array);

	if (IntroTexture[intro_descriptor_index] != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, IntroTexture[intro_descriptor_index]);
		glUniform1i(glGetUniformLocation(program, "TEX"), 0);
	}

	mat4 model_matrix = mat4::translate(introDescriptor[intro_descriptor_index].center) *
		mat4::rotate(introDescriptor[intro_descriptor_index].axle, introDescriptor[intro_descriptor_index].angle) *
		mat4::scale(introDescriptor[intro_descriptor_index].scale.x, introDescriptor[intro_descriptor_index].scale.y, 0);

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, GL_TRUE, model_matrix);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
}
#endif 