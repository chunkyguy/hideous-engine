//
//  View.h
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_View_h
#define HideousGameEngine_View_h
#include <he/Utils/Frame.h>

namespace he {
	namespace ui{
		
		/** Container of all kind of Views.
		 Adds child component in stack order.
		 If AddSubview-order is like [btn_01, btn_01, bg, icon_01]
		 Draw order will be [btn_01, btn_01, bg, icon_01]
		 */
		class View{
		public:
			View(const Frame &frame);
			virtual ~View();
			
			/** Update self. Update all children in draw order */
			void Update(float dt);
						
			/** Render self. Render all children in draw order */
			void Render();
			
			/** Owns the passed component */
			void AddSubview(View *view);
			
			/** Update frame */
			void SetFrame(const Frame &frame);
			/** Get the current frame */
			const Frame &GetFrame() const;
			
			/** Returns pointer to frame
			@warning This is more like a design bug, can get modified in future. Use minimum.
			 */
			Frame *GetFramePtr();
		
		protected:
			/** Actual update 
			 @note Needs to call superclass Update() after doing all the self updating.
			 */
			virtual void update(float dt);

			/** Actual render 
			 @note Needs to call superclass Render(), after doing all the self rendinring.
			 */
			virtual void render();

		private:
		
			Frame frame_; /**< The frame of the view */
			View *add_to_;	/**< Next Submit adds to this node. */
			View *head_;	/**< The head pointer to the first child UIComponent. Starts drawing from here */
			View *next_;	/**< Points to the next sibling UIComponent */
	};
	
} /*namespace ui*/
} /*namespace he*/

#endif
