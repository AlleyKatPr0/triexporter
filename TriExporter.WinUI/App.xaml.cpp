#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

namespace winrt::TriExporter::WinUI::implementation
{
    App::App()
    {
        InitializeComponent();

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
        {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();
                __debugbreak();
            }
        });
#endif
    }

    void App::OnLaunched(LaunchActivatedEventArgs const&)
    {
        m_window = make<implementation::MainWindow>();
        m_window.Activate();
    }
}

// Entry point for the application
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);
    Application::Start([](auto&&) { make<winrt::TriExporter::WinUI::implementation::App>(); });
    return 0;
}