//
//  Shader.fsh
//  HideousGameEngine
//
//  Created by Sid on 02/05/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
