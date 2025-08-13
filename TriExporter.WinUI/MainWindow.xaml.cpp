#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;

namespace winrt::TriExporter::WinUI::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        
        // Initialize ViewModel
        m_viewModel = winrt::make<TriExporter::WinUI::ViewModels::implementation::MainViewModel>();
        
        // Set window properties
        Title(L"TriExporter WinUI 3");
    }

    void MainWindow::OpenFileButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        // Create file picker
        auto picker = FileOpenPicker();
        
        // Set supported file types for 3D files
        picker.FileTypeFilter().Append(L".3ds");
        picker.FileTypeFilter().Append(L".obj");
        picker.FileTypeFilter().Append(L".fbx");
        picker.FileTypeFilter().Append(L".dae");
        picker.FileTypeFilter().Append(L".gltf");
        picker.FileTypeFilter().Append(L".glb");
        
        picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

        // Note: In a real implementation, this would need proper async handling
        // For now, just update the UI to show file selection is in progress
        if (auto fileInfoText = this->FindName(L"FileInfoText").try_as<TextBlock>())
        {
            fileInfoText.Text(L"File picker opened...");
        }
        
        if (auto statusText = this->FindName(L"StatusText").try_as<TextBlock>())
        {
            statusText.Text(L"Selecting file...");
        }
        
        UpdateUI();
    }

    void MainWindow::ExportFileButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        if (auto statusText = this->FindName(L"StatusText").try_as<TextBlock>())
        {
            statusText.Text(L"Export functionality not yet implemented");
        }
    }

    void MainWindow::UpdateUI()
    {
        // Update export button state based on whether a file is loaded
        if (auto exportButton = this->FindName(L"ExportFileButton").try_as<Button>())
        {
            // For now, keep it disabled until file loading is implemented
            exportButton.IsEnabled(false);
        }
    }
}