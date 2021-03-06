﻿#pragma once

#include <string>

#include <d3d11.h>

#include <D3D/Event.h>
#include <D3D/Keyboard.h>
#include <D3D/Mouse.h>

VRPG_BASE_BEGIN

struct WindowImplData;

struct WindowDesc
{
    int clientWidth  = 640;
    int clientHeight = 480;
    bool fullscreen  = false;
    std::wstring windowTitle = L"D3D11 Window";

    bool vsync = true;

    int sampleCount   = 1;
    int sampleQuality = 0;

    DXGI_FORMAT colorFormat        = DXGI_FORMAT_R8G8B8A8_UNORM;
    DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
};

struct WindowResizeEvent
{
    int newClientWidth;
    int newClientHeight;
};

struct WindowCloseEvent { };

struct WindowGetFocusEvent { };

struct WindowLostFocusEvent { };

using WindowEventManager  = EventManager<
    WindowResizeEvent, WindowCloseEvent, WindowGetFocusEvent, WindowLostFocusEvent>;

using WindowResizeHandler    = FunctionalEventHandler<WindowResizeEvent>;
using WindowCloseHandler     = FunctionalEventHandler<WindowCloseEvent>;
using WindowGetFocusHandler  = FunctionalEventHandler<WindowGetFocusEvent>;
using WindowLostFocusHandler = FunctionalEventHandler<WindowLostFocusEvent>;

class Window : public agz::misc::uncopyable_t
{
    WindowImplData *data_ = nullptr;
    WindowEventManager eventMgr_; 

public:

    Window() = default;

    ~Window();

    void Initialize(const WindowDesc &windowDesc);

    bool IsAvailable() const noexcept;

    void Destroy();

    void ImGuiNewFrame() const;

    void ImGuiRender() const;

    int GetClientSizeX() const noexcept;

    int GetClientSizeY() const noexcept;

    float GetClientAspectRatio() const noexcept;

    void SetVSync(bool vsync) noexcept;

    bool GetVSync() const noexcept;

    void UseDefaultViewport();

    void ClearDefaultRenderTarget(float r = 0, float g = 0, float b = 0, float a = 0);

    void ClearDefaultRenderTarget(const float backgroundColor[4]);

    void ClearDefaultDepthStencil();

    void SwapBuffers();

    void DoEvents(bool updateMouse = true, bool updateKeyboard = true);

    void WaitForFocus();

    template<typename Event>
    void Attach(EventHandler<Event> *handler) { eventMgr_.Attach(handler); }

    template<typename Event>
    void Detach(EventHandler<Event> *handler) { eventMgr_.Detach(handler); }

    void SetMouseUpdateInterval(int interval) noexcept;

    MouseEventManager *GetMouse() noexcept;

    KeyboardEventManager *GetKeyboard() noexcept;

    ID3D11Device *Device() const noexcept;

    ID3D11DeviceContext *DeviceContext() const noexcept;

    HWND GetNativeWindowHandle() const noexcept;

    HINSTANCE GetNativeProgramHandle() const noexcept;

    void SetCloseFlag(bool shouldClose) noexcept;

    bool GetCloseFlag() const noexcept;

    bool IsInFocus() const noexcept;

    void _resize();

    void _close();

    void _getFocus();

    void _lostFocus();

    void _mouse_button_down(MouseButton button);

    void _mouse_button_up(MouseButton button);

    void _wheel_scroll(int offset);

    void _key_down(KeyCode key);

    void _key_up(KeyCode key);

    void _char_input(uint32_t ch);

    void _raw_key_down(uint32_t vk);

    void _raw_key_up(uint32_t vk);
};

VRPG_BASE_END
