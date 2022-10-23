//
// Purpur Tentakel
// 23.10.2022
//

#pragma once
class Focusable;

void AddFocusLayer(bool isPopUp = false);
void DeleteFocusLayer(bool isPopUp = false);

void AddFocusElement(Focusable* focusable, bool isPopUp = false);
void DeleteFocusElement(Focusable* focusable, bool isPopUp = false);

void SelectFocusElement(Focusable* focusable, bool isPopUp = false);
