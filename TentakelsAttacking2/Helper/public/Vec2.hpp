//
// Purpur Tentakel
// 08.08.2022
//

#pragma once
#include <string>
#ifdef USE_FMT_FORMAT
#include <fmt/format.h>
#else
#include <format>
#endif
#include <stdexcept>
#include <cmath>

/**
 * contains and manage 2 values.
 */
template<class T>
struct Vec2 final {
	T x, y; ///< contans the 2 values the Vec is holding,

	/**
	 * ctor.
	 * only initialisation.
	 */
	Vec2(T x, T y)
		: x(x), y(y) { }
	/**
	 * generates a exect copy of the Vec.
	 */
	Vec2(const Vec2<T>& toCopy)
		: x(toCopy.x), y(toCopy.y) {}


	/**
	 * returns a new Vec to match a length of 1 while not changing the direkction.
	 */
	[[nodiscard]] Vec2<T> Normalize() const {
		double length = Length();
		return Vec2<T>(x / length, y / length);
	}
	/**
	 * returns the lengs of the Vec.
	 */
	[[nodiscard]] double Length() const {
		double X = static_cast<double>(x);
		double Y = static_cast<double>(y);
		return std::sqrt((X * X) + (Y * Y));
	}

	/**
	 * checks if the Vec are completly equal.
	 */
	bool operator== (const Vec2<T>& other) const {
		return x == other.x && y == other.y;
	}
	/**
	 * adds to Vecs and returns a new one.
	 */
	Vec2<T> operator+ (const Vec2<T>& other) const {
		return Vec2<T>(x + other.x, y + other.y);
	}
	/**
	 * substracts to Vecs and returns a new one.
	 */
	Vec2<T> operator- (const Vec2<T>& other) const {
		return Vec2<T>(x - other.x, y - other.y);
	}
	/**
	 * multiplyes to Vecs and returns a new one.
	 */
	Vec2<T> operator* (const Vec2<T>& other) const {
		return Vec2<T>(x * other.x, y * other.y);
	}

	/**
	 * gereates a new Vec with a new datatype and returns it.
	 */
	template<typename Scalar>
	Vec2<Scalar> To() const {
		static_assert(std::is_floating_point_v<Scalar>, "floting point required");
		return Vec2<Scalar>(static_cast<Scalar>(x), static_cast<Scalar>(y));
	}
	/**
	 * returns a string representation of the Vec.
	 */
	[[nodiscard]] std::string ToString() const {
		return "X: " + std::to_string(x) + " Y: " + std::to_string(y);
	}
};

/**
 * mitliplayes a Vec with a numeber and returns a new Vec.
 */
template <typename T>
Vec2<T> operator* (const Vec2<T>& vector, const T number) {
	return Vec2<T>(vector.x * number, vector.y * number);
}
/**
 * mitliplayes a number with a Vec and returns a new Vec.
 */
template <typename T>
Vec2<T> operator*(const T number, const Vec2<T>& vector) {
	return vector * number;
}

/**
 * devides a Vec with a number and returns a new Vec.
 * if devide by zero: an exception is thrown.
 */
template <typename T>
Vec2<T> operator/ (const Vec2<T>& vector, const T number) {
	if (number == 0) {
		throw std::runtime_error("devide by zero");
	}
	return Vec2<T>(vector.x / number, vector.y / number);
}