#pragma once

#ifndef __PHYSICS_H__
#define __PHYSICS_H__
#include "object.h"

float gravity = 12.3f;  // 중력값	

// collide fuction
bool	floor_collide(float sphere_center_y, float floor_y, float radius)	// 바닥과 충돌 감지
{
	if (floor_y + radius > sphere_center_y)
	{
		return 1;
	}
	return 0;
}
bool	wall_collide(float sphere_center_x, float wall_x, float radius)	 // 뒤의 벽 제외
{
	if (abs(wall_x - sphere_center_x) < radius)
	{
		return 1;
	}
	return 0;
}

// plate의 중점, plate의 크기, 구의 좌표값, 반지름
bool	plate_collide_1(float pl_x, float pl_y, float plsize_x, float plsize_y, float center_x, float center_y, float radius)	// [1] 발판과 충돌
{
	if (pl_y + plsize_y > center_y && pl_y - plsize_y < center_y && center_x < pl_x && pl_x - plsize_x < center_x + radius)	// [1] y 범위 조건 만족, x범위 조건 만족,  x값 충돌
	{
		return 1;
	}
	return 0;
}
bool	plate_collide_2(float pl_x, float pl_y, float plsize_x, float plsize_y, float center_x, float center_y, float radius)	// [2] 발판과 충돌
{
	if (pl_x + plsize_x > center_x && pl_x - plsize_x < center_x && center_y < pl_y && pl_y - plsize_y < center_y + radius)	// [2] x 범위 조건 만족, y값 충돌
	{
		return 1;
	}
	return 0;
}
bool	plate_collide_3(float pl_x, float pl_y, float plsize_x, float plsize_y, float center_x, float center_y, float radius)	// [3] 발판과 충돌
{
	if (pl_y + plsize_y > center_y && pl_y - plsize_y < center_y && center_x > pl_x && pl_x + plsize_x > center_x - radius)
	{
		return 1;
	}
	return 0;
}
bool	plate_collide_4(float pl_x, float pl_y, float plsize_x, float plsize_y, float center_x, float center_y, float radius)	// [4] 발판과 충돌
{
	if (pl_x + plsize_x > center_x && pl_x - plsize_x < center_x && center_y > pl_y && pl_y + plsize_y > center_y - radius)
	{
		return 1;
	}
	return 0;
}

// 실시간 구 좌표 값 변경 && 구 충돌 구현
int		sphere_t::collision(std::vector <rect_t>& floors, std::vector <rect_t>& walls, std::vector <plate_t>& plates, float del_t)
{
	/*
		is_collide 충돌 대상에 관한 정보
		0 - 충돌 없음
		1 - 정체불명의 충돌
		2 - 바닥과 충돌
		3 - 벽과 충돌
		4+ - 발판과 충돌
	*/
	int		is_collide = 0;						// 충돌 대상 정보, return 값
	vec3	p0 = center;						// 이전 구 좌표 저장
	float	maximum_friction = 0.27f * del_t;	// 이동거리에 따른 정지 판정 기준 
	y_speed -= gravity * del_t;					// 중력 적용

	vec3	pn = p0 + vec3(x_speed, y_speed, 0) * del_t;	// 공의 다음 위치 계산

	if (floor_collide(pn.y, floors[0].center.y, radius))	//바닥과 충돌 시
	{
		center.y = floors[0].center.y + radius;
		if (abs(p0.y - center.y) > maximum_friction) is_collide = 3;
		if (y_speed < 0) {
			y_speed = -y_speed;
		}
		x_speed -= x_speed * kFloorElasticity.x;
		y_speed -= y_speed * kFloorElasticity.y;
		if (abs(x_speed) < maximum_friction) {
			x_speed = 0;
		}
		if (abs(y_speed) < maximum_friction) {
			y_speed = 0;
		}

		angle_speed = -x_speed * kSphereRotationSpeed;

	}

	else if (wall_collide(pn.x, walls[1].center.x, radius))	//벽1과 충돌 시
	{
		// 왼쪽 벽
		center.x = walls[1].center.x + radius;
		if (abs(p0.x - center.x) > maximum_friction) is_collide = 3;
		if (x_speed < 0) {
			x_speed = -x_speed;
		}
		x_speed -= x_speed * kWallElasticity.x;
		y_speed -= y_speed * kWallElasticity.y;
		if (abs(x_speed) < maximum_friction) {
			x_speed = 0;
		}
		if (abs(y_speed) < maximum_friction) {
			y_speed = 0;
		}

		angle_speed = -y_speed * kSphereRotationSpeed;

	}

	else if (wall_collide(pn.x, walls[2].center.x, radius))	//벽2과 충돌 시
	{
		center.x = walls[2].center.x - radius;
		if (abs(p0.x - center.x) > maximum_friction) is_collide = 3;
		if (x_speed > 0) {
			x_speed = -x_speed;
		}
		x_speed -= x_speed * kWallElasticity.x;
		y_speed -= y_speed * kWallElasticity.y;
		if (abs(x_speed) < maximum_friction) {
			x_speed = 0;
		}
		if (abs(y_speed) < maximum_friction) {
			y_speed = 0;
		}

		angle_speed = -y_speed * kSphereRotationSpeed;

	}

	for (auto& plates : plates)
	{
		float pl_x = plates.center.x, pl_y = plates.center.y;				// 발판의 x, y좌표
		float plsize_x = plates.scale.x / 2, plsize_y = plates.scale.y / 2;	// 발판의 x, y크기의 절반
		pl_y += plsize_y;	// 발판 높이 보정

		if ((pl_x - pn.x) * (pl_x - pn.x) + (pl_y - pn.y) * (pl_y - pn.y) > (radius + plsize_x + plsize_y) * (radius + plsize_x + plsize_y))
		{
			// 발판과의 충돌이 없음
			continue;
		}
		if (plate_collide_1(pl_x, pl_y, plsize_x, plsize_y, pn.x, pn.y, radius))
		{
			// 왼쪽면과 충돌 처리
			center.x = pl_x - plsize_x - radius;
			if (abs(p0.x - center.x) > maximum_friction) is_collide = 3 + plates.type;
			if (x_speed > 0) {
				x_speed = -x_speed;
			}
			x_speed -= x_speed * kBasicPlateElasticity.x;
			y_speed -= y_speed * kBasicPlateElasticity.y;
			if (abs(x_speed) < maximum_friction) {
				x_speed = 0;
			}
			if (abs(y_speed) < maximum_friction) {
				y_speed = 0;
			}

			angle_speed = -y_speed * kSphereRotationSpeed;
		}
		if (plate_collide_2(pl_x, pl_y, plsize_x, plsize_y, pn.x, pn.y, radius))
		{
			// 아랫면과 충돌 처리
			center.y = pl_y - plsize_y - radius;
			if (abs(p0.y - center.y) > maximum_friction) is_collide = 3 + plates.type;
			if (y_speed > 0) {
				y_speed = -y_speed;
			}
			x_speed -= x_speed * kBasicPlateElasticity.x;
			y_speed -= y_speed * kBasicPlateElasticity.y;
			if (abs(x_speed) < maximum_friction) {
				x_speed = 0;
			}
			if (abs(y_speed) < maximum_friction) {
				y_speed = 0;
			}
			angle_speed = -x_speed * kSphereRotationSpeed;
		}
		if (plate_collide_3(pl_x, pl_y, plsize_x, plsize_y, pn.x, pn.y, radius))
		{
			// 오른쪽 면과 충돌 처리
			center.x = pl_x + plsize_x + radius;
			if (abs(p0.x - center.x) > maximum_friction) is_collide = 3 + plates.type;
			if (x_speed < 0) {
				x_speed = -x_speed;
			}
			x_speed -= x_speed * kBasicPlateElasticity.x;
			y_speed -= y_speed * kBasicPlateElasticity.y;
			if (abs(x_speed) < maximum_friction) {
				x_speed = 0;
			}
			if (abs(y_speed) < maximum_friction) {
				y_speed = 0;
			}
			angle_speed = -y_speed * kSphereRotationSpeed;
		}
		if (plate_collide_4(pl_x, pl_y, plsize_x, plsize_y, pn.x, pn.y, radius))
		{
			// 위쪽면과 충돌 처리
			float new_ex, new_ey;	// 발판 종류마다 마찰계수 다름
			switch (plates.type)
			{
			case 1:
				new_ex = kBasicPlateElasticity.x;
				new_ey = kBasicPlateElasticity.y;
				break;
			case 2:
				new_ex = kIcePlateElasticity.x;
				new_ey = kIcePlateElasticity.y;
				break;
			case 3:
				new_ex = kStickyPlateElasticity.x;
				new_ey = kStickyPlateElasticity.y;
				break;
			case 4:
				new_ex = kJumpPlateElasticity.x;
				new_ey = kJumpPlateElasticity.y;
				break;
			}
			center.y = pl_y + plsize_y + radius;
			if (abs(p0.y - center.y) > maximum_friction) is_collide = 3 + plates.type;
			if (y_speed < 0) {
				y_speed = -y_speed;
			}
			x_speed -= x_speed * new_ex;
			y_speed -= y_speed * new_ey;
			if (abs(x_speed) < maximum_friction) {
				x_speed = 0;
			}
			if (abs(y_speed) < maximum_friction) {
				y_speed = 0;
			}
			angle_speed = -x_speed * kSphereRotationSpeed;
		}
	}

	center += vec3(x_speed, y_speed, 0) * del_t;	// 실제 위치 계산

	if ((p0 - center).length() < maximum_friction) {
		// 매우 작은 움직임 발생
		if (stop_flag) {
			// 계속 정지중
			paused_time += del_t;
			if (paused_time > 0.5f) {
				// 특정 시간 이상 정지 시 움직이지 않음 으로 확정 (가만히 있음)
				is_moving = false;
			}
		}
		else {
			// 구의 정지를 확인
			stop_flag = true;
			paused_time = del_t;
		}
	}
	else {
		// 움직이고 있음
		is_moving = true;
		stop_flag = false;
	}

	return is_collide;
}

#endif