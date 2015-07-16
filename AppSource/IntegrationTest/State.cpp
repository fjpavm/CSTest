//
//  State.cpp
//  CSTest
//  Created by Ian Copland on 13/07/2015.
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

#include <IntegrationTest/State.h>

#include <IntegrationTest/TestSystem/TestSystem.h>

#include <catch.hpp>

namespace CSTest
{
    namespace IntegrationTest
    {
        TEST_CASE("Example", "[Example]")
        {
            REQUIRE(false == true);
        }
        
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void State::CreateSystems()
        {
            m_testSystem = CreateSystem<TestSystem>();
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void State::OnInit()
        {
            auto report = m_testSystem->PerformTests();
            
            if (report.WasRunSuccessful() == false)
            {
                CS_LOG_VERBOSE("Failed to run tests.");
                return;
            }
            
            if (report.DidAllTestsPass() == false)
            {
                CS_LOG_VERBOSE(CSCore::ToString(report.GetNumFailedAssertions()) + " out of " + CSCore::ToString(report.GetNumAssertions()) + " tests failed.");
                return;
            }
            
            CS_LOG_VERBOSE("All tests passed!");
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void State::OnUpdate(f32 in_deltaTime)
        {
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void State::OnDestroy()
        {
        }
    }
}
