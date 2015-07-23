//
//  CSReporter.cpp
//  CSTest
//  Created by Ian Copland on 15/07/2015.
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

#include <IntegrationTest/TestSystem/CSReporter.h>

#include <internal/catch_reporter_registrars.hpp>

namespace CSTest
{
    namespace IntegrationTest
    {
        INTERNAL_CATCH_REGISTER_REPORTER("cs", CSReporter);
     
        Report CSReporter::s_report;
        
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        std::string CSReporter::getDescription()
        {
            return "Generates a report accessible in code.";
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        const Report& CSReporter::getReport()
        {
            return s_report;
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        CSReporter::CSReporter(const Catch::ReporterConfig& in_config)
            : StreamingReporterBase(in_config)
        {
            CS_ASSERT(m_config->includeSuccessfulResults() == false, "CSReporter doesn't support reporting successful results.");
            CS_ASSERT(m_config->warnAboutMissingAssertions() == false, "CSReporter doesn't support warning about missing assertions.");
            CS_ASSERT(m_config->showInvisibles() == false, "CSReporter doesn't support showing invisibles.");
            CS_ASSERT(m_config->showDurations() == false, "CSReporter doesn't support showing durations.");
            CS_ASSERT(m_config->forceColour() == false, "CSReporter doesn't support coloured output.");
            CS_ASSERT(m_config->shouldDebugBreak() == false, "CSReporter doesn't support debug break.");
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        Catch::ReporterPreferences CSReporter::getPreferences() const
        {
            Catch::ReporterPreferences prefs;
            prefs.shouldRedirectStdOut = true;
            return prefs;
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        bool CSReporter::assertionEnded(const Catch::AssertionStats& in_assertionStats)
        {
            const Catch::AssertionResult& assertionResult = in_assertionStats.assertionResult;
            
            if (isOk(assertionResult.getResultType()) == false)
            {
                m_currentFailedAssertions.push_back(FailedAssertion(assertionResult.getSourceInfo().file, static_cast<u32>(assertionResult.getSourceInfo().line), assertionResult.getExpression()));
            }
            
            return true;
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void CSReporter::testCaseEnded(const Catch::TestCaseStats& in_testCaseStats)
        {
            StreamingReporterBase::testCaseEnded(in_testCaseStats);
            
            if (m_currentFailedAssertions.empty() == false)
            {
                m_currentFailedTestCases.push_back(TestCase(in_testCaseStats.testInfo.name, static_cast<u32>(in_testCaseStats.totals.assertions.total()), m_currentFailedAssertions));
                m_currentFailedAssertions.clear();
            }
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void CSReporter::testRunEnded(const Catch::TestRunStats& in_testRunStats)
        {
            StreamingReporterBase::testRunEnded(in_testRunStats);
            
            if (in_testRunStats.aborting == true)
            {
                CS_LOG_FATAL("Failed to run tests, aborting.");
            }
            
            s_report = Report(static_cast<u32>(in_testRunStats.totals.testCases.total()), static_cast<u32>(in_testRunStats.totals.assertions.total()), m_currentFailedTestCases);
            m_currentFailedTestCases.clear();
        }
    }
}
