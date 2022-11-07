#include <windows.h>
#include <iostream>

using namespace std;

string clipboardData();

int main(int argc, char* argv[]){

    RegisterHotKey(NULL, 1000, MOD_ALT + MOD_SHIFT, 0x53);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        if (msg.message == 786) {
            string text = clipboardData();
            Sleep(500);
            for (int i=0;i<text.length();i++){
                if (text[i] == '\r'){
                    continue;
                }
                SHORT keyScanned = VkKeyScan(text[i]);
                SHORT lowbit = keyScanned & 0xFF;
                bool highbit = (keyScanned & 0x100) > 0;
                if ((highbit == 1)){
                    INPUT inputs[4] = {};
                    ZeroMemory(inputs, sizeof(inputs));
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_LSHIFT;
                
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = lowbit;

                    inputs[2].type = INPUT_KEYBOARD;
                    inputs[2].ki.wVk = lowbit;
                    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

                    inputs[3].type = INPUT_KEYBOARD;
                    inputs[3].ki.wVk = VK_LSHIFT;
                    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
                    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                } else {
                    INPUT inputs[2] = {};
                    ZeroMemory(inputs, sizeof(inputs));
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = lowbit;

                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = lowbit; 
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
                    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                }
            }
        }
    }
    return 0;
}


string clipboardData(){
    OpenClipboard(nullptr);
    handle_t hdata = GetClipboardData(CF_TEXT);
    char * pszText = static_cast<char*>( GlobalLock(hdata) );
    std::string text( pszText );
    GlobalUnlock( hdata );
    CloseClipboard();
    return text;
}



