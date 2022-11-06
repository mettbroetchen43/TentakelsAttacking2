//
// Purpur Tentakel
// 08.08.2022
//

#pragma once
#include <string>
#include <format>
#include <stdexcept>
#include <cmath>

template<class T>
struct Vec2 final {
	T x, y;

	Vec2(T x, T y)
		: x(x), y(y) {
		static_assert(std::is_floating_point_v<T>, "floting point required");
	}
	Vec2(const Vec2<T>& toCopy)
		: x(toCopy.x), y(toCopy.y) {}


	[[nodiscard]] Vec2<T> Normalize() const {
		double length = Length();
		return Vec2<T>(x / length, y / length);
	}
	[[nodiscard]] double Length() const {
		double X = static_cast<double>(x);
		double Y = static_cast<double>(y);
		return std::sqrt((X * X) + (Y * Y));
	}
	[[nodiscard]] std::string Display() const {
		return std::format("x -> {} / y -> {}", x, y);
	}

	bool operator== (const Vec2<T>& other) const {
		return x == other.x && y == other.y;
	}
	Vec2<T> operator+ (const Vec2<T>& other) const {
		return Vec2<T>(x + other.x, y + other.y);
	}
	Vec2<T> operator- (const Vec2<T>& other) const {
		return Vec2<T>(x - other.x, y - other.y);
	}
	Vec2<T> operator* (const Vec2<T>& other) const {
		return Vec2<T>(x * other.x, y * other.y);
	}

	template<typename To>
	Vec2<To> To() const {
		static_assert(std::is_floating_point_v<To>, "floting point required");
		return Vec2<To>(static_cast<To>(x), static_cast<To>(y));
	}
	[[nodiscard]] std::string ToString() const {
		return "X: " + std::to_string(x) + " Y: " + std::to_string(y);
	}
};

template <typename T>
Vec2<T> operator* (const Vec2<T>& vector, const T number) {
	return Vec2<T>(vector.x * number, vector.y * number);
}
template <typename T>
Vec2<T> operator*(const T number, const Vec2<T>& vector) {
	return vector * number;
}

template <typename T>
Vec2<T> operator/ (const Vec2<T>& vector, const T number) {
	if (number == 0) {
		throw std::runtime_error("devide by zero");
	}
	return Vec2<T>(vector.x / number, vector.y / number);
}