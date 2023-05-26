//
// Purpur Tentakel
// 26.05.2023
//

#include <memory>
#include <string>

struct AppContext;
using AppContext_ty = AppContext&;
using AppContext_ty_c = AppContext const&;

// Elements
	// Button
class ClassicButton;
using ClassicButton_ty = std::shared_ptr<ClassicButton>;
using ClassicButton_ty_c = std::shared_ptr<ClassicButton> const&;

class SliderButton;
using SliderButton_ty = std::shared_ptr<SliderButton>;
using SliderButton_ty_c = std::shared_ptr<SliderButton> const&;

	// Color Picker
class ColorPicker;
using ColorPicker_ty = std::shared_ptr<ColorPicker>;
using ColorPicker_ty_c = std::shared_ptr<ColorPicker> const&;

class ColorPickerCell;
using ColorPickerCell_ty = std::shared_ptr<ColorPickerCell>;
using ColorPickerCell_ty_c = std::shared_ptr<ColorPickerCell> const&;
	// Default
class Arrow;
using Arrow_ty = std::shared_ptr<Arrow>;
using Arrow_ty_c = std::shared_ptr<Arrow> const&;

class CheckBox;
using CheckBox_ty = std::shared_ptr<CheckBox>;
using CheckBox_ty_c = std::shared_ptr<CheckBox> const&;

class Hover;
using Hover_ty = std::shared_ptr<Hover>;
using Hover_ty_c = std::shared_ptr<Hover> const&;

template <typename T>
class InputLine;
using InputLine_int_ty = std::shared_ptr<InputLine<int>>;
using InputLine_int_ty_c = std::shared_ptr<InputLine<int>> const&;
using InputLine_float_ty = std::shared_ptr<InputLine<float>>;
using InputLine_float_ty_c = std::shared_ptr<InputLine<float>> const&;
using InputLine_double_ty = std::shared_ptr<InputLine<double>>;
using InputLine_double_ty_c = std::shared_ptr<InputLine<double>> const&;
using InputLine_str_ty = std::shared_ptr<InputLine<std::string>>;
using InputLine_str_ty_c = std::shared_ptr<InputLine<std::string>> const&;

class Line;
using Line_ty = std::shared_ptr<Line>;
using Line_ty_c = std::shared_ptr<Line> const&;
