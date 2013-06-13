//
//  Button.h
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Button_h
#define HideousGameEngine_Button_h
#include <he/UI/View.h>

//#include <he/Animation/Animation.h>
#include <he/EventLoop/Gesture.h>
#include <he/Utils/Frame.h>

namespace he {
	namespace ui{
		
		/** Interface of the protocol */
		class Button;
		struct IButtonListner{
			virtual ~IButtonListner(){}
			virtual void Hit(Button *sender) = 0;
		};
		
		/**	Anon delegate */
		template<typename T>
		class ButtonListner : public IButtonListner{
		public:
			typedef void(T::*callback)(Button *sender);
			ButtonListner(T *object, callback callback) :
			object_(object),
			method_(callback)
			{}
			
			void Hit(Button *sender){
				(object_->*method_)(sender);
			}
		private:
			T *object_;
			callback method_;
		};
		
		
		class Button : public View{
		public:
			Button(IButtonListner *listner, const Frame frame = Frame(), int tag = -1);
			~Button();
			
			/** Animatiion finish callback.
			 Called in case an animation is registered.
			 @warning Don't call explicitly, expected to be called from AnimationLoop.
			 */
			//		void AnimationFinish(int animation_id);
			
			/** The Gesture event callback.
			 @warning Don't call explicitly, expected to be called only from the EventLoop.
			 */
			void HandleGesture(const Gesture &g);
			
			int GetTag() const;
			
		private:
			/** Implementation of the virtual UIComponent::update
			 */
			void self_update(float dt);
			
			/** Implementation of the virtual UIComponent::render
			 */
			void self_render();
			
			void self_set_needs_display();
			
			int tag_;	/**< tag to identify the object */
			//unsigned long animation_handle_; /**< animation handle to kill the animation if required */
			GestureListener<Button> *gesture_listener_; /**< Registered gesture listener */
			IButtonListner *listner_;	/**< Registered button listener */
			//		AnimationListener<Button> *animation_listener_; /**< Registered animation listener */
		};
	} /*namespace ui*/
} /*namespace he*/

//namespace he {
//
//	class Font;
//	class RenderObject;
//	class Text;
//	class TextureShader;
//	class TextureAtlas;
//	class TextureVertex;
//
//
//	namespace ui{
//
//		/** Interface of the protocol */
//		class Button;
//		struct IButtonListner{
//			virtual ~IButtonListner(){}
//			virtual void Hit(Button *sender) = 0;
//		};
//
//		/**	Anon delegate */
//		template<typename T>
//		class ButtonListner : public IButtonListner{
//		public:
//			typedef void(T::*callback)(Button *sender);
//			ButtonListner(T *object, callback callback) :
//			object_(object),
//			method_(callback)
//			{}
//
//			void Hit(Button *sender){
//				(object_->*method_)(sender);
//			}
//		private:
//			T *object_;
//			callback method_;
//		};
//
//
//		/** Create buttons.
//		 Holds all assets necessary to create a button.
//		 */
//		struct ButtonFactory{
//			ButtonFactory(TextureShader *shdr, TextureAtlas *atls = nullptr, Font *fnt = nullptr);
//
//			Asset<Font> font;
//			Asset<TextureAtlas> atlas;
//			Asset<TextureShader> shader;
//		};
//
//		/** Button
//		 Can register and event and a callback.
//		 Can be created with a plain text/font or a image
//		 */
//		class Button : public View{
//		public:
//			Button(const ButtonFactory *factory,		/**< The factory that provides assets */
//				   IButtonListner *listner,			/**< The listener for any event callbacks */
//				   int tag = -1,						/**< The tag value can be used to differentiate between buttons*/
//				   const std::string &image_name = "",		/**< The name of the image. Optional */
//				   const std::string &string = "",				/**< The text to be displayed. Optional */
//				   const Transform transform = Transform(),	/**< The transform value of the UI */
//				   const GLKVector4 color = GLKVector4Make(0,0,0,0));	/** The color tint, if any. Optional */
//
//			~Button();
//
//			/** Animatiion finish callback.
//			 Called in case an animation is registered.
//			 @warning Don't call explicitly, expected to be called from AnimationLoop.
//			 */
//			void AnimationFinish(int animation_id);
//
//			/** The Gesture event callback.
//			 @warning Don't call explicitly, expected to be called only from the EventLoop.
//			 */
//			void HandleGesture(const Gesture &g);
//
//		private:
//			/** Implementation of the virtual UIComponent::update
//			 */
//			void update(float dt);
//
//			/** Implementation of the virtual UIComponent::render
//			 */
//			void render();
//
//			int tag_;	/**< tag to identify the object */
//			unsigned long animation_handle_; /**< animation handle to kill the animation if required */
//			RenderObject *background_; /**< background texture to be rendered, if any */
//			TextureVertex *background_data_; /**< background texture data */
//			GestureListener<Button> *gesture_listener_; /**< Registered gesture listener */
//			IButtonListner *listner_;	/**< Registered button listener */
//			AnimationListener<Button> *animation_listener_; /**< Registered animation listener */
//			Text *text_;	/**< Text to be rendered, if any */
//			Transform transform_; /**< Transform property of the object */
//			Transform original_transform_;	/**< Used in case of animation to cache the original transform value */
//		};
//
//
//	} /*namespace ui*/
//} /*namespace he*/


#endif
