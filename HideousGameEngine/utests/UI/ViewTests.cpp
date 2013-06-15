//
//  View.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/View.h>

#include <gtest.h>

//TEST(View, Destructor){
//	std::string atlas_data_path(he::ResourcePath() + "homescreen_ss.xml");
//	std::string atlas_img_path(he::ResourcePath() + "homescreen_ss.png");
//	atlas_.Load(new he::TextureAtlas(atlas_data_path, atlas_img_path, he::TextureAtlas::kStarling), true);
//	he::ui::ImageViewFactory img_factory(g_Assets->textureShader.Get(), atlas_.Get());
//	
//	// load view
//	he::Frame view_frame;
//	view_ = std::unique_ptr<he::ui::View>( new he::ui::View(view_frame) );
//	
//	// bg
//	std::string bg_img_name("town.png instance 1");
//	he::Frame bg_img_frame(he::Transform(GLKVector2Make(-2, 2)), atlas_.Get()->GetTextureAtlasRegion(bg_img_name)->sprite_size_);
//	view_->AddSubview( new he::ui::ImageView(&img_factory, bg_img_name, bg_img_frame));
//
//}
