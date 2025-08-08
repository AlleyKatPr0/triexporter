#pragma once

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include "ViewModels/MainViewModel.h"

namespace winrt::TriExporter::WinUI::implementation
{
    struct MainWindow : winrt::Microsoft::UI::Xaml::WindowT<MainWindow>
    {
        MainWindow();

        // Event handlers
        void OpenFileButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ExportFileButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        // Property for ViewModel
        TriExporter::WinUI::ViewModels::MainViewModel ViewModel() { return m_viewModel; }

    private:
        TriExporter::WinUI::ViewModels::MainViewModel m_viewModel{ nullptr };
        void UpdateUI();
    };
}

namespace winrt::TriExporter::WinUI::factory_implementation
{
    struct MainWindow : winrt::Microsoft::UI::Xaml::WindowT<MainWindow, implementation::MainWindow>
    {
    };
}