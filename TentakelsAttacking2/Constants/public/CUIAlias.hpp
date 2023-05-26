//
// Purpur Tentakel
// 26.05.2023
//

#include <memory>

struct AppContext;
using AppContext_ty = AppContext&;
using AppContext_ty_c = AppContext const&;

// Elements
class ClassicButton;
using ClassicButton_ty = std::shared_ptr<ClassicButton>;
using ClassicButton_ty_c = std::shared_ptr<ClassicButton> const&;

class SliderButton;
using SliderButton_ty = std::shared_ptr<SliderButton>;
using SliderButton_ty_c = std::shared_ptr<SliderButton> const&;

class ColorPicker;
using ColorPicker_ty = std::shared_ptr<ColorPicker>;
using ColorPicker_ty_c = std::shared_ptr<ColorPicker> const&;