#ifndef IMBASE_TEXTURE_HPP_INCLUDED_
#define IMBASE_TEXTURE_HPP_INCLUDED_ 1
#pragma once

namespace ImBase {
	enum TScaleFunc {
		Linear,
		Nearest
	};

	// Note: Pixels are expected to be aligned in R-G-B-A order in memory
	struct Texture {
		unsigned int id = 0; // when using with ImGui::Image, use reinterpret_cast<ImTextureID>()

		Texture(int width, int height, const unsigned char* pixels, TScaleFunc scaleFunc = TScaleFunc::Nearest);

		// Update a sub-region of the texture, where
		// the sub-region's coordinates are dX & dY
		// and dW & dH are width & height of the sub-region
		void Update(const unsigned char* pixels, unsigned int dX = 0, unsigned int dY = 0, unsigned int dW = 0, unsigned int dH = 0);

		~Texture();
		inline TScaleFunc GetScalingFunc() { return scaleFunc; }

	private:
		int width = 0, height = 0;
		TScaleFunc scaleFunc;
	};
}

#endif // IMBASE_TEXTURE_HPP_INCLUDED_

