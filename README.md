<h1 align="center">Welcome to argentum-imgui 👋</h1>
<p>
  <a href="https://opensource.org/licenses/MIT" target="_blank">
    <img alt="License: MIT" src="https://img.shields.io/badge/License-MIT-yellow.svg" />
  </a>
</p>

> ImGui integration for the popular 2D MMORPG Argentum Online
## What is this?
This is an integration of [Dear ImGui](https://github.com/ocornut/imgui) (a bloat-free graphical user interface library for C++) into Argentum Online. For this, it's necessary to hook DirectX EndScene/BeginScene/Present in order to hijack the d3d device, serve it to ImGui and gain access to an extensive graphical interface.
## What is the usage?
When you inject a dll to a process, the interaction with I/O is either very poor (e.g spawning a console) or very complex (e.g having to make a GUI on C# and connect it with the dll via pipes). What this enables you is to have an extensive graphical interface to make complex components for the user to interact directly from your dll.
## Is this only for Argentum Online?
No. This can be extended to any DX8 game, the only thing you need to find by yourself is the method to feed ImGui the currently pressed keys (in this example, [this is the way](https://github.com/Reversive/argentum-imgui/blob/dc98afcd8be645fee2cf5cde23059172b775d03a/argentum-imgui/argentum/hooks/impl/hooks.cpp#L4)). Generally it can be done with a WndProc hook but it varies from game to game (e.g some may use DirectInput to which you will need to hook into the created devices to see which keys are being processed in-game).
## Requirements
- [DirectX Software Development Kit](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
- [dxwrapper](https://github.com/elishacloud/dxwrapper) to wrap dx8 calls into dx9 (put the d3d8.dll, dxwrapper.dll and dxwrapper.ini in the game executable directory and enable d3d8to9 setting on dxwrapper.ini)
## Showcase

### Radar PoC


https://user-images.githubusercontent.com/14043761/159783642-b2689318-f98f-4ae9-b76d-5653b68abda7.mp4
#### DISCLAIMER: Sole purpose of this showcase is giving people insight on how you can interact with the UI, this showcase/feature is not included in the repository and will never be, don't message me asking on how to achieve this.



### ImGui Demo Menu
https://user-images.githubusercontent.com/14043761/159626853-49a286e4-5e2a-4ca0-8c0d-0404d8dbbc00.mp4



## Author

👤 **Matias Pavan**

* Github: [@Reversive](https://github.com/Reversive)

## 🤝 Contributing

Contributions, issues and feature requests are welcome!<br />Feel free to check [issues page](https://github.com/Reversive/argentum-imgui/issues). 

## Show your support

Give a ⭐️ if this project helped you!

## 📝 License

Copyright © 2022 [Matias Pavan](https://github.com/Reversive).<br />
This project is [MIT](https://opensource.org/licenses/MIT) licensed.
***
DISCLAIMER: Sole purpose of this repository is giving people insight into how to integrate ImGui to any dx8 game, please, don't do anything that negatively impacts someone.
***
