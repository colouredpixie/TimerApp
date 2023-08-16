#include "App.h"
#include "TimerApp.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	TimerFrame* timerFrame = new TimerFrame("Timer App");
	timerFrame->SetClientSize(450, 450);
	timerFrame->Center();
	timerFrame->Show();

	return true;
}
