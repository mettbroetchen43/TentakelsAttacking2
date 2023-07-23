//
// Purpur Tentakel
// 23.07.2023
//

#pragma once
#include "UIElement.hpp"

class CountRing final : public UIElement {
private:
	Vector2 m_absolutePos; ///< contains the absolute position
	float m_relativeDotSize; ///<< contains the relative dot size
	int m_absoluteDotSize; ///<< contains the relative dot size
	float m_relativeRingSize; ///< contains the absolute outer size
	int m_absoluteRingSize; ///< contains the absolute outer size
	Color m_dotColor{ BLACK }; //< contains the dot color
	Color m_ringColor{ GREY_50 }; //< contains the ring color

public:

	CountRing(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, float innerSize, float ringSize);

	/**
	 * returns the dot color.
	 */
	[[nodiscard]] Color GetDotColor() const;
	/**
	 * sets a new color the dot is rendered with.
	 */
	void SetDotColor(Color color);
	/**
	 * returns the ring color.
	 */
	[[nodiscard]] Color GetRingColor() const;
	/**
	 * sets a new color the ring is rendered with.
	 */
	void SetRingColor(Color color);

	/**
	 * updates the position.
	 */
	void SetPosition(Vector2 newPos) override;
	/**
	 * 
	 */
	void CheckAndUpdate(Vector2 const&, AppContext_ty_c) override;
	/**
	 * 
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 *
	 */
	void Resize(Vector2 resolution, AppContext_ty_c) override;
};