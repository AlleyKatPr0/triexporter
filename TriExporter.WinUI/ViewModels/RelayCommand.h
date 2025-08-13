#pragma once

#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <functional>

namespace winrt::TriExporter::WinUI::ViewModels::implementation
{
    struct RelayCommand : winrt::implements<RelayCommand, winrt::Microsoft::UI::Xaml::Input::ICommand>
    {
    public:
        // Constructor that takes execute and canExecute delegates
        RelayCommand(std::function<void()> execute, std::function<bool()> canExecute = nullptr);

        // ICommand implementation
        bool CanExecute(winrt::Windows::Foundation::IInspectable const& parameter);
        void Execute(winrt::Windows::Foundation::IInspectable const& parameter);
        
        // CanExecuteChanged event
        winrt::event_token CanExecuteChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler);
        void CanExecuteChanged(winrt::event_token const& token) noexcept;

        // Method to raise CanExecuteChanged event
        void RaiseCanExecuteChanged();

    private:
        std::function<void()> m_execute;
        std::function<bool()> m_canExecute;
        winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>> m_canExecuteChanged;
    };
}

namespace winrt::TriExporter::WinUI::ViewModels::factory_implementation
{
    struct RelayCommand : winrt::implements<RelayCommand, winrt::Microsoft::UI::Xaml::Input::ICommand>
    {
    };
}

// Inline implementation for header-only convenience
namespace winrt::TriExporter::WinUI::ViewModels::implementation
{
    inline RelayCommand::RelayCommand(std::function<void()> execute, std::function<bool()> canExecute)
        : m_execute(std::move(execute)), m_canExecute(std::move(canExecute))
    {
    }

    inline bool RelayCommand::CanExecute(winrt::Windows::Foundation::IInspectable const&)
    {
        return m_canExecute ? m_canExecute() : true;
    }

    inline void RelayCommand::Execute(winrt::Windows::Foundation::IInspectable const&)
    {
        if (m_execute && CanExecute(nullptr))
        {
            m_execute();
        }
    }

    inline winrt::event_token RelayCommand::CanExecuteChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler)
    {
        return m_canExecuteChanged.add(handler);
    }

    inline void RelayCommand::CanExecuteChanged(winrt::event_token const& token) noexcept
    {
        m_canExecuteChanged.remove(token);
    }

    inline void RelayCommand::RaiseCanExecuteChanged()
    {
        m_canExecuteChanged(*this, nullptr);
    }
}