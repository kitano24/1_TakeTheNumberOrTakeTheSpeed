//---------------------------------------------------------------------------
//!	@file	WinMain.cpp
//!	@brief	�E�B���h�E�Y�N���V�X�e��
//---------------------------------------------------------------------------

GameMain gamemain;
//-----------------------------------------------------------------------
//! @name�@imgui
//-----------------------------------------------------------------------
//@{
static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp))
		return true;

	switch (msg)
	{
	case WM_CLOSE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}
//@}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_W, WINDOW_H, 32);
	SetBackgroundColor(144,144,144);
	SetMainWindowText("�����Ƃ邩�A�������Ƃ邩");
	//! Z�o�b�t�@�̐[�x��24bit�ɕύX
	SetZBufferBitDepth(24);
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);


	//! Effekseer
	//{@
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (Effkseer_Init(8000) == -1) {
		DxLib_End();
		return -1;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	//@}

	// ---------------
    //! ����������
    // ---------------
	KeyInputInit();
	gamemain.Initialize();

	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false);

	SetHookWinProc(WndProc);

	//-----------------------------------------------------------------------
    //! @name�@imgui
    //-----------------------------------------------------------------------
    //@{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	g_pd3dDevice = (ID3D11Device*)(GetUseDirect3D11Device());
	g_pd3dDeviceContext = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();

	ImGui_ImplWin32_Init(GetMainWindowHandle());
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	//@}

	while (ProcessMessage() == 0 && !IsKeyOn(KEY_INPUT_ESCAPE) && KeyInputUpdate() == 0)
	{
		//-----------------------------------------------------------------------
		//! @name�@imgui
		//-----------------------------------------------------------------------
		//@{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		//@}

		PadInputUpdate();
		// ---------------
		//! �X�V����
		// ---------------
		gamemain.Update();

		// ---------------
		//! �`�揈��
		// ---------------
		ClearDrawScreen();
		clsDx();
		
		gamemain.Draw();

		//-----------------------------------------------------------------------
        //! @name�@imgui
        //-----------------------------------------------------------------------
        //@{
		ImGui::Render(); 
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		//@}

		ScreenFlip();
	}

	// ---------------
	// �I������
	// ---------------
	KeyInputExit();
	PadInputExit();

	//-----------------------------------------------------------------------
	//! @name�@imgui
	//-----------------------------------------------------------------------
	//@{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	//@}

	// Effekseer���I������B
	Effkseer_End();

	DxLib_End();

	return 0;
}

