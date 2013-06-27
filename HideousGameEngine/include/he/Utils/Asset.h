//
//  Asset.h
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Asset_h
#define HideousGameEngine_Asset_h
#include <he/Utils/DebugHelper.h>	// For assert()

namespace he {

	/** RAII for any asset that lives in memory
		Best use is for creating factories those instanciate objects.
	 */
	template <typename T>
	class Asset{
	public:
		/** Default construct Asset with blank values
		 @note	Set self_destruct false, if the asset is not owned by the class constructing the asset
				Another case could be when the asset is to be used shared among many contexts.
		 */
		Asset() :
		asset_(nullptr),
		self_destruct_(false)
		{	}
		
		/** Destroys the contained asset, if self_destruct was enabled. */
		~Asset(){
			if(self_destruct_){
				delete asset_;
			}
		}

		/** Check if the asset is empty */
		bool IsEmpty() const{
			return (asset_ == nullptr);
		}
		
		/** Get a reference to the asset */
		T* Get() const{
			return asset_;
		}

		/** Set asset
		 @param asset The asset.
		 @param clean Clean the loaded asset, if any.
		 */
		void Set(T* asset, bool clean = false){
			if(clean && asset_){
				delete asset_;
			}
			asset_ = asset;
			self_destruct_ = false;
		}

		
		/** Move asset
		 @param asset The asset.
		 @param clean Clean the loaded asset, if any.
		 */
		void Move(T* asset, bool clean = false){
			if(clean && asset_){
				delete asset;
			}
			asset_ = asset;
			self_destruct_ = true;
		}
		
	private:
		T *asset_;				/**< the asset pointer */
		bool self_destruct_;		/**< can destroy after use. */
	};
	
	
} /*namespace he*/

#endif
