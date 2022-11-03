#pragma once

class Rainbow {
	
	static constexpr float PI = 3.1415936f;
	
public:
	static sf::Color nextColor(float t) {
		const float r = sin(t);
		const float g = sin(t + 0.33f * 2.0f * PI);
		const float b = sin(t + 0.66f * 2.0f * PI);
		return { static_cast<uint8_t>(255.0f * r * r),
				static_cast<uint8_t>(255.0f * g * g),
				static_cast<uint8_t>(255.0f * b * b) };
	}
	
};