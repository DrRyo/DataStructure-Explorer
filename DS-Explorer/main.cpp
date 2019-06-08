/**
*	@mainpage	Folder Explorer
*				This is a middle project on data structures course.<br>
*
*				- Doxygen GUI 설정법<br>
*				Step 1: Doxygen 으로 문서화 할 프로젝트 경로 삽입.<br>
*				Step 2: Wizard 탭에서 Project name 설정.<br>
*				Step 3: Wizard 탭에서 Source code directory 에 문서화 할 소스 경로 지정 후 Scan recursively 를 체크.
*						[Step 1] 의 경로와 같은 경로를 삽입해도 됨.<br>
*				Step 4: Destination directory 에 문서화한 데이터가 저장될 경로 지정.<br>
*				Step 5: Wizard 탭의 Output 에서 LaTeX 체크 해제.<br>
*				Step 6: Run 탭의 Run doxygen 수행 후, "Doxygen has finished" 확인.<br>
*
*				- 한글사용을 위해서는 Doxywizard에서 아래와 같이 설정할 것.<br>
*				Expert 탭 -> Input (Topics 에서 선택) -> INPUT_ENCODING 을 "UTF-8" 로 설정.
*
*	@date		2019-06-08
*	@author		전자공학과 2014103991 우주현
*/

#include "Application.h"

/**
*	program main function for data structures course.
*/
int main() {
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	///
	/// Create our main App instance.
	///
	auto app = u::App::Create();

	///
	/// Create our Window using default window flags.
	///
	auto window = u::Window::Create(app->main_monitor(), 1600, 900, false, u::kWindowFlags_Titled);

	///
	/// Set our window title.
	///
	window->SetTitle("DS Explorer");

	///
	/// Bind our App's main window.
	///
	/// @note This MUST be done before creating any overlays or calling App::Run
	///
	app->set_window(window);

	///
	/// Create our MyApp instance (creates overlays and handles all logic).
	///
	Application explorer(window, "root", ".\\");

	///
	/// Run our main loop.
	///
	app->Run();

	return 0;
}