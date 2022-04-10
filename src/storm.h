#pragma once
#ifndef __STORM_H__
#define __STORM_H__
#include "object.h"

// opengl variables
GLuint	StormTexture = 0;

// variable
vec3 sphere_pos;		// ���� ��ǳ������ �̵�
vec3 del_sphere_pos;
vec3 cam_at;			// ī�޶� ��ǳ������ �̵�
vec3 del_cam_at;
vec3 cam_eye;			// ī�޶� ��ǳ������ �̵�
vec3 del_cam_eye;

// render function
void render_storm(GLuint program, circle_t& storm, float del_t) {
	glBindVertexArray(circle_vertex_array);

	if (StormTexture != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, StormTexture);
		glUniform1i(glGetUniformLocation(program, "TEX"), 0);
	}

	storm.angle += storm.angle_speed * del_t;

	mat4 model_matrix = mat4::translate(storm.center) *
		mat4::rotate(vec3(0, 0, 1.0f), storm.angle) *
		mat4::scale(storm.scale, storm.scale, 0);

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, GL_TRUE, model_matrix);
	glDrawElements(GL_TRIANGLES, 2 * 3 * (N + 1), GL_UNSIGNED_INT, nullptr);
}
bool circle_t::in_storm(vec3 sp_center, float sp_r){
	// ���� ��ġ�� ũ�⸦ �޾� �ð��� ��ǳ�� ������ �ִ��� �Ǵ��Ͽ� return
	return (center - sp_center).length() < scale + sp_r ? 1 : 0;
}
int circle_t::go_to_storm(sphere_t & sp, camera & cam, float del_t) {
	proceed += del_t;
	float percent = sin(proceed * PI / (kStormMaxTime * 2));
	if (proceed > kStormMaxTime) return 1;

	angle_speed = kStormAngleBasicSpeed + kStormIncreaseSpeed * percent;
	sp.center = sphere_pos + del_sphere_pos * percent;
	cam.at = cam_at + del_cam_at * percent;
	cam.eye = cam_eye + del_cam_eye * percent;

	return 0;
}

// creating object functions
inline circle_t create_storm() //function to save the information about walls - 3 walls
{
	return { vec3(0.0f, 64.0f, 1.0f), 1.0f, 0.0f, 0.0f, 0.6f};	// �� ���� ����
	//return { vec3(2.0f, 2.0f, 2.0f), 1.0f, 0.0f };		// �ٷ� ���� ����
}

circle_t		storm = create_storm();

void reset_storm() {
	sphere_pos = 0;		// ���� ��ǳ������ �̵�
	del_sphere_pos = 0;
	cam_at = 0;			// ī�޶� ��ǳ������ �̵�
	del_cam_at = 0;
	cam_eye = 0;			// ī�޶� ��ǳ������ �̵�
	del_cam_eye = 0;
	storm = create_storm();
}
#endif 