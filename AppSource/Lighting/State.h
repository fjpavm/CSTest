//
//  State.h
//  CSTest
//  Created by Ian Copland on 04/08/2015.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2015 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef _LIGHTING_STATE_H_
#define _LIGHTING_STATE_H_

#include <CSTest.h>

#include <ChilliSource/Core/State.h>

namespace CSTest
{
    namespace Lighting
    {
        //------------------------------------------------------------------------------
        /// A state for testing lighting and shadows.
        ///
        /// @author Ian Copland
        //------------------------------------------------------------------------------
        class State final : public CS::State
        {
            //------------------------------------------------------------------------------
            /// Creates a series of lights.
            ///
            /// @author Ian Copland
            ///
            /// @param in_room - The room the lights are in.
            //------------------------------------------------------------------------------
            void CreateLights(const CS::EntitySPtr& in_room);
            //------------------------------------------------------------------------------
            /// Creates a grid of randomly sized and coloured boxes and added them to the
            /// scene.
            ///
            /// @author Ian Copland
            //------------------------------------------------------------------------------
            void CreateBoxes();
            //------------------------------------------------------------------------------
            /// The life-cycle event for creating all state systems.
            ///
            /// @author Ian Copland
            //------------------------------------------------------------------------------
            void CreateSystems() override;
            //------------------------------------------------------------------------------
            /// Initialises the state.
            ///
            /// @author Ian Copland
            //------------------------------------------------------------------------------
            void OnInit() override;
        };
    }
}

#endif
