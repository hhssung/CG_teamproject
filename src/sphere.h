#pragma once
#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "object.h"

// opengl variables
GLuint	SphereTexture = 0;			// 구의 텍스쳐 정보

// global variables
float	power = kSphereJumpBasicPower;		// 점프 위력 변수
float	max_charge_time = 1.0f;		// 최대 충전 시간
float	min_charge_time = 0.4f;		// 최소 충전 시간
float	charge_range = max_charge_time - min_charge_time;

struct jp_t {//jump 게이지 표현
	bool jumpping_now = false;		// true - 점프버튼을 누르는 중
	float startTime = 0.0f;			// 점프버튼 누른 시간
	float endTime = 0.0f;			// 점프버튼 놓은 시간
	void jump_action(sphere_t& sp);	// 점프효과 적용 함수
	float get_gauge(float t);		// callback 충전게이지 return
} jp; // flags of keys for smooth changes

// implement fuctions
void sphere_t::update(float del_t) {
	angle += angle_speed * del_t;

	model_matrix = mat4::translate(center) *
		mat4::rotate(vec3(0, 0, 1), angle) *
		mat4::scale(radius);
}
void jp_t::jump_action(sphere_t& sp) {
	//jump_once = true;
	float gauge = min((jp.endTime - jp.startTime)/charge_range + min_charge_time, max_charge_time) * power;
	float angle = pointer.angle + PI / 4.0f; // 각도 조정

	sp.angle_speed = -cos(angle) * gauge;
	sp.x_speed += gauge * cos(angle);
	sp.y_speed += gauge * sin(angle);
	power = kSphereJumpBasicPower;					// 원래 파워로 복구
	more_view_angle = 0;					// 원래 시야로 복구
	cam_away.y = 5;							// 원래 시야로 복구
};
float jp_t::get_gauge(float t) {
	return  jumpping_now ? min((t - startTime)/charge_range + min_charge_time, max_charge_time) : 0;
}

// render function
void render_sphere(GLuint program, sphere_t & sphere, float del_t) {
	glBindVertexArray(sphere_vertex_array);
	
	if (SphereTexture != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, SphereTexture);
		glUniform1i(glGetUniformLocation(program, "TEX"), 0);
	}

	sphere.update(del_t);

	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, GL_TRUE, sphere.model_matrix);
	if (b_index_buffer)	glDrawElements(GL_TRIANGLES, M * (N * 3 + 3) * 2, GL_UNSIGNED_INT, nullptr);
	else				glDrawArrays(GL_TRIANGLES, 0, M * (N * 3 + 3) * 2);
}

// creating object functions
inline sphere_t create_sphere() {
	return { vec3(0.0f, 1.0f, 2.0f), 0.5f, 0};
}

sphere_t	sphere = create_sphere();

void reset_sphere() {
	sphere = create_sphere();
	jp.jumpping_now = false;
	jp.startTime = 0.0f;
	jp.endTime = 0.0f;
}
#endif 