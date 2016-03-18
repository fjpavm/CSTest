//
//  OptionsMenuPresenter.cpp
//  CSTest
//  Created by Ian Copland on 28/07/2015.
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

#include <Common/UI/OptionsMenuPresenter.h>

#include <Common/UI/OptionsMenuDesc.h>
#include <Common/UI/BasicWidgetFactory.h>

#include <ChilliSource/Core/Base.h>
#include <ChilliSource/Core/Resource.h>
#include <ChilliSource/Core/State.h>
#include <ChilliSource/Rendering/Font.h>
#include <ChilliSource/UI/Base.h>
#include <ChilliSource/UI/Layout.h>
#include <ChilliSource/UI/Text.h>

namespace CSTest
{
    namespace Common
    {
        namespace
        {
            constexpr f32 k_relativeSpacing = 0.065f;
            constexpr f32 k_listMargins = 0.2f;
            constexpr u32 k_numItemsPerColumn = 5;
            constexpr u32 k_numColumns = 2;
            constexpr u32 k_maxItems = k_numItemsPerColumn * k_numColumns;
        }
        
        CS_DEFINE_NAMEDTYPE(OptionsMenuPresenter);
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        OptionsMenuPresenterUPtr OptionsMenuPresenter::Create() noexcept
        {
            return OptionsMenuPresenterUPtr(new OptionsMenuPresenter());
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        bool OptionsMenuPresenter::IsA(CSCore::InterfaceIDType in_interfaceId) const noexcept
        {
            return (OptionsMenuPresenter::InterfaceID == in_interfaceId);
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void OptionsMenuPresenter::Present(const OptionsMenuDesc& in_desc) noexcept
        {
            CS_ASSERT(in_desc.GetButtons().size() <= k_maxItems, "Too many options. The system will need upgraded to support pages.");
            
            Dismiss();

			if (in_desc.GetButtons().size() < k_numItemsPerColumn)
			{
				auto layoutComponent = m_buttonContainer->GetComponent<CSUI::LayoutComponent>();
				layoutComponent->ApplyLayoutDef(CSUI::LayoutDefSPtr(new CSUI::VListLayoutDef(k_numItemsPerColumn, CSCore::Vector4(0.0f, k_listMargins, 0.0f, k_listMargins), CSCore::Vector4::k_zero, k_relativeSpacing, 0.0f)));
			}
			else
			{
				auto layoutComponent = m_buttonContainer->GetComponent<CSUI::LayoutComponent>();
				layoutComponent->ApplyLayoutDef(CSUI::LayoutDefSPtr(new CSUI::GridLayoutDef(CSUI::GridLayout::CellOrder::k_rowMajor, k_numItemsPerColumn, k_numColumns, CSCore::Vector4::k_zero, CSCore::Vector4::k_zero, k_relativeSpacing, 0.0f, k_relativeSpacing, 0.0f)));
			}

            auto basicWidgetFactory = CSCore::Application::Get()->GetSystem<Common::BasicWidgetFactory>();
            for (const auto& buttonDesc : in_desc.GetButtons())
            {
                CSUI::WidgetSPtr button = basicWidgetFactory->CreateStretchableButton(CSCore::Vector2::k_one, buttonDesc.m_name, CSRendering::AlignmentAnchor::k_middleCentre, CSCore::Colour(0.92f, 0.95f, 0.98f, 1.0f));
                m_buttonContainer->AddWidget(button);
                
                auto connection = button->GetReleasedInsideEvent().OpenConnection([=](CSUI::Widget* in_widget, const CSInput::Pointer& in_pointer, CSInput::Pointer::InputType in_inputType)
                {
                    buttonDesc.m_action();
                });
                
                m_buttons.push_back(button);
                m_connectionContainer.push_back(std::move(connection));
            }
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void OptionsMenuPresenter::Dismiss() noexcept
        {
            m_connectionContainer.clear();
            
            for (const auto& button : m_buttons)
            {
                button->RemoveFromParent();
            }
            
            auto layoutComponent = m_buttonContainer->GetComponent<CSUI::LayoutComponent>();
            layoutComponent->ApplyLayoutDef(CSUI::LayoutDefSPtr(new CSUI::VListLayoutDef(k_numItemsPerColumn, CSCore::Vector4::k_zero, CSCore::Vector4::k_zero, k_relativeSpacing, 0.0f)));
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void OptionsMenuPresenter::OnInit() noexcept
        {
            auto resourcePool = CSCore::Application::Get()->GetResourcePool();
            auto mediumFont = resourcePool->LoadResource<CSRendering::Font>(CSCore::StorageLocation::k_package, "Fonts/ArialMed.csfont");
            
            auto widgetFactory = CSCore::Application::Get()->GetWidgetFactory();
            m_buttonContainer = widgetFactory->CreateLayout();
            m_buttonContainer->SetParentalAnchor(CSRendering::AlignmentAnchor::k_topCentre);
            m_buttonContainer->SetOriginAnchor(CSRendering::AlignmentAnchor::k_topCentre);
            m_buttonContainer->SetRelativePosition(CSCore::Vector2(0.0f, -0.15f));
            m_buttonContainer->SetRelativeSize(CSCore::Vector2(0.75f, 0.65f));
            
            Dismiss();
            
            GetState()->GetUICanvas()->AddWidget(m_buttonContainer);
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void OptionsMenuPresenter::OnDestroy() noexcept
        {
            Dismiss();

            m_buttonContainer->RemoveFromParent();
            m_buttonContainer.reset();
        }
    }
}