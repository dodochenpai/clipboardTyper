import win32clipboard
import pyautogui
import time
import keyboard

win32clipboard.OpenClipboard()
data = win32clipboard.GetClipboardData()
win32clipboard.CloseClipboard()

shortcut = "alt+1"

def on_hotkey():
    pyautogui.typewrite(data)

keyboard.add_hotkey(shortcut, on_hotkey)
keyboard.wait('esc')
