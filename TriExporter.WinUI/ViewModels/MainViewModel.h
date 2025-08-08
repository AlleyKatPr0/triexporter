#pragma once

#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include "RelayCommand.h"

namespace winrt::TriExporter::WinUI::ViewModels::implementation
{
    struct MainViewModel : winrt::implements<MainViewModel, winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged>
    {
        MainViewModel();

        // Properties
        winrt::hstring SelectedFilePath() const { return m_selectedFilePath; }
        void SelectedFilePath(winrt::hstring const& value);

        winrt::hstring FileInfo() const { return m_fileInfo; }
        void FileInfo(winrt::hstring const& value);

        winrt::hstring StatusMessage() const { return m_statusMessage; }
        void StatusMessage(winrt::hstring const& value);

        bool IsFileLoaded() const { return m_isFileLoaded; }
        void IsFileLoaded(bool value);

        bool CanExport() const { return m_canExport; }
        void CanExport(bool value);

        // Commands
        TriExporter::WinUI::ViewModels::RelayCommand OpenFileCommand() const { return m_openFileCommand; }
        TriExporter::WinUI::ViewModels::RelayCommand ExportFileCommand() const { return m_exportFileCommand; }

        // INotifyPropertyChanged
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

    private:
        // Private methods
        void OpenFile();
        void ExportFile();
        void RaisePropertyChanged(winrt::hstring const& propertyName);

        // Fields
        winrt::hstring m_selectedFilePath{ L"" };
        winrt::hstring m_fileInfo{ L"No file selected" };
        winrt::hstring m_statusMessage{ L"Ready" };
        bool m_isFileLoaded{ false };
        bool m_canExport{ false };

        // Commands
        TriExporter::WinUI::ViewModels::RelayCommand m_openFileCommand{ nullptr };
        TriExporter::WinUI::ViewModels::RelayCommand m_exportFileCommand{ nullptr };

        // Event
        winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::TriExporter::WinUI::ViewModels::factory_implementation
{
    struct MainViewModel : winrt::implements<MainViewModel, winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChangedT<MainViewModel>>
    {
    };
}