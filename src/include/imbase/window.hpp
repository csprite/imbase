#ifndef IMBASE_WINDOW_HPP_INCLUDED_
#define IMBASE_WINDOW_HPP_INCLUDED_ 1
#pragma once

namespace ImBase {
	namespace Window {
		int  Init(int width, int height, const char* const title, bool resizable = true);
		void SetIcon(int width, int height, unsigned char* pixels);
		void SetTitle(const char* title);
		void SetBG(unsigned char r, unsigned char g, unsigned char b);
		void SetMaxFPS(int fps);
		bool ShouldClose();
		void NewFrame();
		void EndFrame();
		void Destroy();

		void Minimize();
		void Restore(); // Opposite of minimize
		void Maximize();
	}
}

#endif // IMBASE_WINDOW_HPP_INCLUDED_

