//  The MIT License (MIT)
//
//  Copyright (c) 2016 Tag Games Limited
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

#ifndef _GYROSCOPE_GYROSCOPEPRESENTER_H_
#define _GYROSCOPE_GYROSCOPEPRESENTER_H_

#include <CSTest.h>

#include <ChilliSource/Core/System.h>

namespace CSTest
{
    namespace Gyroscope
    {
        /// A system which displays gyro information on-screen.
        ///
        class GyroscopePresenter final : public CS::StateSystem
        {
        public:
            CS_DECLARE_NAMEDTYPE(GyroscopePresenter);

            /// Allows querying of whether or not the component implements the
            /// interface associated with the given interface Id.
            ///
            /// @param interfaceId 
            ///     The interface Id.
            ///
            /// @return Whether the object implements the given interface.
            ///
            bool IsA(CS::InterfaceIDType interfaceId) const noexcept override;
            
        private:
            friend class CS::State;

            /// Creates a new instance of the system.
            ///
            /// @return The new instance.
            ///
            static GyroscopePresenterUPtr Create() noexcept;
  
            /// Constructor
            ///
            GyroscopePresenter() = default;
            
            /// Initialises all of the UI on which the gyro information will be presented.
            ///
            void InitUI() noexcept;
            
            /// Called when the presenter is first created. This will set up the
            /// information which should be presented.
            ///
            void OnInit() noexcept override;

            /// Called during init; adds event receiver for gyro updates.
            ///
            void AddGyroscopeHandler() noexcept;
            
            /// Creates ambient and directional light and adds to the scene
            ///
            void CreateLights();

            /// Displays gyro value on screen.
            ///
            /// @param orientation
            ///     The orientation quaternion to display.
            ///
            void DisplayOrientation(const CS::Quaternion& orientation) noexcept;
            
            /// Called when the presenter is about to be destroyed. This will clean
            /// up the events and elements which were being presented.
            ///
            void OnDestroy() noexcept override;
            
            CS::EventConnectionUPtr m_eventConnection;
            CS::Gyroscope* m_gyro = nullptr;
            
            CS::WidgetSPtr m_rootUI;
            CS::TextUIComponent* m_textComponent = nullptr;
            
            CS::EntitySPtr m_box;
        };
    }
}

#endif
