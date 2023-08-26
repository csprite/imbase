#ifndef IMBASE_BASE_HPP_INCLUDED_
#define IMBASE_BASE_HPP_INCLUDED_ 1
#pragma once

namespace ImBase {
	int  Window_Init(int width, int height, const char* const title);
	void Window_SetIcon(int width, int height, unsigned char* pixels);
	void Window_SetTitle(const char* const title);
	void Window_SetBG(unsigned char r, unsigned char g, unsigned char b);
	bool Window_ShouldClose();
	void NewFrame();
	void EndFrame();
	void Window_Destroy();
}

#endif // IMBASE_BASE_HPP_INCLUDED_

