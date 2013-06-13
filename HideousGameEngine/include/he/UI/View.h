//
//  View.h
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_View_h
#define HideousGameEngine_View_h
#include <he/Utils/Transform.h>

namespace he {
	namespace ui{
		
		/** Container of all kind of Views.
		 Adds child component in stack order.
		 If AddSubview-order is like [btn_01, btn_01, bg, icon_01]
		 Draw order will be [btn_01, btn_01, bg, icon_01]
		 */
		class View{
		public:
			View(const Transform &transform);
			virtual ~View();
			
			/** Update self. Update all children in draw order */
			void Update(float dt);
			/** Render self. Render all children in draw order */
			void Render();
			
			/** Owns the passed component */
			void AddSubview(View *view);
			
			/** Update transform */
			void SetTransform(const Transform &transform);
			
			/** Get transform */
			const Transform &GetTransform() const;
			
			/** Refresh the UI */
			void SetNeedsDisplay();
			
		private:
			/** Actual update */
			virtual void update(float dt);

			/** Actual render */
			virtual void render();

			/** Actual refresh.
				Update the render_object
			 */
			virtual void refresh();
			
			View *add_to_;	/**< Next Submit adds to this node. */
			View *head_;	/**< The head pointer to the first child UIComponent. Starts drawing from here */
			View *next_;	/**< Points to the next sibling UIComponent */
			Transform transform_; /**< The transform of the view */
	};
	
} /*namespace ui*/
} /*namespace he*/

#endif
