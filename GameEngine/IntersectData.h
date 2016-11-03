#pragma once
class IntersectData {
public:
	IntersectData(const bool _doesIntersect, const float _distance) {
		doesIntersect = _doesIntersect;
		distance = _distance;
	};
	bool GetDoesIntersect() const {
		return doesIntersect;
	}
	float GetDistance() const {
		return distance;
	}
private:
	bool doesIntersect;
	float distance;
};