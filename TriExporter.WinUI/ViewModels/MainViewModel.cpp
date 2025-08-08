#include "pch.h"
#include "MainViewModel.h"

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml::Data;

namespace winrt::TriExporter::WinUI::ViewModels::implementation
{
    MainViewModel::MainViewModel()
    {
        // Initialize commands
        m_openFileCommand = winrt::make<RelayCommand>([this]() { OpenFile(); }, [this]() { return true; });
        m_exportFileCommand = winrt::make<RelayCommand>([this]() { ExportFile(); }, [this]() { return CanExport(); });
    }

    void MainViewModel::SelectedFilePath(winrt::hstring const& value)
    {
        if (m_selectedFilePath != value)
        {
            m_selectedFilePath = value;
            RaisePropertyChanged(L"SelectedFilePath");
            
            // Update file loaded state
            IsFileLoaded(!value.empty());
        }
    }

    void MainViewModel::FileInfo(winrt::hstring const& value)
    {
        if (m_fileInfo != value)
        {
            m_fileInfo = value;
            RaisePropertyChanged(L"FileInfo");
        }
    }

    void MainViewModel::StatusMessage(winrt::hstring const& value)
    {
        if (m_statusMessage != value)
        {
            m_statusMessage = value;
            RaisePropertyChanged(L"StatusMessage");
        }
    }

    void MainViewModel::IsFileLoaded(bool value)
    {
        if (m_isFileLoaded != value)
        {
            m_isFileLoaded = value;
            RaisePropertyChanged(L"IsFileLoaded");
            
            // Update export capability based on file loaded state
            CanExport(value);
        }
    }

    void MainViewModel::CanExport(bool value)
    {
        if (m_canExport != value)
        {
            m_canExport = value;
            RaisePropertyChanged(L"CanExport");
        }
    }

    winrt::event_token MainViewModel::PropertyChanged(PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void MainViewModel::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }

    void MainViewModel::OpenFile()
    {
        // Update status
        StatusMessage(L"Opening file picker...");
        
        // In a real implementation, this would:
        // 1. Open a file picker
        // 2. Load and parse the selected 3D file
        // 3. Update the UI with file information
        // For now, just simulate the process
        
        // Simulate file selection (this would be replaced with actual file picker logic)
        SelectedFilePath(L"C:\\Sample\\example.3ds");
        FileInfo(L"Sample 3DS file loaded\nVertices: 1024\nFaces: 2048\nMaterials: 4");
        StatusMessage(L"File loaded successfully");
    }

    void MainViewModel::ExportFile()
    {
        if (!IsFileLoaded())
        {
            StatusMessage(L"No file loaded for export");
            return;
        }

        StatusMessage(L"Export functionality not yet implemented");
        
        // In a real implementation, this would:
        // 1. Open a save file dialog
        // 2. Convert the loaded 3D data to the target format
        // 3. Save the file
        // 4. Update status with success/failure
    }

    void MainViewModel::RaisePropertyChanged(winrt::hstring const& propertyName)
    {
        m_propertyChanged(*this, PropertyChangedEventArgs(propertyName));
    }
}