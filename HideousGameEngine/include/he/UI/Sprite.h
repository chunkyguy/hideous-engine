//
//  Sprite.h
//  HideousGameEngine
//
//  Created by Sid on 20/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Sprite_h
#define HideousGameEngine_Sprite_h
#include <he/UI/ImageView.h>
#include <he/Utils/Frame.h>
#include <he/Utils/Asset.h>

namespace he {
		class Sprite : public ImageView{
		public:
			/**	Sprite from factory */
			Sprite(const Frame frame, const ImageViewFactory *factory, const std::string &image_name,
				   const int repeat_count = -1, const int final_frame = 0, const float fps = 24.0f);
			virtual ~Sprite();
			
		protected:
			virtual void update(float dt);
			virtual void render();

		};
}

#endif
